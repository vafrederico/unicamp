#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

#define error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#define error_exit(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

int main(int argc, char* argv[]){

    struct sockaddr_in socket_address;
    char buf[MAX_LINE];
    unsigned int len;
    int s, new_s;

    /* criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_addr.s_addr = htons(INADDR_ANY);
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(LISTEN_PORT);

    /* criação de socket passivo */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s== -1){
        error_exit("Failed to create socket\n")
    }
    printf("Socket created.\n");

    /* Associar socket ao descritor */
    if (bind(s, (struct sockaddr*) &socket_address, sizeof(socket_address)) == -1){
        error_exit("Failed to bind\n");
    }
    printf("Bound.\n");

	/* Criar escuta do socket para aceitar conexões */
    if (listen(s, MAX_PENDING) == -1){
        error_exit("Failed to listen\n");
    }
    printf("Listening.\n");

    /* aguardar/aceita conexão, receber e imprimir texto na tela, enviar eco */
    while (1) {
        new_s = accept(s, (struct sockaddr *) NULL, NULL);
        if (!new_s) {
            error("Failed to accept connection");
            continue;
        }
        printf("Connection accepted\n");
        while (1) {
            bzero(buf, MAX_LINE);
            if (read(new_s, buf, MAX_LINE) == -1) {
                error("Failed to read\n");
                break;
            }
            if (write(new_s, buf, strlen(buf) + 1) == -1) {
                error("Failed to write\n");
                break;
            }
            if (strlen(buf) != 0) {
                printf("Sent echo: %s", buf);
            }
        }
    }
}