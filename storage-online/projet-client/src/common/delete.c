#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"

int client_fd;

void delete(int client_fd,char* cmd_name){


    printf("cmd : %s\n",cmd_name);

    int check_error = send(client_fd,cmd_name,BUFSIZ,0);perror("send");
    if (check_error == -1){return;}


}