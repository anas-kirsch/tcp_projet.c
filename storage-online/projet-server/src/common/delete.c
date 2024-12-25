#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "../../../module/config.h"

int client_fd;

void delete(int client_fd){

    char filename[BUFSIZ];memset(filename,0,BUFSIZ);

    int check_error = recv(client_fd,filename,BUFSIZ,0);perror("recv");
    if (check_error == -1){return;}

    printf("filename : %s\n",filename);

    char pathname[BUFSIZ];memset(pathname,0,BUFSIZ);
    sprintf(pathname,"build/public/%s",filename);perror("sprintf");

    int access(const char *pathname, int mode);perror("access");

    remove(pathname);perror("remove");


    

    
    // remove(filename);


}