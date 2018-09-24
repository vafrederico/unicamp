/**************************
******** Cliente *********
**************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include "utils.h"

#define SERVER_PORT 12345
#define MAX_LINE 256
#define CLIENT 1
extern int h_errno;
extern int errno;

// dados do servidor
//unsigned int message_port = 0;
char server_ip[INET_ADDRSTRLEN];

typedef struct car_packet_list {
    int s;
    car_packet_t car;
    bool ativo;
    unsigned int server_port;
} car_packet_list;

car_packet_list carros_client[MAX_CARS];

char *sec_messages[] =
        {
                "Olá!",
                "Continue",
                "Diminua",
                "Acelere",
                "Chame ambulância!"
        };

/**
 * Imprime mensagem formatada IP e porta do servidor.
 * @param msg Mensagem a ser imprimida
 */
void print_message(int idx_carro, char msg[MAX_LINE]) {
    printf("[%15s, %u, %d] %s\n", server_ip, carros_client[idx_carro].server_port, idx_carro, msg);
}

int main(int argc, char *argv[]) {
    struct hostent *host_address;
    struct sockaddr_in socket_address;
    char *host, *file_name;
    char buf[MAX_LINE];
    char line[MAX_LINE];
    int len, msg_idx;
    FILE *f;
    car_packet_t carro;

    /* verificação de argumentos */
    if (argc != 5 || strcmp(argv[1], "-h") || strcmp(argv[3], "-i")) {
        printf("Entrada invalida!\nFormato esperado: 'cliente -h hostname -i input_file'\n");
        return EINVAL;
    }

    host = argv[2];
    file_name = argv[4];

    /* tradução de nome para endereço IP */
    host_address = malloc(sizeof(struct hostent));
    if (host_address == NULL) {
        return ENOMEM;
    }

    host_address = gethostbyname(host);
    if (host_address == NULL) {
        printf("Erro ao traduzir nome do host.\n");
        return h_errno;
    }

    /* criação da estrutura de dados de endereço */
    bzero((char *) &socket_address, sizeof(socket_address));


    /* abrir arquivo com inputs */
    f = fopen(file_name, "r");

    for (int i = 0; i < MAX_CARS; i++) {
        carros_client[i].ativo = false;
        carros_client[i].s = -1;
    }
    int ativos = 0;
    /* ler e enviar linhas de texto, receber resposta */
    while (fgets(line, MAX_LINE, f)) {
        if (strchr(line, '#'))
            continue;

        memset(&carros_client[ativos].car, 0, sizeof(car_packet_t));

        /* criação de socket ativo*/
        carros_client[ativos].s = socket(AF_INET, SOCK_DGRAM, 0);
        if (carros_client[ativos].s < 0) {
            printf("Erro ao criar o socket.\n");
            return errno;
        }

        bcopy(&socket_address.sin_addr, host_address->h_addr_list[0], host_address->h_length);
        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(SERVER_PORT);
        len = sizeof(socket_address);

        carros_client[ativos].car.type = PACKET_T_HELLO;
        memcpy(buf, &carros_client[ativos].car, sizeof(car_packet_t));
        if (sendto(carros_client[ativos].s, buf, sizeof(car_packet_t), 0, (struct sockaddr *) &socket_address, len) ==
            -1) {
            printf("Erro ao enviar mensagem para o host.\n");
        }

        memset(buf, 0, MAX_LINE);
        if (recvfrom(carros_client[ativos].s, buf, MAX_LINE, 0, (struct sockaddr *) &socket_address, &len) == -1) {
            printf("Erro ao receber eco do servidor.");
        } else {
            printf("%s\n", buf);
            memset(buf, 0, MAX_LINE);
        }

        //socket_address.sin_port = htons(message_port);
        if (connect(carros_client[ativos].s, (struct sockaddr *) &socket_address, len) < 0) {
            perror("Connect");
            return errno;
        }

        inet_ntop(AF_INET, &(socket_address.sin_addr), server_ip, INET_ADDRSTRLEN);
        carros_client[ativos].server_port = ntohs(socket_address.sin_port);
        print_message(ativos, "Pronto para enviar mensagens.");
        sscanf(line, "%d %u %d %d %d %d %u", &carros_client[ativos].car.type, &carros_client[ativos].car.ts,
               &carros_client[ativos].car.pos_x, &carros_client[ativos].car.pos_y, &carros_client[ativos].car.vel,
               &carros_client[ativos].car.dir,
               &carros_client[ativos].car.size);
        carros_client[ativos].ativo = true;
        ativos++;
        printf("%s\n", line);
    }

    int tempo = 0;
    while (ativos > 0) {

        for (int c = 0; c < MAX_CARS; c++) {
            if (!carros_client[c].ativo) continue;
            print_message(c, "Running");
            carros_client[c].car.ts = tempo;
            sprintf(line, "Tempo: %u X: %d Y: %d Vel: %d Dir: %d Tamanho: %u", carros_client[c].car.ts,
                    carros_client[c].car.pos_x, carros_client[c].car.pos_y, carros_client[c].car.vel,
                    carros_client[c].car.dir,
                    carros_client[c].car.size);
            print_message(c, line);
            print_packet(carros_client[c].car);
            memcpy(buf, &carros_client[c].car, sizeof(car_packet_t));
            if (send(carros_client[c].s, buf, sizeof(buf), 0) == -1) {
                print_message(c, "Erro ao enviar mensagem para o host.");
                continue;
            }

            if (recv(carros_client[c].s, buf, sizeof(buf), 0) == -1) {
                print_message(c, "Erro ao receber resposta do servidor.");
            } else {
                //TODO aumentar ou diminuir a velocidade de acordo com a mensagem recebida
                msg_idx = strtol(buf, NULL, 10);
                print_message(c, sec_messages[msg_idx]);
                if (msg_idx == MSG_SLOW) {
//                    if (carros_client[c].car.vel / 2 > 0)
                    carros_client[c].car.vel /= 2;
                    printf("Velocidade reduzida para %d\n", carros_client[c].car.vel);
                } else if (msg_idx == MSG_ACC) {
                    carros_client[c].car.vel *= 2;
                    if (carros_client[c].car.vel == 0) carros_client[c].car.vel = 1;
                    printf("Velocidade aumentada para %d\n", carros_client[c].car.vel);
                }
                memset(buf, 0, MAX_LINE);
            }

            switch (carros_client[c].car.dir) {
                case up:
                    if (carros_client[c].car.pos_y < carros_client[c].car.size) //0 + tamanho
                    {
                        carros_client[c].car.pos_y += carros_client[c].car.vel;
                        if (carros_client[c].car.pos_y > -1 && carros_client[c].car.pos_y < 1)
                            carros_client[c].car.pos_y++;
                    } else {
                        //já passou do cruzamento
                        carros_client[ativos].ativo = false;
                        ativos--;
                    }
                    break;
                case down:
                    if (carros_client[c].car.pos_y > -carros_client[c].car.size) //0 - tamanho
                    {
                        carros_client[c].car.pos_y -= carros_client[c].car.vel;
                        if (carros_client[c].car.pos_y > -1 && carros_client[c].car.pos_y < 1)
                            carros_client[c].car.pos_y--;
                    } else {
                        //já passou do cruzamento
                        carros_client[ativos].ativo = false;
                        ativos--;
                    }
                    break;
                case left:
                    if (carros_client[ativos].car.pos_x > -carros_client[ativos].car.size) //0 + tamanho
                    {
                        carros_client[c].car.pos_x -= carros_client[c].car.vel;
                        if (carros_client[c].car.pos_x > -1 && carros_client[c].car.pos_x < 1)
                            carros_client[c].car.pos_x--;
                    } else {
                        //já passou do cruzamento
                        carros_client[ativos].ativo = false;
                        ativos--;
                    }
                    break;
                case right:
                    if (carros_client[ativos].car.pos_x < carros_client[ativos].car.size) //0 - tamanho
                    {
                        carros_client[c].car.pos_x += carros_client[c].car.vel;
                        if (carros_client[c].car.pos_x > -1 && carros_client[c].car.pos_x < 1)
                            carros_client[c].car.pos_x++;
                    } else {
                        //já passou do cruzamento
                        carros_client[ativos].ativo = false;
                        ativos--;
                    }
                    break;
            }

        }
        usleep(500000); //500ms
        tempo++;
    }

    fclose(f);

    for (int i = 0; i < MAX_CARS; i++) {
        if (carros_client[i].s != -1)
            close(carros_client[i].s);
    }

    return 0;
}
