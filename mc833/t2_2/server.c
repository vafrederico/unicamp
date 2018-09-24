#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define LISTEN_PORT 12345
#define MAX_PENDING 5
#define MAX_LINE 256

#define print(...) { fprintf(stdout, __VA_ARGS__); fflush(stdout); }
#define error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#define error_exit(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }

typedef struct {
    int sockfd;
    char address[INET6_ADDRSTRLEN];
    int port;
} cliente;

int main(int argc, char* argv[]){
    char buf[MAX_LINE];
    struct sockaddr_in socket_address;
    ssize_t len;
    int s, new_s, maxfd, nready;
    cliente clientes[FD_SETSIZE];
    fd_set todos_fds, novo_set;

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

    maxfd = s;
    int i;
    int cliente_num = -1;
    for (i = 0; i < FD_SETSIZE; i++){
        bzero(&clientes[i], sizeof(clientes[i]));
        clientes[i].sockfd = -1;
    }
    FD_ZERO(&todos_fds);
    FD_SET(s, &todos_fds);

    /* aguardar/aceita conexão, receber e imprimir texto na tela, enviar eco */
    while (1) {
        novo_set = todos_fds;
        nready = select(maxfd+1, &novo_set, NULL, NULL, NULL);

        if (FD_ISSET(s, &novo_set)){
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

            /* Adiciona novo socket na lista de clientes */
            for (i = 0; i < FD_SETSIZE; i++) {
                if (clientes[i].sockfd < 0) {
                    clientes[i].sockfd = new_s;
                    clientes[i].port = ntohs(client_address.sin_port);
                    if (ntohs(client_address.sin_family) == AF_INET6){
                        inet_ntop(AF_INET6, &client_address.sin_addr, clientes[i].address, sizeof(clientes[i].address));
                    } else {
                        inet_ntop(AF_INET, &client_address.sin_addr, clientes[i].address, sizeof(clientes[i].address));
                    }
                    print("Connection accepted from: %s:%d\n", clientes[i].address, clientes[i].port);
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                error_exit("Numero maximo de clientes atingido.");
            }
            /* Adiciona novo socket no set de descritores */
            FD_SET(new_s, &todos_fds);
            /* Atualiza maior descritor */
            if (new_s > maxfd)
                maxfd = new_s;

            /* Altera indice maximo do cliente */
            if (i > cliente_num)
                cliente_num = i;

            /* Atualiza descritores para serem lidos */
            nready--;
            if (nready <= 0)
                continue;
        }
        for (i = 0; i <= cliente_num; i++){
            if(clientes[i].sockfd < 0) continue;
            if (FD_ISSET(clientes[i].sockfd, &novo_set)) {
                len = recv(clientes[i].sockfd, buf, sizeof(buf), 0);
                if (len == 0) {
                    /* cliente fechou conexão */
                    close(clientes[i].sockfd);
                    clientes[i].sockfd = -1;
                    continue;
                }
                if (write(clientes[i].sockfd, buf, strlen(buf) + 1) == -1) {
                    error("[%s:%d]: Failed to write\n", clientes[i].address, clientes[i].port);
                    continue;
                }
                if (strlen(buf) != 0) {
                    print("[%s:%d]: Sent echo: %s", clientes[i].address, clientes[i].port, buf);
                }
            }
        }
    }
}
#pragma clang diagnostic pop