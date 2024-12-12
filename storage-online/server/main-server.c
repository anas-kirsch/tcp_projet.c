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
#include "../config.h"

int server_fd;


int main(){

    int server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");


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




    /*permet de recuperer en avance le nombre exact d'octet de l'image a recv */
    int sizeFile=0;
    check_error = recv(client_fd,&sizeFile,sizeof(int),0);perror("recv");
    if (check_error == -1 ){return EXIT_FAILURE;}
    printf("%d\n",sizeFile);


     
    /*recv l'image du client*/
    char image[sizeFile];memset(image,0,sizeFile);
    check_error = recv(client_fd,image,sizeFile,0);perror("recv");
    if (check_error == -1 ){return EXIT_FAILURE;}
    
    

    /*recv le nom du fichier image ou non, provient de l'entree terminal du client recuperer avec argv*/
    char filename[BUFSIZ];memset(filename,0,BUFSIZ);
    filename[strlen(filename)-1]=0;
    check_error = recv(client_fd,filename,BUFSIZ,0);perror("recv");
    if (check_error == -1){return EXIT_FAILURE;}    
    // printf("%d\n",check_error);    

    // printf("filename : %s\n",filename);


    for (int i = 0; filename[i] <255; i++) {
        printf("%c", filename[i]);
    }


    /*ouvre le fichier dans lequel le contenu va etre enregistrer et afficher */
    FILE* fd_image = fopen("voiture.jpeg","w+");perror("fopen");
    // fread(image,BUFSIZ,1,fd_image);
    // printf("ou est le beug\n"); 
    fwrite(image,sizeFile,1,fd_image);


    /*ouvre le fichier dans lequel vont etre lister les fichiers que le serveur possède*/
    FILE* list_file = fopen("liste-fichier.txt","a+");
    
    /* lire l'heure courante */ 
        time_t now = time (NULL);
        
        /* la convertir en heure locale */
        struct tm tm_now = *localtime (&now);
        
        /* Créer une chaine JJ/MM/AAAA HH:MM:SS */
        char s_now[sizeof "JJ/MM/AAAA HH:MM:SS" ];
        
        strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

        // FILE* liste = fopen("todoliste.txt","a+");
        fprintf(list_file,"[%s] %d %s \n",s_now,sizeFile,filename);/*recuper entrer bash file_name */
        fclose(list_file);perror("fclose");

    /*fichier qui va enregistrer les noms des fichiers recu la date/heure et sa taille */
    // char element[BUFSIZ];memset(element,0,BUFSIZ);
    
    



    return 0;
}