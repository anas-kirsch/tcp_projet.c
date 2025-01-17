#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"
        


void download(char* cmd_name, int client_fd){

    long long int sizeFile = 0;

    char path[BUFSIZ+strlen("build/public/")-1];/*recupere chemin vers les images*/


      /*send file name que je veux recevoir*/
        int check_error = send(client_fd,cmd_name,BUFSIZ,0);perror("send");
        // check_error = send(client_fd,cmd_name,strlen(cmd_name)+1,0);perror("send");
        if (check_error == -1  ){  close(client_fd);return ;}

        check_error = recv(client_fd,&sizeFile,sizeof(long long int),0);perror("recv");
        if (check_error == -1 ){return ;}
        printf("sizefile : %d\n",sizeFile);
        
        /*ouvre le fichier contenant l'image */
        sprintf(path,"build/public/%s",cmd_name);perror("sprintf");/*colle deux chaine de caractere*/
        printf("path : %s\n",path);
        FILE* fd = fopen(path,"wb+");perror("fopen");/*ouvre le fd a lire */
        rewind(fd);perror("rewind");
        // fseek(fd,0,SEEK_SET);perror("fseek");

















        char* file= malloc(sizeFile);
        // char file[sizeFile];memset(file,0,sizeFile);

        long long int bytesReceived = 0;
        // printf("sizefile : %d\n",sizeFile);
        // printf("taille : %d\n",sizeof(file));
        printf("bytes recv : %lld\n",bytesReceived);
      

        while (bytesReceived < sizeFile) {
        long long int chunkSize = recv(client_fd, file, sizeFile, 0);perror("recv");
        // printf("bytessent = %d et bytesread = %d\n",chunkSize,bytesReceived);
        if (chunkSize <= 0) {
              perror("recv (file fragment)");
              fclose(fd);
              close(client_fd);
              return;
          }
        printf("bytes recv : %lld\n",bytesReceived);

          // fseek(fd,0,SEEK_SET);
          fwrite(file,1,chunkSize,fd);perror("fwrite");
          bytesReceived += chunkSize;
      }
      free(file);

  
        // fwrite(file,sizeFile,1,fd);perror("fwrite");
        // // fread(file,sizeFile,1,fd);perror("fread"); 

      

}



        // char* file = malloc(sizeFile);
        // check_error = recv(client_fd,file,sizeFile,0);perror("recv");
        // if (check_error == -1 ){return ;}