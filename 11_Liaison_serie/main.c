/* Programme de test de la liaison série via un adaptateur USB série
   Vitesse de transmission 115200 bauds avec ECHO
   Ce programme renvoie le nb de caractères reçus et le message
   tant que le message reçu est différent de bye

*/

#include <stdio.h>
#include <stdlib.h>
#include "serie.h"

int main(int argc, char** argv) {

    int fdSerie;
    char message[1000];
    int nb = 0;
    int vitesse = 115200;
    char device[]="/dev/ttyS0";

    fdSerie = OuvrirPort(device);
    configurerSerie(fdSerie, vitesse, ECHO);
    viderBuffer(fdSerie);
    printf("%s Vitesse : %s\n", device, obtenirVitesse(fdSerie));

    // reception de message avec echo des caractères reçus
    do{
        nb = recevoirMessage(fdSerie, message,'\r' );
        printf("%d caractères reçus : %s\n", nb, message);
        envoyerMessage(fdSerie, "\r\nVotre message :");
        envoyerMessage(fdSerie, message);
        envoyerMessage(fdSerie,"\n");
    }
    while(strncmp(message, "bye", 3));
    // tant que le message reçu est différent de bye

    fermerPort(fdSerie);
    printf("la liaison série %s est fermée\n", device);
    return (EXIT_SUCCESS);
}

