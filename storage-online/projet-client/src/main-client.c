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
#include "common/upload.c"


#define UPLOAD 1
#define DOWNLOAD 2
#define LIST 3
#define DELETE 4


int client_fd;



int main(int argc,char** argv){

    if (argc >= 2)
    {
        printf("argv[1]: %s\n",argv[1]);
    }
    if (argc >= 2)
    {
        printf("argv[2]: %s\n",argv[2]);
    }
    

    client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if (client_fd == -1){return EXIT_FAILURE;}
    
    struct sockaddr_in client_addr = {
    
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };
    
    int check_error = bind(client_fd,(struct sockaddr*)&client_addr,sizeof client_addr);perror("bind");
    if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}

    struct sockaddr_in server_addr = {

        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };
  
    check_error = connect(client_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("connect");
    if(check_error == -1 ) { close(client_fd); return EXIT_FAILURE; }



    int choix=0;
    if(strcmp(argv[1],"upload")==0){
        choix = UPLOAD;
    }
    else if(strcmp(argv[1],"download")==0){
        choix = DOWNLOAD;
    }
    if(strcmp(argv[1],"list")==0){
        choix = LIST;
    }
    if(strcmp(argv[1],"delete")==0){
        choix = DELETE;
    }




    switch(choix) {
    case UPLOAD:
        upload(argv[2]);

        break;
    case DOWNLOAD:
        break;
    
    case LIST:
        break;

    case DELETE:
        break;
    
    default:
        break;
    }








    

    return 0;
}