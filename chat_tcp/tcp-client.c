#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "config.h"
int client_fd;

void* recv_thread(){

    while (1)
    {
        char reponse[BUFSIZ];memset(reponse,0,BUFSIZ);
        int error = recv(client_fd,reponse,BUFSIZ,0);perror("recv()");
        if(error == -1) return NULL;

        printf("%s\n",reponse);

        
    }
}


int main(int argc,char **argv){
    // printf("argc : %d\n",argc);
    int port_client=atoi(argv[1]);
    // printf("argv[1] : %d\n",port_client);
    



    client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    if(client_fd == -1) return EXIT_FAILURE;
    
    struct sockaddr_in addr =
    {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(port_client)
    };
    
    int error = bind(client_fd,(struct sockaddr*)&addr, sizeof(addr));perror("blind()");
    if(error == -1) return EXIT_FAILURE;
    

    struct sockaddr_in serv_addr = 
    {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = inet_addr ("127.0.0.1")
    };
    

    error = connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));perror("connect()");
    if(error == -1) return EXIT_FAILURE;

    pthread_t thread;
    pthread_create(&thread,NULL,recv_thread,(void*)client_fd);perror("pthread_create");
    if(thread == -1)return EXIT_FAILURE;

    while(1){


    char envoie[BUFSIZ];memset(envoie,0,BUFSIZ);
    fgets(envoie,BUFSIZ,stdin);
    error = send(client_fd,envoie,BUFSIZ,0);perror("send()");
    if(error == -1) return EXIT_FAILURE;

    
    }

    close(client_fd);perror("close()");


    return 0;
}