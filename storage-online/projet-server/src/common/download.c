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

   

    int sizeFile=0;
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
        printf("%d\n",sizeFile);

        char file[sizeFile];memset(file,0,sizeFile);
        check_error = send(client_fd,&sizeFile,sizeof(int),0);perror("send");
        if (client_fd == -1){return  ;}

        fseek(fd_fichier,0,SEEK_SET);
        fread(file,sizeFile,1,fd_fichier);
        check_error = send(client_fd,file,sizeFile,0);perror("send");
        if (client_fd == -1){return ;}


}