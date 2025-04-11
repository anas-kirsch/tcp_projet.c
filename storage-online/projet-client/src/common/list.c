#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"
        

void list(int client_fd){

    int sizeFile = 0;

    int check_error = recv(client_fd,&sizeFile,sizeof(int),0);perror("recv");
    if (check_error == -1 ){return;}
    printf("sizefile : %d\n",sizeFile);
    char liste[sizeFile];memset(liste,0,sizeFile);

    check_error = recv(client_fd,liste,sizeFile,0);perror("recv");
    if (check_error == -1 ){return;}
    printf("Voici la liste :\n%s",liste);
}

