#define SERVER_PORT 7002
#define CLIENT_PORT 5222



/*permet de commenter les fonctions et voir en passant la souris dessu*/

/**
 * 
 *
 */

/*serveur */


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <pthread.h>
// #include <errno.h>
// #include "config.h"
// int serveur_fd;



// /** 
//  * Fonction qui lance le chat et demande au client le message et envoie au serveur puis attend la reponse, le serveur renvoie tout message que le client lui renvoie
//  * @param void* arg - le client_fd doit etre un long int 
//  * @return void* rien du tout
//  */
// void* chat_thread(void* arg){
//     long int client_fd = (long int)arg;

//     while(1){

//         char reponse[BUFSIZ];memset(reponse,0,BUFSIZ);
//         recv(client_fd,reponse,BUFSIZ,0);perror("recv()");
//         printf("%s\n",reponse);


//         char envoie[BUFSIZ];memset(envoie,0,BUFSIZ);   
//         // fgets(envoie,BUFSIZ,stdin);


//         send(client_fd,envoie,BUFSIZ,0);perror("send()");



//     }
// }

// // void* recv_thread(){



// // }

// int main(){

//     /**
//      * 
//      */
//     serveur_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
//     if(serveur_fd == -1) return EXIT_FAILURE;

//     struct sockaddr_in addr =
//     {
//         .sin_family = AF_INET,
//         .sin_addr.s_addr = INADDR_ANY,
//         .sin_port = htons(SERVER_PORT)
//     };
    
//     int error = bind(serveur_fd,(struct sockaddr*)&addr,sizeof(addr));perror("bind()");
//     if(error == -1) return EXIT_FAILURE;

//     listen(serveur_fd,BUFSIZ);perror("listen()");
//     if(error == -1) return EXIT_FAILURE;

    

//     while (1)
//     {
//         struct sockaddr client_addr;
//         socklen_t len;
 
    
//         long int client_fd = accept(serveur_fd,&client_addr,&len);perror("accept()");
//         if(client_fd == -1) return EXIT_FAILURE;


//         pthread_t thread;
//         pthread_create(&thread,NULL,chat_thread,(void*)client_fd);perror("pthread_create");
//         if(thread == -1) return EXIT_FAILURE;



//     //  close(client_fd);perror("close()");

//     }
//     return 0;
// }






 /* client*/


//  #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <pthread.h>

// #include "config.h"
// int client_fd;

// int main(){

//     client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket()");
   
//     struct sockaddr_in addr =
//     {
//         .sin_family = AF_INET,
//         .sin_addr.s_addr = INADDR_ANY,
//         .sin_port = htons(CLIENT_PORT)
//     };
    
//     bind(client_fd,(struct sockaddr*)&addr, sizeof(addr));perror("blind()");
    

//     struct sockaddr_in serv_addr = 
//     {
//         .sin_family = AF_INET,
//         .sin_port = htons(SERVER_PORT),
//         .sin_addr.s_addr = inet_addr ("127.0.0.1")
//     };
    

//     connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));perror("connect()");

//     while(1){

//     char reponse[BUFSIZ];memset(reponse,0,BUFSIZ);
//     recv(client_fd,reponse,BUFSIZ,0);perror("recv()");
//     printf("%s\n",reponse);

//     char envoie[BUFSIZ];memset(reponse,0,BUFSIZ);
//     fgets(envoie,BUFSIZ,stdin);
//     send(client_fd,envoie,BUFSIZ,0);perror("send()");

//     }

//     // sleep(5);
//     close(client_fd);perror("close()");


//     return 0;
// }