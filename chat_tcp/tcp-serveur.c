
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
#include "config.h"

#define DISCONNECTED 0
#define ERROR -1

int serveur_fd;


int client[BUFSIZ];
int nb_clients=0;

/** 
 * Fonction qui lance le chat et demande au client le message et envoie au serveur puis attend la reponse, le serveur renvoie tout message que le client lui renvoie
 * @param void* arg - le client_fd doit etre un long int 
 * @return void* rien du tout
 */
void* chat_thread(void* arg){
    long int client_fd = (long int)arg;

    while(1){


        // printf("BIENVENUE client : %d\n",nb_clients);
            
        
            char reponse[BUFSIZ];//variable pour afficher le message d'un client

            
            memset(reponse,0,BUFSIZ);
            int error =  recv(client_fd,reponse,BUFSIZ,0);perror("recv()");
            if(error == -1) return NULL;


            printf("$%s\n",reponse);//verifie la reception des messages client 

            // si recv donc error renvoie une erreur ou deco ferme le client concerné 
            if (error == DISCONNECTED || error == ERROR)
            {
                close(client_fd);perror("close");
                nb_clients--;
                printf("Client déconnecté...\n");
            }
            
            // parcour les clients pour faire le brodwast 
            for (int j = 0; j < nb_clients; j++)
            {
                // si il n'y a aucune erreur/deco continue et send
                if (error != DISCONNECTED || error!= ERROR)
                {
                    // 
                    int error = send(client[j],reponse,BUFSIZ,0);perror("send()");
                    if(error == -1) return NULL;
                    // printf("%s\n",error);
                }
            }

           
    }
}



int main(){

    /**
     * 
     */
    serveur_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
    if(serveur_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in addr =
    {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(SERVER_PORT)
    };
    
    int error = bind(serveur_fd,(struct sockaddr*)&addr,sizeof(addr));perror("bind()");
    if(error == -1) return EXIT_FAILURE;

    listen(serveur_fd,BUFSIZ);perror("listen()");
    if(error == -1) return EXIT_FAILURE;


    while (1)
    {
        struct sockaddr client_addr;
        socklen_t len;
 
    
        long int client_fd = accept(serveur_fd,&client_addr,&len);perror("accept()");
        client[nb_clients] = client_fd;
        if(client_fd == -1) return EXIT_FAILURE;
        nb_clients++;
        printf("client : %d\n",nb_clients);


        pthread_t thread;
        pthread_create(&thread,NULL,chat_thread,(void*)client_fd);perror("pthread_create");
        if(thread == -1) return EXIT_FAILURE;


        // pthread_join;
  
        // close(client_fd);perror("close");
    

    }
    return 0;
}