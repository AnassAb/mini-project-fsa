#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "GestionVoitures.h"
#include "GestionClients.h"
#include "LocationVoiture.h"

//Prototype des fonctions menu

void menu_principal (char *ficV, char *ficC, char *ficCL);
void menu_loc(char *ficCL, char *ficC, char *ficV);//Location d'une voiture // CL: Contrats Locations
void menu_gv (char *ficV);//gv: gestion des voitures
void menu_gc (char *ficC);//gc: gestion des clients

//Programme principal
int main () {
    char *fichierVoitures, *fichierClients, *fichierContrats;
    fichierVoitures = "Voitures.dat";
    fichierClients = "Clients.dat";
    fichierContrats = "ContratsLocations.dat";
    menu_principal(fichierVoitures, fichierClients, fichierContrats);
    return 0;
}

void menu_principal (char *ficV, char *ficC, char *ficCL){
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
                menu_loc(ficCL, ficC, ficV);
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
void menu_loc (char *ficCL, char *ficC, char *ficV) {
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
                system("cls");
                //ListeContrats(ficCL);
                VisualiserContrat(ficCL);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                system("cls");
                LouerVoiture(ficCL, ficC, ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                system("cls");
                RetournerVoiture(ficCL,ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                system("cls");
                ModifierContrat(ficCL, ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 5:
                system("cls");
                SupprimerContrat(ficCL, ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }
    } while (x!=6);
}
void menu_gv (char *ficV) {
    int x;
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
                ListeVoitures(ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                system("cls");
                AjouterVoiture(ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                system("cls");
                ModifierVoiture(ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                system("cls");
                SupprimerVoiture(ficV);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }
    } while (x!=5);
}
void menu_gc (char *ficC) {
    int x;
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
                ListeClients(ficC);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                system("cls");
                printf("Entrez les informations du client:\n");
                AjouterClient(ficC);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                system("cls");
                ModifierClient(ficC);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                system("cls");
                SupprimerClient(ficC);
                printf("\nAppuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }

    }while(x!=5);
}
