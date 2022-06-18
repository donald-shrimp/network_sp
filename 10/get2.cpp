#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = inet_addr("133.43.7.130");
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    char  get[64],filename[32];
    printf("filename:");
    scanf("%s",filename);
    sprintf(get,"GET /%s HTTP/1.0",filename);
    int len = strlen(get);
    get[len] = 0x0d;
    get[len + 1] = 0x0a;
    get[len + 2] = 0x0d;
    get[len + 3] = 0x0a;
    write(sock, get, len + 4);

    char buff[1024] = {0};
    int n = read(sock, buff, sizeof(buff));
    printf("%s", buff);
    while (n > 0){
        memset(buff, 0, sizeof(buff));
        n = read(sock, buff, sizeof(buff));
        printf("%s", buff);
    }
    close(sock);
    return 0;
}