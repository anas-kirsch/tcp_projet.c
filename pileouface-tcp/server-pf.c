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
#include "config.h"

#define DISCONNECTED 0
#define ERROR -1

#define PILE 1
#define FACE 2
int server_fd;





int main(){

    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if (server_fd == -1 || server_fd == 0){return EXIT_FAILURE;}
    
    struct sockaddr_in serv_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    int check_error = bind(server_fd,(struct sockaddr*)&serv_addr,sizeof serv_addr);perror("bind");
    if (check_error == -1 ){return EXIT_FAILURE;}
    // printf("ahjefeejfejjjddjjdj\n");

    check_error = listen(server_fd,BUFSIZ);perror("listen");
    if (check_error == -1 ){return EXIT_FAILURE;}



    struct sockaddr_in client_addr;
    socklen_t len; 
    long int client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&len);perror("accept");
    if (client_fd == -1 || client_fd == 0){close(client_fd); close(server_fd); return EXIT_FAILURE; }



    while (1)
    {
        
  
    int choix;
    /*recoi le choix du joueur/client a t-il jouer pile ou face*/
    check_error = recv(client_fd,&choix,sizeof(int),0);perror("recv");
    if (check_error == -1 || check_error == 0){return EXIT_FAILURE;}

    /*affiche le choix pour verifier son contenu */
    // printf("%d\n",choix);
    srand(time(NULL));
    /*defini un rand soit 1 ou 2 dans ce cas*/
    int jeu = (float)rand()/RAND_MAX *2+1;   
  
    /*renvoie au client de qu'elle cote la piece est tombé*/
     if(jeu == PILE){
        
        char renvoie_jeu[]="Pile !\n";
        check_error = send(client_fd,renvoie_jeu,strlen(renvoie_jeu),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        
    }   
    /*renvoie au client de qu'elle cote la piece est tombé*/
    else if(jeu == FACE){
        char renvoie_jeu[]="Face !\n";
        check_error = send(client_fd,renvoie_jeu,strlen(renvoie_jeu),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
       
    }

    /*renvoie la phrase de victoire si la piece est tomber du bon coté*/
    if (choix == jeu)
    {
        printf("bravo\n");
        
        char phrase[] = "vous avez gagné, BRAVO!\n";
        check_error = send(client_fd,phrase,strlen(phrase),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        // printf("%s a gagner le point\n",p_name);
        

    }
    /*renvoie la phrase de defaite si la piece est tombée du mauvais coté*/
    else if(choix != jeu){
        printf("perdu\n");
        char phrase[] = "vous avez perdu, DOMMAGE!\n";
        check_error = send(client_fd,phrase,strlen(phrase),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        // printf("%s a perdu le point\n",p_name);
    }


    }
    return 0;
}



