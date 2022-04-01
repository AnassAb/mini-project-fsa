#ifndef GESTIONVOITURE_H_INCLUDED
#define GESTIONVOITURE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#define MAX 1000
#define VSIZE 66

int idV_n(char *fichier, int idVoiture, int nbrV){
    FILE *fvoiture = NULL;
    int i;
    char str[5];
    int id, count, ln = -1;

    fvoiture = fopen(fichier, "r");
    if (fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    rewind(fvoiture);
    count = 0;
    for(i=0; i<nbrV; i++){
        fgets(str,5,fvoiture);
        id = atoi(str);
        count++;
        if(id == idVoiture){
            ln = count;
            break;
        }
        fseek(fvoiture,VSIZE-4,SEEK_CUR);
    }

    fclose(fvoiture);

    return ln;
}
void AfficherVoiture (char * fichier, int nbrV){
    FILE * fvoiture;
    int i;
    char car;

    fvoiture = fopen(fichier, "r");
    if (fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }
    fseek(fvoiture,VSIZE*(nbrV-1), SEEK_SET);
    printf("Voiture %d:\n", nbrV);
    printf("\tId: ");
    for(i=0; i<4;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tMarque: ");
    for(i=0; i<15;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tModele: ");
    for(i=0; i<15;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tCouleur: ");
    for(i=0; i<7;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tNombre de Places: ");
    for(i=0; i<2;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tPrix: ");
    for(i=0; i<12;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");
    fseek(fvoiture,1,SEEK_CUR);
    printf("\tEn Location: ");
    for(i=0; i<4;i++){
        car = fgetc(fvoiture);
        printf("%c", car);
    }
    printf("\n");

    fclose(fvoiture);

}
void ListeVoitures (char * fichier, int nombreVoiture){
    FILE* fvoiture = NULL;
    int n;

    fvoiture = fopen(fichier, "r");
    if (fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    for(n=1; n<=nombreVoiture; n++){
        AfficherVoiture(fichier,n);
    }

    fclose(fvoiture);

}
void AjouterVoiture (char *fichier, int n){
    FILE *fvoiture = NULL;
    Voiture V;
    int i, ln, lg;

    fvoiture = fopen(fichier, "a");
    if (fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    printf("Voiture %d:\n", n+1);
    do{
        printf("\tid: ");
        scanf("%d", &V.idVoiture);
        ln = idV_n(fichier, V.idVoiture, n);
        if(ln != -1)
            printf("L'id entr%c est d%cj%c utilis%c.\nVeuillez entrer une id unique!\n",130,130,133,130);
    }while(ln != -1);
    if (V.idVoiture< 10){
        fprintf(fvoiture,"%d   :",V.idVoiture);
    } else if (V.idVoiture < 100){
        fprintf(fvoiture,"%d  :",V.idVoiture);
    } else if (V.idVoiture < 1000){
        fprintf(fvoiture,"%d :",V.idVoiture);
    } else {
        fprintf(fvoiture,"%d:",V.idVoiture);
    }
    printf("\tMarque: ");
    scanf("%s", V.marque);
    lg = strlen(V.marque);
    if(lg < 15){
        for (i=lg; i<15; i++)
            strcat(V.marque, " ");
    }
    fprintf(fvoiture,"%s:",V.marque);
    printf("\tModele: ");
    scanf("%s", V.nomVoiture);
    lg = strlen(V.nomVoiture);
    if(lg < 15){
        for (i=lg; i<15; i++)
            strcat(V.nomVoiture, " ");
    }
    fprintf(fvoiture,"%s:",V.nomVoiture);
    printf("\tCouleur: ");
    scanf("%s", V.couleur);
    lg = strlen(V.couleur);
    if(lg < 7){
        for (i=lg; i<7; i++)
            strcat(V.marque, " ");
    }
    fprintf(fvoiture,"%s:",V.couleur);
    printf("\tNombre de places: ");
    scanf("%d", &V.nbplaces);
    if (V.nbplaces < 10){
        fprintf(fvoiture,"%d :",V.nbplaces);
    } else {
        fprintf(fvoiture,"%d:",V.nbplaces);
    }
    printf("\tPrix du jour: ");
    scanf("%d", &V.prixJour);
    if (V.prixJour < 100){
        fprintf(fvoiture,"%d DH/JOUR  :",V.prixJour);
    } else if (V.prixJour < 1000){
        fprintf(fvoiture,"%d DH/JOUR :",V.prixJour);
    } else {
        fprintf(fvoiture,"%d DH/JOUR:",V.prixJour);
    }
    printf("\tEn Location (Oui/Non): ");
    scanf("%s", V.EnLocation);
    lg = strlen(V.EnLocation);
    if(lg < 3){
        for (i=lg; i<3; i++)
            strcat(V.EnLocation, " ");
    }
    fprintf(fvoiture,"%s\n",V.EnLocation);

    fclose(fvoiture);

}
int ModifierVoiture(char *fichier, int n){
    FILE * fvoiture;
    FILE * ftmp;
    FILE * line;
    int id,ln,x;
    char chaine[MAX],nouveau[MAX];

    do{
        do{
            printf("Quelle voiture voulez vous modifier?\n");
            printf("Veuillez entrez son id (ou 0 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == 0) {return 0;}
            ln = idV_n(fichier, id, n);
            if( ln == -1)
                printf("Aucune voiture avec cet id!\n");
        }while(ln == -1);

        AfficherVoiture(fichier, ln);
        printf("Voulez vous modifier cette voiture?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    ln--;
    AjouterVoiture("modification.txt", ln);
    ln++;

    line = fopen("modification.txt", "r");
    if (line == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }
    fgets(nouveau, MAX, line);
    fclose(line);
    remove("modification.txt");

    fvoiture = fopen(fichier, "r");
    ftmp = fopen("ftmp.txt", "w");

    if (fvoiture == NULL || ftmp == NULL){
        printf("\nImpossible d'ouvrir le fichier.\n");
        exit(0);
    }

    int count = 0;
    while ((fgets(chaine, MAX, fvoiture)) != NULL){
        count++;
        if (count == ln){
            fputs(nouveau, ftmp);
        }else
            fputs(chaine, ftmp);
    }
    fclose(fvoiture);
    fclose(ftmp);

    int res1, res2;
    res1 = remove(fichier);
    res2 = rename("ftmp.txt",fichier);

    if ( res1 == 0 && res2 == 0)
        printf("La voiture %d a %ct%c modifi%ce avec succ%cs!\n", ln, 130,130,130,138); //Code ASCII: � : 130 - � : 138
    else
        printf("ERREUR: la voiture n'a pas pu %ctre modifi%ce!\n",136,130);

    return 1;
}
int SupprimerVoiture (char *fichier, int n){
    FILE * fvoiture;
    FILE * ftmp;

    int x, ln, id, count;
    char chaine[MAX];

    do{
        do{
            printf("Quelle voiture voulez vous supprimer?\n");
            printf("Veuillez entrez son id (ou 0 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == 0) {return 0;}
            ln = idV_n(fichier, id, n);
            if( ln == -1){ printf("Aucune voiture avec cet id!\n"); }
        }while(ln == -1);
        AfficherVoiture(fichier, ln);
        printf("Voulez vous supprimer cette voiture?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3) return 0;

    }while(x != 1 );

    fvoiture = fopen(fichier, "r");
    ftmp = fopen("ftmp.txt", "w");

    if (fvoiture == NULL || ftmp == NULL){
        printf("\nImpossible d'ouvrir le fichier.\n");
        exit(0);
    }

    count = 0;
    while ((fgets(chaine, MAX, fvoiture)) != NULL){
        count++;
        if (count == ln)
            fputs("", ftmp);
        else
            fputs(chaine, ftmp);
    }

    fclose(fvoiture);
    fclose(ftmp);
    int res1, res2;
    res1 = remove(fichier);
    res2 = rename("ftmp.txt", fichier);
    if ( res1 == 0 && res2 == 0)
        printf("La voiture %d a %ct%c supprim%ce avec succ%cs!\n", ln, 130,130,130,138); //Code ASCII: � : 130 - � : 138
    else
        printf("ERREUR: la voiture n'a pas pu %ctre supprim%ce!\n",136,130);
    return 1;
}
int nbrVoiture (char *fichier){
    FILE * fvoiture;
    char chaine[MAX];
    int count = 0;

    fvoiture = fopen(fichier, "r");
    if (fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    while(fgets(chaine, MAX, fvoiture) != NULL){
        count++;
    }

    fclose(fvoiture);

    return count;
}

#endif // GESTIONVOITURE_H_INCLUDED
