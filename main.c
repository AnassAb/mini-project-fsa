#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "GestionVoiture.h"

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
        printf("\n\t\t\t\t\t---------------Menu Principal---------------\n");
        printf("\t\t\t\t\t============================================");
        printf("\n");
        printf("\t\t\t\t\tLocation...................................1\n");
        printf("\t\t\t\t\tGestion voitures...........................2\n");
        printf("\t\t\t\t\tGestion clients............................3\n");
        printf("\t\t\t\t\tQuitter....................................4\n");
        printf("\n");
        printf("\t\t\t\t\t============================================");
        printf("\n\t\t\t\t\t\t\t Votre choix: ");
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
        printf("\n\t\t\t\t\t---------------Location d'une voiture---------------\n");
        printf("\t\t\t\t\t====================================================");
        printf("\n");
        printf("\t\t\t\t\tVisualiser contrat.................................1\n");
        printf("\t\t\t\t\tLouer voiture......................................2\n");
        printf("\t\t\t\t\tRetourner voiture..................................3\n");
        printf("\t\t\t\t\tModifier contrat...................................4\n");
        printf("\t\t\t\t\tSupprimer contrat..................................5\n");
        printf("\t\t\t\t\tRetour.............................................6\n");
        printf("\n");
        printf("\t\t\t\t\t====================================================");
        printf("\n\t\t\t\t\t\t\t Votre choix: ");
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
        printf("\n\t\t\t\t\t---------------Gestion des Voitures---------------\n");
        printf("\t\t\t\t\t====================================================");
        printf("\n");
        printf("\t\t\t\t\tListe des voitures.................................1\n");
        printf("\t\t\t\t\tAjouter voiture....................................2\n");
        printf("\t\t\t\t\tModifier voiture...................................3\n");
        printf("\t\t\t\t\tSupprimer voiture..................................4\n");
        printf("\t\t\t\t\tRetour.............................................5\n");
        printf("\n");
        printf("\t\t\t\t\t====================================================");
        printf("\n\t\t\t\t\t\t\t Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                n = nbrVoiture(ficV);
                ListeVoitures(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 2:
                n = nbrVoiture(ficV);
                AjouterVoiture(ficV, n);
                printf("La voiture %d a %ct%c ajout%ce avec succ%cs!\n", n+1, 130,130,130,138); //Code ASCII: é : 130 - è : 138
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 3:
                n = nbrVoiture(ficV);
                ModifierVoiture(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
            case 4:
                n = nbrVoiture(ficV);
                SupprimerVoiture(ficV, n);
                printf("Appuyer sur une touche pour revenir au menu!\n");
                getch();
                break;
        }
    } while (x!=5);
}
void menu_gc (char *ficC) {
    int x;
    do {
        system("cls");
        printf("\n\t\t\t\t\t---------------Gestion des Clients---------------\n");
        printf("\t\t\t\t\t===================================================");
        printf("\n");
        printf("\t\t\t\t\tListe des clients.................................1\n");
        printf("\t\t\t\t\tAjouter client....................................2\n");
        printf("\t\t\t\t\tModifier client...................................3\n");
        printf("\t\t\t\t\tSupprimer client..................................4\n");
        printf("\t\t\t\t\tRetour............................................5\n");
        printf("\n");
        printf("\t\t\t\t\t====================================================");
        printf("\n\t\t\t\t\t\t\t Votre choix: ");
        scanf("%d", &x);
        switch (x) {
            case 1:
                printf("Liste des client");
                getch();
                break;
            case 2:
                printf("Ajouter client");
                getch();
                break;
            case 3:
                printf("Modifier client");
                getch();
                break;
            case 4:
                printf("Supprimer client");
                getch();
                break;
        }
    } while (x!=5);
}
