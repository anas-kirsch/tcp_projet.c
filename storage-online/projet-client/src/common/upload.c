#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../../../module/config.h"

int client_fd;

void upload(char* cmd) {
    printf("cmd : %s\n", cmd);

    // Construire le chemin
    char path[BUFSIZ + strlen("build/public/")];
    sprintf(path, "build/public/%s", cmd);
    perror("sprintf");
    printf("path : %s\n", path);

    // Ouvrir le fichier
    FILE* fd = fopen(path, "rb"); // "rb" pour mode binaire
    if (!fd) {
        perror("fopen");
        return;
    }

    // Récupérer la taille du fichier
    fseek(fd, 0, SEEK_END);
    long long int sizeFile = ftell(fd);
    printf("taille fichier : %lld\n",sizeFile);
    rewind(fd); // Revenir au début du fichier

    // Envoyer la taille du fichier
    if (send(client_fd, &sizeFile, sizeof(long long int), 0) == -1) {
        perror("send (sizeFile)");
        fclose(fd);
        return;
    }

    // Envoyer le nom du fichier avec un '\0'
    if (send(client_fd, cmd, strlen(cmd) + 1, 0) == -1) {
        perror("send (filename)");
        fclose(fd);
        return;
    }

    // Envoyer le fichier par fragments
    char* buffer= malloc(sizeFile);
    long long int bytesRead = 0;


    while ((bytesRead = fread(buffer, 1, sizeFile, fd)) > 0) {
    long long int bytesSent = 0;
        perror("fread");
            printf("bytes read: %lld\n",bytesRead);

        while (bytesSent < bytesRead) {
            printf("bytessent : %lld\n",bytesSent);
            int sent = send(client_fd, buffer + bytesSent, bytesRead - bytesSent, 0);perror("send");
            if (sent == -1) {
                perror("send (file fragment)");
                fclose(fd);
                return;
            }
            bytesSent += sent;
        }
    }
    free(buffer);

    printf("Fichier envoyé avec succès !\n");
    fclose(fd);
}
