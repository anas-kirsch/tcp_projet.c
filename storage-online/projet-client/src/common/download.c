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
        if (check_error == -1  ){  close(client_fd);return ;}

        check_error = recv(client_fd,&sizeFile,sizeof(long long int),0);perror("recv");
        if (check_error == -1 ){return ;}
        printf("sizefile : %d\n",sizeFile);
        
        sprintf(path,"build/public/%s",cmd_name);perror("sprintf");/*colle deux chaine de caractere*/
        printf("path : %s\n",path);
        FILE* fd = fopen(path,"wb+");perror("fopen");/*ouvre le fd a lire */
        rewind(fd);perror("rewind");


        char* file= malloc(sizeFile);

        long long int bytesReceived = 0;
        printf("bytes recv : %lld\n",bytesReceived);
      

        while (bytesReceived < sizeFile) {
        long long int chunkSize = recv(client_fd, file, sizeFile, 0);perror("recv");
        if (chunkSize <= 0) {
              perror("recv (file fragment)");
              fclose(fd);
              close(client_fd);
              return;
          }
        printf("bytes recv : %lld\n",bytesReceived);

          fwrite(file,1,chunkSize,fd);perror("fwrite");
          bytesReceived += chunkSize;
      }
      free(file);

 

      

}


