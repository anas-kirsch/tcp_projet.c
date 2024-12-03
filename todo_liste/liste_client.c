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

#include "config.h"


int main(){

    int client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if(client_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in client_addr = {

        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };


    int error = bind(client_fd,(struct sockaddr*)&client_addr,sizeof client_addr);perror("bind");
    if(error == -1){ close(client_fd);  return EXIT_FAILURE; }

    struct sockaddr_in server_addr = {

        .sin_addr.s_addr =  inet_addr("127.0.0.1"),
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
        
        };

    error = connect(client_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("connect");
    if(error == -1) { close(client_fd); return EXIT_FAILURE; }



    printf("-------------------------------\n");
    printf("1- Créer votre ToDo List\n");
    printf("2- Afficher une liste existente\n");
    printf("0- Quitter \n");
    printf("-------------------------------\n");
    
    while(1){

    char choix[BUFSIZ];memset(choix,0,BUFSIZ);
    fgets(choix,BUFSIZ,stdin);
    int number_choice = atoi(choix);

    error = send(client_fd,choix,BUFSIZ,0);perror("send");
    if(error == -1) { close(client_fd); return EXIT_FAILURE; }

    switch (number_choice)
    {
    case 1:
        printf("Entrez la tache à executer.. \n");
        fgets(choix,BUFSIZ,stdin);

        error = send(client_fd,choix,BUFSIZ,0);perror("send");
        if(error == -1) { close(client_fd); return EXIT_FAILURE; }
        break;

    case 2:

        printf("Voici votre liste\n");
        error = recv(client_fd,choix,BUFSIZ,0);perror("recv");
        if (error == -1){return EXIT_FAILURE;}

        printf("%s\n",choix);        
        
        
        break;
    default:
        break;
    }



    
    }
    close(client_fd);perror("close");
    return EXIT_FAILURE;


    return 0;
}