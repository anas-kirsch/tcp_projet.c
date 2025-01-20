
Projet STORAGE ONLINE

Voici mon projet TCP en langage C nommé Storage Online, il permet à un cient de se connecter à un serveur afin de stocker des fichier de son choix dans celui ci. Avec ces fichiers il peux executer plusieurs fonctionnaité notamment UPLOAD, DOWNLOAD, DELETE ET LIST et cela en entrant la commande dans le terminale et en y ajoutant le nom du fichier qu'il souhaite envoyer, recevoir, supprimer, et si le client à oublier qu'elle fichier sont stocker dans le serveur parmis ceux qu'il a déjà ulpoad, il peux afficher la liste des fichiers enregistrer parmis les commandes énnoncer precédemment.


A quoi servent les différentes commande: 

UPLOAD : le client peux envoyer un fichier qu'il possède afin qu'il soit stocker dans le serveur, après ca il pourra supprimer la copie qu'il possède de son coté.
DOWNLOAD : le client peux télécharger le fichier de son choix qui est actuellement stocker coté serveur en recevant une copie(le fichier reste toujours coté serveur).
LIST : le client à oublier les fichiers qui sont stocker coté serveur, il peux afficher la liste des fichiers afin de choisir celui qu'il veux télécharger ou autre.
DELETE : le client choisi le fichier qu'il veux supprimer coté serveur afin de nettoyer son cloud ou autre.

Pour utiliser ces fonctionnalitées le client doit entrer le nom de la commande suivie du nom du fichier(sauf pour LIST) par exemple: UPLOAD image.png

A savoir qu'une fois que le cient a entrer sa commande la connexion s'effectue le temps de l'execution puis elle se coupe automatiquement.


Ce projet à été optimiser afin de permettre le transfert dans de fichier sans limite de taille, et cela à une vitesse optimisé selon votre situation, en local moins de 5 secondes, et en réseau cela varie de la connexion internet de l'utilsateur et de la taille du fichier. 

Vous pouvez retrouver sur ce repo un use case qui peux etre plus clair pour comprendre l'utilisation et utiliser ce service proposé. 

