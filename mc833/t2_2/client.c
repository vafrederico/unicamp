#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define SERVER_PORT 12345
#define MAX_LINE 256

#define error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); continue;}
#define error_exit(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1);}
int main(int argc, char * argv[])
{
    struct hostent *host_address;
    struct sockaddr_in socket_address;
    char buf[MAX_LINE];
    int sockfd;

	/* verificação de argumentos */
	if (argc < 2) {
		error_exit("USAGE: ./client <hostname>\n");
	}

	/* tradução de nome para endereço IP */
	host_address = gethostbyname(argv[1]);
    if (!host_address){
        error_exit("Hostname not found\n");
    }
    printf("Host address resolved.\n");

    /* criação da estrutura de dados de endereço */
    bzero((char *)&socket_address, sizeof(socket_address));
    socket_address.sin_port = htons(SERVER_PORT);
    socket_address.sin_family = AF_INET;
    inet_pton(AF_INET, host_address->h_name, &(socket_address.sin_addr));

    /* criação de socket ativo*/
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1){
        error_exit("Failed to create socket\n")
    }
    printf("Socket created.\n");

	/* estabelecimento da conexão */
    if (connect(sockfd,(struct sockaddr *)&socket_address, sizeof(socket_address)) == -1){
        error_exit("Failed to connect\n");
    }
    printf("Connected.\n");

    struct sockaddr_in local_address;
    socklen_t socklen = sizeof local_address;
    if (getsockname(sockfd, (struct sockaddr *) &local_address, &socklen) == -1){
        error_exit("Failed to get socket information\n");
    }
    char address[INET6_ADDRSTRLEN];
    int port = ntohs(local_address.sin_port);
    if (ntohs(local_address.sin_family) == AF_INET6){
        inet_ntop(AF_INET6, &local_address.sin_addr, address, sizeof(address));
    } else {
        inet_ntop(AF_INET, &local_address.sin_addr, address, sizeof(address));
    }
    printf("Socket address: %s:%d\n", address, port);

    /* ler e enviar linhas de texto, receber eco */
    while (1) {
        bzero(buf, sizeof(buf));
        fgets(buf, MAX_LINE, stdin);
        printf("Writing to socket.\n");
        if (write(sockfd, buf, strlen(buf)+1) == -1){
            error("Failed to write\n");
        }

        printf("Reading from socket.\n");
        if (read(sockfd, buf, strlen(buf)+1) == -1) {
            error("Failed to read\n");
        }
        printf("Received: %s", buf);
    }
}
#pragma clang diagnostic pop