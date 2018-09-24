#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

#define print(...) { fprintf(stdout, __VA_ARGS__); fflush(stdout); }
#define error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#define error_exit(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

int main(int argc, char* argv[]){

    struct sockaddr_in socket_address;
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
        new_s = accept(s, NULL, NULL);
        if (new_s == -1) {
            error("Failed to accept connection\n");
            continue;
        }

        socklen_t socklen;
        struct sockaddr_in client_address;
        if (getpeername(new_s, (struct sockaddr *) &client_address, &socklen) == -1){
            error("Failed to get client remote address\n");
        }
        char address[INET6_ADDRSTRLEN];
        int port = ntohs(client_address.sin_port);
        if (ntohs(client_address.sin_family) == AF_INET6){
            inet_ntop(AF_INET6, &client_address.sin_addr, address, sizeof(address));
        } else {
            inet_ntop(AF_INET, &client_address.sin_addr, address, sizeof(address));
        }
        print("Connection accepted from: %s:%d\n", address, port);

        pid_t pid = fork();
        if (pid == 0) {
            /* processo filho */
            char buf[MAX_LINE];
            while (1) {
                bzero(buf, MAX_LINE);
                if (read(new_s, buf, MAX_LINE) == -1) {
                    error("[%s:%d]: Failed to read\n", address, port);
                    break;
                }
                if (write(new_s, buf, strlen(buf) + 1) == -1) {
                    error("[%s:%d]: Failed to write\n", address, port);
                    break;
                }
                if (strlen(buf) != 0) {
                    print("[%s:%d]: Sent echo: %s", address, port, buf);
                }
            }
            close(new_s);
            break;
        } else if (pid > 0) {
            close(new_s);
        } else {
            close(new_s);
            error("Failed to fork\n");
        }
    }
}
#pragma clang diagnostic pop