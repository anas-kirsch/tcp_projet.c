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



void upload(int client_fd){


        int sizeFile=0;
        char filename[BUFSIZ];memset(filename,0,BUFSIZ);
        // char chemin[BUFSIZ+strlen("build/public/")-1];memset(chemin,0,BUFSIZ);/*recupere chemin vers les images ou texte*/
        char chemin[BUFSIZ];memset(chemin,0,BUFSIZ);
        char file[sizeFile];memset(file,0,sizeFile);

        char cmd_name[BUFSIZ];memset(cmd_name,0,BUFSIZ);
        

      
           /*permet de recuperer en avance le nombre exact d'octet de l'image a recv */
        int check_error = recv(client_fd,&sizeFile,sizeof(int),0);perror("recv");
        if (check_error == -1 ){return;}
        printf("%d\n",sizeFile);
        

        /*recv le nom du fichier image ou non, provient de l'entree terminal du client recuperer avec argv*/
        check_error = recv(client_fd,filename,BUFSIZ,0);perror("recv");
        if (check_error == -1){return;}
        printf("filename : %s\n",filename); 



        /*ouvre le fichier dans lequel vont etre lister les fichiers que le serveur possède*/
        FILE* list_file = fopen("build/bdd/liste-fichier.txt","a+");perror("fopen");
        
        /* lire l'heure courante */ 
            time_t now = time (NULL);
            
            /* la convertir en heure locale */
            struct tm tm_now = *localtime (&now);
            
            /* Créer une chaine JJ/MM/AAAA HH:MM:SS */
            char s_now[sizeof "JJ/MM/AAAA HH:MM:SS" ];
            
            strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);


            fprintf(list_file,"[%s] %d %s \n",s_now,sizeFile,filename);/*recuper entrer bash file_name */
            fclose(list_file);perror("fclose");
        
    
        // char element[BUFSIZ];memset(element,0,BUFSIZ);
        
        //  char chemin[BUFSIZ+strlen("build/public/")-1];
        sprintf(chemin,"build/public/%s",filename);perror("sprintf");/*colle deux chaine de caractere*/
        printf("chemin: %s\n",chemin);


        
        /*recv l'image ou fichier du client*/
        check_error = recv(client_fd,file,sizeFile,0);perror("recv");
        if (check_error == -1 ){return ;}

        /*ouvre le fichier dans lequel le contenu va etre enregistrer et afficher */
        FILE* fd_fichier = fopen(chemin,"w+");perror("fopen");
        // fread(image,BUFSIZ,1,fd_image);
        
        fseek(fd_fichier,0,SEEK_SET);
        fwrite(file,sizeFile,1,fd_fichier);perror("fwrite");




}