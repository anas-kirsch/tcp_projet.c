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


    int sizeFile=0;

    

void list(int client_fd){


    FILE* list_file = fopen("build/bdd/liste-fichier.txt","a+");perror("fopen");

    fseek(list_file,0,SEEK_END);
    sizeFile = ftell(list_file);
    printf("%d\n",sizeFile);

    char liste[sizeFile];memset(liste,0,sizeFile);
    int check_error = send(client_fd,&sizeFile,sizeof(int),0);perror("send");
    if (check_error == -1 ){return;}

    fseek(list_file,0,SEEK_SET);
    fread(liste,sizeFile,1,list_file);

    check_error = send(client_fd,liste,sizeFile,0);perror("send");
    if (check_error == -1){return;} // if (check_error == -1 ){return;}
        


}