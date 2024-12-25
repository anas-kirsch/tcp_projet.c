#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include "../../module/config.h"
#include "../src/common/download.c"
#include "../src/common/upload.c"
#include "../src/common/list.c"
#include"../src/common/delete.c"

#define UPLOAD 1
#define DOWNLOAD 2
#define LIST 3
#define DELETE 4

int server_fd;


int main(){

    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");


    struct sockaddr_in serv_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    int check_error = bind(server_fd,(struct sockaddr*)&serv_addr,sizeof serv_addr);perror("bind");
    if (check_error == -1 ){return EXIT_FAILURE;}
    // printf("ahjefeejfejjjddjjdj\n");

    check_error = listen(server_fd,BUFSIZ);perror("listen");
    if (check_error == -1 ){return EXIT_FAILURE;}



    struct sockaddr_in client_addr;
    socklen_t len; 
    long int client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&len);perror("accept");
    if (client_fd == -1 || client_fd == 0){close(client_fd); close(server_fd); return EXIT_FAILURE; }




    int choix = 0;
    check_error = recv(client_fd,&choix,sizeof(int),0);perror("recv");
    if (check_error == -1 || check_error == 0){return EXIT_FAILURE;}


        int sizeFile=0;

        // char liste[sizeFile];memset(liste,0,sizeFile);
        

    switch (choix)
    {
    case UPLOAD:
        upload(client_fd);
        break;

    case DOWNLOAD:
        download(client_fd);
        break;

    case LIST:
        // printf("voici la liste\n");
        list(client_fd);
        break;

    case DELETE:
        printf("bufffff\n");
        delete(client_fd);

        break;
    default:
        break;
    }

 

    return 0;
}