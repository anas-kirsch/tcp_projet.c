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
    int sizeFile = ftell(fd);
    rewind(fd); // Revenir au début du fichier
    printf("Taille du fichier : %d\n", sizeFile);

    // Envoyer la taille du fichier
    if (send(client_fd, &sizeFile, sizeof(int), 0) == -1) {
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
    char buffer[1024];
    int bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fd)) > 0) {
        int bytesSent = 0;
        while (bytesSent < bytesRead) {
            int sent = send(client_fd, buffer + bytesSent, bytesRead - bytesSent, 0);
            if (sent == -1) {
                perror("send (file fragment)");
                fclose(fd);
                return;
            }
            bytesSent += sent;
        }
    }

    printf("Fichier envoyé avec succès !\n");
    fclose(fd);
}
