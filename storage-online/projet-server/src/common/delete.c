#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "../../../module/config.h"

int client_fd;

void delete(int client_fd){

    char filename[BUFSIZ];memset(filename,0,BUFSIZ);

    int check_error = recv(client_fd,filename,BUFSIZ,0);perror("recv");
    if (check_error == -1){return;}

    printf("filename : %s\n",filename);

    char pathname[BUFSIZ];memset(pathname,0,BUFSIZ);
    sprintf(pathname,"build/public/%s",filename);perror("sprintf");

    int access(const char *pathname, int mode);perror("access");

    remove(pathname);perror("remove");


///////


// Ouverture du fichier en mode lecture et écriture
    FILE *file = fopen("./build/bdd/liste-fichier.txt", "r+");perror("fopen");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char line[BUFSIZ];
    long pos;
    int found = 0;

    // Parcours du fichier ligne par ligne pour trouver la ligne à supprimer
    while (fgets(line, sizeof(line), file)) {
        pos = ftell(file);  // Sauvegarde la position actuelle du curseur dans le fichier
        
        // Vérifie si le nom du fichier à supprimer est trouvé dans la ligne
        if (strstr(line, filename) != NULL) {
            found = 1;  // Ligne à supprimer trouvée
            break;
        }
    }

    // Si la ligne n'a pas été trouvée
    if (!found) {
        printf("Le fichier %s n'a pas été trouvé dans la liste.\n", filename);
        fclose(file);
        return;
    }

    // Déplacement du curseur à la position où la ligne à supprimer commence
    fseek(file, pos, SEEK_SET);

    // Lecture de la suite du fichier et réécriture du contenu à partir de la position actuelle
    FILE *temp = fopen("temp.txt", "w+");  // On va réécrire à partir de la ligne supprimée
    if (temp == NULL) {
        perror("fopen temp.txt");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        fputs(line, temp);
    }

    // Revenir au début du fichier et réécrire sans la ligne supprimée
    freopen("./build/bdd/liste-fichier.txt", "w", file);perror("freopen");  // Ouvre à nouveau le fichier en mode écriture pour remplacer son contenu
    fseek(temp, 0, SEEK_SET);  // Déplace le curseur du fichier temporaire au début
    while (fgets(line, sizeof(line), temp)) {
        fputs(line, file);
    }

    // Fermeture des fichiers
    fclose(file);
    fclose(temp);




}