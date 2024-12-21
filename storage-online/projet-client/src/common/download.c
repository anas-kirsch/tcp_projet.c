#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"
        


void download(char* cmd_name, int client_fd){

    int sizeFile = 0;

    char path[BUFSIZ+strlen("build/public/")-1];/*recupere chemin vers les images*/


      /*send file name que je veux recevoir*/
        int check_error = send(client_fd,cmd_name,BUFSIZ,0);perror("send");
        // check_error = send(client_fd,cmd_name,strlen(cmd_name)+1,0);perror("send");
        if (check_error == -1  ){  close(client_fd);return ;}

        check_error = recv(client_fd,&sizeFile,sizeof(int),0);perror("recv");
        if (check_error == -1 ){return ;}
        printf("sizefile : %d\n",sizeFile);
        
        char file[sizeFile];memset(file,0,sizeFile);/*commentaire peux etre*/
        check_error = recv(client_fd,file,sizeFile,0);perror("recv");
        if (check_error == -1 ){return ;}
        
        /*ouvre le fichier contenant l'image */
        sprintf(path,"build/public/%s",cmd_name);perror("sprintf");/*colle deux chaine de caractere*/
        printf("path : %s\n",path);
        FILE* fd = fopen(path,"w+");perror("fopen");/*ouvre le fd a lire */
        fseek(fd,0,SEEK_SET);
        fwrite(file,sizeFile,1,fd);perror("fwrite");
        // fread(file,sizeFile,1,fd);perror("fread"); 



}