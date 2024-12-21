#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"

int client_fd;

void upload(char* cmd){

    
        printf("cmd : %s\n",cmd);

        char path[BUFSIZ+strlen("build/public/")-1];/*recupere chemin vers les images*/
        /*ouvre le fichier contenant l'image */
        sprintf(path,"build/public/%s",cmd);perror("sprintf");/*colle deux chaine de caractere*/
        printf("path : %s\n",path);
        FILE* fd = fopen(path,"r+");perror("fopen");/*ouvre le fd a lire */
        /*recupere sa taille*/
        fseek(fd,0,SEEK_END);
        int sizeFile = ftell(fd);
        printf("%d\n",sizeFile);

        

        /*envoie le nb d'octet en avance au serveur afin qu'il s'adapte au volume d'image qu'il recevra */
        int check_error = send(client_fd,&sizeFile,sizeof(int),0);perror("send");
        if (client_fd == -1){return;}



        // char cmd[BUFSIZ];memset(cmd,0,BUFSIZ);
        // strcpy(cmd,argv[2]);
        // printf("cmd : %s\n",cmd);

        /*envoie le nom du fichier pour que le serveur l'inclus dans la liste de fichier */
        check_error = send(client_fd,cmd,strlen(cmd),0);perror("send");
        if (client_fd == -1){return;}

        /*declaration de variable pour envoyer au serveur le fichier choisi par le client*/
        char send_file[sizeFile];
        memset(send_file,0,sizeFile);
        fseek(fd,0,SEEK_SET);
        fread(send_file,sizeFile,1,fd);/*lis le fichier qui va etre envoyer*/
        /*envoie au serveur l'image ou fichier */
        check_error = send(client_fd,send_file,sizeFile,0);perror("send");
        if (client_fd == -1){return;}
}