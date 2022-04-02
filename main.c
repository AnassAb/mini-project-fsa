#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "GestionVoiture.h"
#include "GestionClient.h"
//Prototype des fonctions menu

void menu_principal (char *ficV, char *ficC, char *ficCL);
void menu_loc(char *ficCL);//Location d'une voiture // CL: Contrats Locations
void menu_gv (char *ficV);//gv: gestion des voitures
void menu_gc (char *ficC);//gc: gestion des clients

//Programme principal
int main () {
    char *fichierVoitures, *fichierClients, *fichierContrats;
    fichierVoitures = "Voitures.txt";
    fichierClients = "Clients.txt";
    fichierContrats = "ContratsLocations.txt";
    menu_principal(fichierVoitures, fichierClients, fichierContrats);
    return 0;
}

void menu_principal (char *ficV, char *ficC, char *ficCL) {
    int x;
    do {
        system("cls");
        printf("\n \t\t\t\t\t\t  \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n \t\t\t\t\t\t  \xb3 Menu Principal  \xb3");
        printf("\n \t\t\t\t\t\t  \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n \t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xba\tLocation..............................1        \xba");
        printf("\n \t\t\t\t\xba\tGestion voitures......................2        \xba");
        printf("\n \t\t\t\t\xba\tGestion clients.......................3        \xba");
        printf("\n \t\t\t\t\xba\tQuitter...............................4        \xba");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n\t\t\t\t\t\t    Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                menu_loc(ficCL);
                break;
            case 2:
                menu_gv(ficV);
                break;
            case 3:
                menu_gc(ficC);
                break;
        }
    } while (x!=4);
}
void menu_loc (char *ficCL) {
    int x;
    do {
        system("cls");
        printf("\n \t\t\t\t\t      \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n \t\t\t\t\t      \xb3 Location d'une voiture  \xb3");
        printf("\n \t\t\t\t\t      \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n \t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xba\tVisualiser un contrat.................1        \xba");
        printf("\n \t\t\t\t\xba\tLouer une voiture.....................2        \xba");
        printf("\n \t\t\t\t\xba\tRetourner une voiture.................3        \xba");
        printf("\n \t\t\t\t\xba\tModifier un contrat...................4        \xba");
        printf("\n \t\t\t\t\xba\tSupprimer un contrat..................5        \xba");
        printf("\n \t\t\t\t\xba\tRetour................................6        \xba");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n\t\t\t\t\t\t    Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                printf("Visualiser contrat");
                getch();
                break;
            case 2:
                printf("Louer voiture");
                getch();
                break;
            case 3:
                printf("Retourner voiture");
                getch();
                break;
            case 4:
                printf("Modifier contrat");
                getch();
                break;
            case 5:
                printf("Supprimer contrat");
                getch();
                break;
        }
    } while (x!=6);
}
void menu_gv (char *ficV) {
    int x, n;
    do {
        system("cls");
        printf("\n \t\t\t\t\t\t \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n \t\t\t\t\t\t \xb3 Gestion des Voitures  \xb3");
        printf("\n \t\t\t\t\t\t \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n \t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xba\tListe des voitures....................1        \xba");
        printf("\n \t\t\t\t\xba\tAjouter une voiture...................2        \xba");
        printf("\n \t\t\t\t\xba\tModifier une voiture..................3        \xba");
        printf("\n \t\t\t\t\xba\tSupprimer une voiture.................4        \xba");
        printf("\n \t\t\t\t\xba\tRetour................................5        \xba");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n\t\t\t\t\t\t    Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                system("cls");
                n = nbrVoiture(ficV);
                ListeVoitures(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                system("cls");
                n = nbrVoiture(ficV);
                AjouterVoiture(ficV, n);
                printf("La voiture %d a %ct%c ajout%ce avec succ%cs!\n", n+1, 130,130,130,138); //Code ASCII: é : 130 - è : 138
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                system("cls");
                n = nbrVoiture(ficV);
                ModifierVoiture(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                system("cls");
                n = nbrVoiture(ficV);
                SupprimerVoiture(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }
    } while (x!=5);
}
void menu_gc (char *ficC) {
    int x, n;
    do {
        system("cls");
        printf("\n \t\t\t\t\t\t \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n \t\t\t\t\t\t \xb3 Gestion des Clients  \xb3");
        printf("\n \t\t\t\t\t\t \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n \t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xba\tListe des clients.....................1        \xba");
        printf("\n \t\t\t\t\xba\tAjouter un client.....................2        \xba");
        printf("\n \t\t\t\t\xba\tModifier un client....................3        \xba");
        printf("\n \t\t\t\t\xba\tSupprimer un client...................4        \xba");
        printf("\n \t\t\t\t\xba\tRetour................................5        \xba");
        printf("\n \t\t\t\t\xba\t\t\t\t\t\t       \xba");
        printf("\n \t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n\t\t\t\t\t\t    Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                system("cls");
                n = nbrClient(ficC);
                ListeClient(ficC,n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                system("cls");
                n = nbrClient(ficC);
                AjouterClient(ficC,n);
                printf("Le client %d a %ct%c ajout%c avec succ%cs!\n", n+1, 130,130,130,138); //Code ASCII: é : 130 - è : 138
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                system("cls");
                n = nbrClient(ficC);
                ModifierClient(ficC,n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                system("cls");
                n = nbrClient(ficC);
                SupprimerClient(ficC,n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }
    } while (x!=5);
}
