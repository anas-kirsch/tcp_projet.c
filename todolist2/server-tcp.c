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
#include <unistd.h>
#include <time.h>
#include "config.h"


int server_fd;

int main(){

    server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    if(server_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in server_addr =
    {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    int error = bind(server_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("bind");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }

    
    error = listen(server_fd,BUFSIZ);perror("listen");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }

    while (1)
    {
    

        struct sockaddr_in client_addr;
        socklen_t len;
        int client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&len);perror("accept");
        if(client_fd == -1) { close(client_fd); close(server_fd); return EXIT_FAILURE; }


        
        char choix[BUFSIZ];memset(choix,0,BUFSIZ);
        error = recv(client_fd,choix,BUFSIZ,0);perror("recv");
        int number_choice = atoi(choix);
        printf("%d\n",number_choice);


        switch (number_choice)
        {
        case 1:
            memset(choix,0,BUFSIZ);
            error = recv(client_fd,choix,BUFSIZ,0);perror("recv");
            if(error == -1){return EXIT_FAILURE;}

            
            /* lire l'heure courante */ 
            time_t now = time (NULL);
            
            /* la convertir en heure locale */
            struct tm tm_now = *localtime (&now);
            
            /* Créer une chaine JJ/MM/AAAA HH:MM:SS */
            char s_now[sizeof "JJ/MM/AAAA HH:MM:SS" ];
            
            strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

            FILE* todo_liste = fopen("todoliste.txt","a+");
            fprintf(todo_liste,"[%s] %s            \n",s_now,choix);
            fclose(todo_liste);perror("fclose");

        
            break;
        case 2:
            memset(choix,0,BUFSIZ);
            todo_liste = fopen("todoliste.txt","r");perror("fopen");
            // fgets(choix,BUFSIZ,todo_liste);
            fread(choix,1,BUFSIZ,todo_liste);

            error = send(client_fd,choix,BUFSIZ,0);perror("send");
            if(error == -1){return EXIT_FAILURE;}
            fclose(todo_liste);perror("fclose");
            break;
            
        case 3:
            memset(choix,0,BUFSIZ);
            char ligne[BUFSIZ];memset(ligne,0,BUFSIZ);
            todo_liste = fopen ("todoliste.txt","r+");
            recv(client_fd,choix,BUFSIZ,0);perror("recv");
            if(error == -1){return EXIT_FAILURE;}
            int ligne_valide = atoi(choix);
            fseek(todo_liste,0,SEEK_SET);
            printf("%s\n",choix);

            for (int i = 0; i < ligne_valide; i++)
            {
                fgets(ligne,BUFSIZ,todo_liste);
            }

                fseek(todo_liste,-10,SEEK_CUR);
                char* valider = " ✔️";

            
                fwrite(valider,1,strlen(valider),todo_liste);
                printf("%d : %s",strlen(ligne),ligne);

            
            break;
        default: 
            printf("Erreur, ressayer..\n");
            break;
        }

 break;
       
        // close(client_fd);
    }
    close(server_fd);
    return EXIT_FAILURE;

    return 0;
}



            
