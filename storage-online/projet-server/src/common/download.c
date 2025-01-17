// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <errno.h>
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
#include "../../../module/config.h"
        

void download(int client_fd){

   

    long long int sizeFile=0;
    char filename[BUFSIZ];memset(filename,0,BUFSIZ);
    char chemin[BUFSIZ];memset(chemin,0,BUFSIZ);/*recupere chemin vers les images ou texte*/
    char cmd_name[BUFSIZ];memset(cmd_name,0,BUFSIZ);

    

        int check_error = recv(client_fd,cmd_name,BUFSIZ,0);perror("recv");
        if (check_error == -1 ){return;}
        printf("cmd_name : %s\n",cmd_name);


        sprintf(chemin,"build/public/%s",cmd_name);perror("sprintf");/*colle deux chaine de caractere*/
        printf("chemin: %s\n",chemin);

        FILE* fd_fichier = fopen(chemin,"r+");perror("fopen");
        fseek(fd_fichier,0,SEEK_END);
        sizeFile = ftell(fd_fichier);
        printf("%lld\n",sizeFile);
        rewind(fd_fichier);
        // fseek(fd_fichier,0,SEEK_SET);

        check_error = send(client_fd,&sizeFile,sizeof(long long int),0);perror("send");
        if (client_fd == -1){return ;}









    char* buffer = malloc(sizeFile);
    // char buffer[sizeFile];memset(buffer,0,sizeFile);
    long long int bytesRead = 0;
    // printf("size of buffer : %d\n",sizeFile);
    // printf("sizefile : %d\n",sizeFile);
    


    while ((bytesRead = fread(buffer, 1, sizeFile, fd_fichier)) > 0) {
    long long int bytesSent = 0;
        // printf("bytessent = %d et bytesread = %d\n",bytesSent,bytesRead);
        while (bytesSent < bytesRead) {
            long long int sent = send(client_fd, buffer + bytesSent, bytesRead - bytesSent, 0);perror("send");
            if (sent == -1) {
                perror("send (file fragment)");
                fclose(fd_fichier);
                return;
            }
            bytesSent += sent;
        }
    }
    printf("Fichier envoyé avec succès !\n");
    free(buffer);
    fclose(fd_fichier);perror("fclose");

}





        // char* file = malloc(sizeFile);
        // check_error = send(client_fd,&sizeFile,sizeof(long long int),0);perror("send");
        // if (client_fd == -1){return  ;}

        // fseek(fd_fichier,0,SEEK_SET);
        // fread(file,sizeFile,1,fd_fichier);
        // check_error = send(client_fd,file,sizeFile,0);perror("send");
        // if (client_fd == -1){return ;}

        // free(file);