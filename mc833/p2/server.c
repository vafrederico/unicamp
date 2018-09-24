/**************************
******** Servidor *********
***************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "security_app.h"
#include "utils.h"

#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

extern int errno;
bool debug = false;

/**
 * Detecta o tipo de pacote e processa de acordo.
 * @param id   ID do carro
 * @param c    Dados do carro
 * @param resp Retorna com o código da mensagem após o processamento
 */
void process_packet(unsigned int id, car_packet_t c, char * resp)
{
    int car_idx, res;

    if(debug)
        print_packet(c);

    switch(c.type)
    {
        case PACKET_T_HELLO:
            //printf("Greetings!\n");
            sprintf(resp, "%d", MSG_HELLO);
            break;
        case PACKET_T_SECURITY:
            res = detect_collision(id, c, false);
            sprintf(resp, "%d", res);
            usleep(10000); //10ms
            break;
        case PACKET_T_ENTERTAINMENT:
        case PACKET_T_TRAFFIC:
            sprintf(resp, "%d", MSG_OK);
            usleep(100000); //100ms
            break;
    }
}

/**
 * Thread que controla as conexões do servidor.
 * @param  thread_arg Vazio
 * @return            Vazio
 */
void *thread_server(void * thread_arg)
{
    struct sockaddr_in socket_address, client_address;
    char buf[MAX_LINE];
    char client_ip[INET_ADDRSTRLEN];
    unsigned int len;
    int s, new_s;
    int err, read_len;
    car_packet_t carro;

    /* criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(LISTEN_PORT);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    /* Criação de socket passivo */
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s == -1)
    {
        err = errno;
        printf("Falha ao criar o socket. Erro(%d)\n", err);
        pthread_exit(&err);
    }

	/* Associar socket ao descritor */
    if(bind(s, (struct sockaddr *) &socket_address, sizeof(socket_address)) < 0)
    {
        err = errno;
        printf("Falha ao associar socket com endereço. Erro(%d)\n", err);
        close(s);
        pthread_exit(&  err);
    }

    /* Aguardar/aceita conexão, receber e imprimir texto na tela, enviar eco */
    len = sizeof(struct sockaddr_in);
    bzero((char *)&client_address, len);
    memset(buf, 0, MAX_LINE);
    printf("Servidor inicializado.\n");
    while(true)
    {
        while((read_len = recvfrom(s, buf, MAX_LINE, 0, (struct sockaddr *)&client_address, &len)) > 0)
        {
            inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
            printf("[%15s, %u] Recebido.\n", client_ip, ntohs(client_address.sin_port));
            memcpy(&carro, buf, sizeof(car_packet_t));
            process_packet(ntohs(client_address.sin_port), carro, buf);

            if(sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&client_address, len) < 0)
            {
                printf("[%15s, %u] Falha ao responder cliente\n", client_ip, ntohs(client_address.sin_port));
            }
            else
            {
                printf("[%15s, %u] Resposta enviada: %s\n", client_ip, ntohs(client_address.sin_port), buf);
            }
        }

        if(read_len == -1)
        {
            printf("[%15s, %u] Falha ao receber mensagem do cliente.\n", client_ip, ntohs(client_address.sin_port));
        }
    }

    close(s);
}

int main(int argc, char *argv[])
{
    pthread_t threads[2];
    int *exit_code;

    if(argc == 2)
    {
        if(strcmp(argv[1], "-d") == 0)
        {
            debug = true;
        }
    }

    pthread_mutex_init(&mutex_grid, NULL);

    printf("Main: Criando threads.\n");
    pthread_create(&threads[0], NULL, thread_server, NULL);
    pthread_create(&threads[1], NULL, thread_update_cars_pos, NULL);

    printf("Main: Executando...\n");
    pthread_join(threads[0], (void **)&exit_code);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex_grid);

    printf("Main: Finalizando servidor.\n");

    return 0;
}
