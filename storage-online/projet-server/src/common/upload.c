#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"

void upload(int client_fd) {
    long long int sizeFile = 0;
    char filename[BUFSIZ] = {0};
    char chemin[BUFSIZ] = {0};

    // Recevoir la taille du fichier
    if (recv(client_fd, &sizeFile, sizeof(long long int), 0) <= 0) {
        perror("recv (sizeFile)");
        close(client_fd);
        return;
    }
    printf("Taille du fichier : %d\n", sizeFile);

    // Recevoir le nom du fichier
    if (recv(client_fd, filename, BUFSIZ, 0) <= 0) {
        perror("recv (filename)");
        close(client_fd);
        return;
    }
    printf("Nom du fichier : %s\n", filename);

    // Construire le chemin complet
    sprintf(chemin, "build/public/%s", filename);
    perror("sprintf");
    printf("Chemin : %s\n", chemin);

    // Ouvrir le fichier en mode écriture binaire
    FILE* fd_fichier = fopen(chemin, "wb");
    if (!fd_fichier) {
        perror("fopen");
        close(client_fd);
        return;
    }

    // Recevoir le fichier par fragments
    char* file= malloc(sizeFile);
    int bytesReceived = 0;
    while (bytesReceived < sizeFile) {
        int chunkSize = recv(client_fd, file, sizeof(file), 0);
        if (chunkSize <= 0) {
            perror("recv (file fragment)");
            fclose(fd_fichier);
            close(client_fd);
            return;
        }
        fwrite(file,1,chunkSize,fd_fichier);
        bytesReceived += chunkSize;
    }
    free(file);
    printf("Fichier reçu avec succès !\n");
    fclose(fd_fichier);

    // Mettre à jour la liste des fichiers
    FILE* list_file = fopen("build/bdd/liste-fichier.txt", "a");
    if (list_file) {
        time_t now = time(NULL);
        struct tm* tm_now = localtime(&now);
        char s_now[20];
        strftime(s_now, sizeof(s_now), "%d/%m/%Y %H:%M:%S", tm_now);
        fprintf(list_file, "[%s] %d %s\n", s_now, sizeFile, filename);
        fclose(list_file);
    } else {
        perror("fopen (liste-fichier)");
    }
}
