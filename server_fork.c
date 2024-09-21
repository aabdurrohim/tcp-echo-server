#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]){
    int ser_sock, client_sock;
    char message[BUF_SIZE];
    int str_len, i;
    pid_t pid;

    struct sockaddr_in ser_adr;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    ser_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (ser_sock == -1)
        error_handling("socket() error");

    memset(&ser_adr, 0, sizeof(ser_adr));
    ser_adr.sin_family = AF_INET;
    ser_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    ser_adr.sin_port = htons(atoi(argv[1]));

    if (bind(ser_sock, (struct sockaddr*)&ser_adr, sizeof(ser_adr)) == -1)
        error_handling("bind() error");

    if (listen(ser_sock, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);

    while (1) {
        client_sock = accept(ser_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if (client_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected to client: %s\n", inet_ntoa(clnt_adr.sin_addr));

        pid = fork();
        if (pid == 0) { // child process
            close(ser_sock);
            while ((str_len = read(client_sock, message, BUF_SIZE)) != 0) {
                write(client_sock, message, str_len); // echo back to client
                message[str_len] = 0;
                printf("Message from client: %s\n", message);
            }
            close(client_sock);
            return 0;
        }
        close(client_sock); // parent closes connected socket
    }

    close(ser_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
