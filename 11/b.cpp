#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

void okreq(int sock,char *req){

    char html[1024] ={0};
    if (strcmp(req, "/")==0){
        strcpy(html , "HTTP/1.1 200 OK");
    }else if (strcmp(req, "/")==0){
        strcpy(html , "HTTP/1.1 200 OK");
    }else{
        strcpy(html , "HTTP/1.1 404 Not Found");
    }
    int html_len = strlen(html);
    html[html_len] = 0x0d;
    html[html_len + 1] = 0x0a;
    html[html_len + 2] = 0x0d;
    html[html_len + 3] = 0x0a;
    write(sock, html, html_len + 4);
}

int main(){
    int sock0 = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock0, 5);

    struct sockaddr_in client;
    unsigned int len = sizeof(client);
    int sock = accept(sock0, (struct sockaddr *)&client, &len);
    char buff[1024] = {0};
    int n = read(sock, buff, sizeof(buff));
    char *req = strtok(buff, " ");
    req = strtok(NULL, " ");
    printf("%s",req);
    char* file;
    if (strcmp(req, "/") == 0){ // index
        okreq(sock,req);
        int fd = fopen("hello.html",r);
        fread(file,sizeof(char),1024,fd);
        write(sock, file, strlen(body));
    }else if (strcmp(req, "/wd") == 0){
        okreq(sock,req);
        int fd = fopen("world.html",r);
        fread(file,sizeof(char),1024,fd);
        write(sock, file, strlen(body));
    }else{
        okreq(sock,req);
        int fd = fopen("404.html",r);
        fread(file,sizeof(char),1024,fd);
        write(sock, file, strlen(body));
    }

    close(sock);
    close(sock0);
    return 0;
}