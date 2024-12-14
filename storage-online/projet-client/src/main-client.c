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
        check_error= send(client_fd,&choix,sizeof(int),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
    }
    else if(strcmp(argv[1],"download")==0){
        choix = DOWNLOAD;
        check_error= send(client_fd,&choix,sizeof(int),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}

    }
    if(strcmp(argv[1],"list")==0){
        choix = LIST;
        check_error= send(client_fd,&choix,sizeof(int),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}

    }
    if(strcmp(argv[1],"delete")==0){
        choix = DELETE;
        check_error= send(client_fd,&choix,sizeof(int),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
    }

    

    switch(choix) {
    case UPLOAD:
        upload(argv[2]);

        break;
    case DOWNLOAD:
        /*si le case se lance alors je send argv[2 ] au serveur afin qui sache quelle fichier m'envoyer  */
        /*je recv la sizefile pour facilite le recv du fichier*/
        /*je recv limage et je la lis en louvrant avec le chemin ver le dossier pulic*/
        break;
    
    case LIST:
        /*permet de demande la liste des fichier pour en choisir un a recuperer du serveur */
        /*je recv la taille du fichier liste */
        /* je recv le fichier liste lui meme 
        contenu dans le buff et je printf le buff avec la liste(autre solution jouvre le fichier a+ et je read
        )*/
        break;

    case DELETE:
        /*je send le nom du fichier a delete*/
        break;
    
    default:
        printf("Erreur dans la commande\n");
        break;
    }








    

    return 0;
}