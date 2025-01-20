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
#include <ctype.h>
#include "config.h"
#define PILE 1
#define FACE 2
#define QUITTER 3
#define DISCONNECTED 0
#define ERROR -1
int client_fd;
int choice = 0;
char choix[BUFSIZ];
char p_name[BUFSIZ];
int score = 0;


int main(){

    client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if (client_fd == -1){return EXIT_FAILURE;}
    
    struct sockaddr_in client_addr = {
    
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };
    
    int check_error = bind(client_fd,(struct sockaddr*)&client_addr,sizeof client_addr);perror("bind");
    if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}

    struct sockaddr_in server_addr = {

        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    check_error = connect(client_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("connect");
    if(check_error == -1 ) { close(client_fd); return EXIT_FAILURE; }

    /*demande le nom du joueur */
    printf("-----------------------------------\n");
    printf("Bienvenue\n");
    printf("Entrez le nom du joueur \n");
    printf("3. Quitter\n");
    printf("-----------------------------------\n");
    
        /*permet d'entrer le nom du joueur */
        memset(p_name,0,BUFSIZ);
        fgets(p_name,BUFSIZ,stdin);/*entre le nom du joueur */
        p_name[strlen(p_name)-1]=0;
        // atoi(p_name);
    if (atoi(p_name) == 3)
    {
        // close(client_fd);perror("close");
        return EIO;
    }
    


    while (1)
    {   
        printf("bienvenue %s !\n",p_name);
        /*presente le jeu et propose les choix possibles*/
        printf("-----------------------------------\n");
        printf("------------ PILE OU FACE ------------\n");
        printf("Que veux tu jouer pile ou face ?\n");
        printf("1 pour pile\n");
        printf("2 pour face\n");
        printf("3. Quitter\n");
        printf("-----------------------------------\n");

        /*entrée utilisateur, que veut il jouer? */
        memset(choix,0,BUFSIZ);
        fgets(choix,BUFSIZ,stdin);
        choix[strlen(choix)-1]=0;
        choice = atoi(choix);
        check_error= send(client_fd,&choice,sizeof(int),0);perror("send");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        
        if (choice == 3)
        {
        // close(client_fd);perror("close");
            return EIO;
        }

        /*affichele choix du joueur */
        if (choice == PILE)  
        {                           
            printf("Vous faite PILE !\n");  
        }                                               
        else if (choice == FACE) 
        {                                                       
            printf("Vous faite FACE !\n"); 
        }                            

        if (choice == 3)    
        {                                   
            printf("vous quittez le jeu...\n"); 
            break;
        }        

        /*wait*/
        printf("La piece est jetée\n");
        printf("3...\n");
        sleep(1);
        printf("2..\n");
        sleep(1);
        printf("1.\n");
        sleep(1);

        /*recoi qu'elle cote de la piece est tombe*/
        char cote[BUFSIZ];memset(cote,0,BUFSIZ);
        check_error = recv(client_fd,cote,BUFSIZ,0);perror("recv");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        printf("%s\n",cote);

        
        /*recoi le resultat gagné ou perdu*/
        char result[BUFSIZ];memset(result,0,BUFSIZ);
        check_error = recv(client_fd,result,BUFSIZ,0);perror("recv");
        if (check_error == -1  ){  close(client_fd);return EXIT_FAILURE;}
        printf("%s\n",result);
    
        
        
    }
    

    close(client_fd);perror("close");
    return EXIT_FAILURE;

    return 0;
}
