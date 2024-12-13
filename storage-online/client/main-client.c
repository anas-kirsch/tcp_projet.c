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
#include "../config.h"




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





    /*ouvre le fichier contenant l'image */
    FILE* fd = fopen("voiture.jpeg","r+");
    /*recupere sa taille*/
    fseek(fd,0,SEEK_END);
    int sizeFile = ftell(fd);
    printf("%d\n",sizeFile);

    /*envoie le nb d'octet en avance au serveur afin qu'il s'adapte au volume d'image qu'il recevra */
    check_error = send(client_fd,&sizeFile,sizeof(int),0);perror("send");
    if (client_fd == -1){return EXIT_FAILURE;}

    


    char envoie_image[sizeFile];memset(envoie_image,0,sizeFile);
    fseek(fd,0,SEEK_SET);
    fread(envoie_image,sizeFile,1,fd);
    /*envoie au serveur l'image */
    check_error = send(client_fd,envoie_image,sizeFile,0);perror("send");
    if (client_fd == -1){return EXIT_FAILURE;}


    /*envoie le nom du fichier pour que le serveur l'inclus dans la liste de fichier */
    // char filename[BUFSIZ];memset(filename,0,BUFSIZ);
    char cmd[BUFSIZ];memset(cmd,0,BUFSIZ);
    strcpy(cmd,argv[2]);
    printf("cmd : %s\n",cmd);
    check_error = send(client_fd,cmd,BUFSIZ,0);perror("send");
    if (client_fd == -1){return EXIT_FAILURE;}

    return 0;
}