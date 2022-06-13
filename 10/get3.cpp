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

    char  get[32],filename[16];
    printf("filename:");
    scanf("%s",filename);
    sprintf(get,"GET /%s HTTP/1.0",filename);
    int len = strlen(get);
    get[len] = 0x0d;
    get[len + 1] = 0x0a;
    get[len + 2] = 0x0d;
    get[len + 3] = 0x0a;
    write(sock, get, len + 4);

    char buff[1024] = {0},cpbuff[1024];
    int n = read(sock, buff, sizeof(buff));
    strcpy(cpbuff,buff);
    char* status = strtok(cpbuff," ");
    status = strtok(NULL," ");
    if (strcmp(status,"200")!=0){
        printf("status:%s\n",status);
        return 1;
    }

    char delim[4]={0x0d,0x0a,0x0d,0x0a};
    char* html = strtok(buff,delim);
    html = strtok(NULL,delim);
    printf("%s", html);
    printf("\n-------------------------\n");
    // html = strtok(NULL,"\n");
    // printf("%s", html);
    // printf("\n-------------------------\n");
    // printf("%s", buff);
    // printf("\n-------------------------\n");
    while (n > 0){
        memset(buff, 0, sizeof(buff));
        n = read(sock, buff, sizeof(buff));
        printf("%s", buff);
    }
    close(sock);
    return 0;
}