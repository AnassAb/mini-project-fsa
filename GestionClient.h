#ifndef GESTIONCLIENT_H_INCLUDED
#define GESTIONCLIENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#define MAX 1000
#define CSIZE 125

int idC_n(char *fichier, int idClient, int nbrC){
    FILE *fclient = NULL;
    int i;
    char str[5];
    int id, count, ln = -1;

    fclient = fopen(fichier, "r");
    if (fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    rewind(fclient);
    count = 0;
    for(i=0; i<nbrC; i++){
        fgets(str,5,fclient);
        id = atoi(str);
        count++;
        if(id == idClient){
            ln = count;
            break;
        }
        fseek(fclient,CSIZE-4,SEEK_CUR);
    }

    fclose(fclient);

    return ln;
}
void AfficherClient (char * fichier, int nbrV){
    FILE * fclient;
    int i;
    char car;

    fclient = fopen(fichier, "r");
    if (fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }
    fseek(fclient,CSIZE*(nbrV-1), SEEK_SET);
    printf("Client %d:\n", nbrV);
    printf("\tId: ");
    for(i=0; i<4;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");
    fseek(fclient,1,SEEK_CUR);
    printf("\tNom: ");
    for(i=0; i<20;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");
    fseek(fclient,1,SEEK_CUR);
    printf("\tPr%cnom: ", 130);
    for(i=0; i<20;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");
    fseek(fclient,1,SEEK_CUR);
    printf("\tCIN: ");
    for(i=0; i<10;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");
    fseek(fclient,1,SEEK_CUR);
    printf("\tAdresse: ");
    for(i=0; i<54;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");
    fseek(fclient,1,SEEK_CUR);
    printf("\tTelephone: ");
    for(i=0; i<10;i++){
        car = fgetc(fclient);
        printf("%c", car);
    }
    printf("\n");


    fclose(fclient);

}
void ListeClient (char * fichier, int nombreClient){
    FILE* fclient = NULL;
    int n;

    fclient = fopen(fichier, "r");
    if (fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    for(n=1; n<=nombreClient; n++){
        AfficherClient(fichier,n);
    }

    fclose(fclient);

}
void AjouterClient (char *fichier, int n){
    FILE *fclient = NULL;
    Client C;
    int i, ln, lg;

    fclient = fopen(fichier, "a");
    if (fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    printf("Client %d:\n", n+1);
    do{
        printf("\tid: ");
        scanf("%d", &C.idClient);
        ln = idC_n(fichier, C.idClient, n);
        if(ln != -1)
            printf("L'id entr%c est d%cj%c utilis%c.\nVeuillez entrer une id unique!\n",130,130,133,130);
    }while(ln != -1);
    if (C.idClient< 10){
        fprintf(fclient,"%d   :",C.idClient);
    } else if (C.idClient < 100){
        fprintf(fclient,"%d  :",C.idClient);
    } else if (C.idClient < 1000){
        fprintf(fclient,"%d :",C.idClient);
    } else {
        fprintf(fclient,"%d:",C.idClient);
    }
    printf("\tNom: ");
    scanf("%s", C.nom);
    lg = strlen(C.nom);
    if(lg < 20){
        for (i=lg; i<20; i++)
            strcat(C.nom, " ");
    }
    fprintf(fclient,"%s:",C.nom);
    printf("\tPr%cnom: ",130);
    scanf("%s", C.prenom);
    lg = strlen(C.prenom);
    if(lg < 20){
        for (i=lg; i<20; i++)
            strcat(C.prenom, " ");
    }
    fprintf(fclient,"%s:",C.prenom);
    printf("\tCIN: ");
    scanf("%s", C.cin);
    lg = strlen(C.cin);
    if(lg < 10){
        for (i=lg; i<10; i++)
            strcat(C.cin, " ");
    }
    fprintf(fclient,"%s:",C.cin);
    printf("\tAdresse: ");
    fflush(stdin);
    fgets(C.adresse,54,stdin);
    lg = strlen(C.adresse);
    C.adresse[lg-1] = '\0';
    lg = strlen(C.adresse);
    if(lg < 54){
        for (i=lg; i<54; i++)
            strcat(C.adresse, " ");
    }
    fprintf(fclient, "%s:", C.adresse);
    printf("\tTelephone (ex: 0666666666): ");
    scanf("%d", &C.telephone);
    fprintf(fclient,"0%d\n",C.telephone);

    fclose(fclient);


}
int ModifierClient(char *fichier, int n){
    FILE * fclient;
    FILE * ftmp;
    FILE * line;
    int id,ln,x;
    char chaine[MAX],nouveau[MAX];

    do{
        do{
            printf("Quel client voulez vous modifier?\n");
            printf("Veuillez entrez son id (ou 0 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == 0) {return 0;}
            ln = idC_n(fichier, id, n);
            if( ln == -1)
                printf("Aucun client avec cet id!\n");
        }while(ln == -1);

        AfficherClient(fichier, ln);
        printf("Voulez vous modifier ce client?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    ln--;
    AjouterClient("modification.txt", ln);
    ln++;

    line = fopen("modification.txt", "r");
    if (line == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }
    fgets(nouveau, MAX, line);
    fclose(line);
    remove("modification.txt");

    fclient = fopen(fichier, "r");
    ftmp = fopen("ftmp.txt", "w");

    if (fclient == NULL || ftmp == NULL){
        printf("\nImpossible d'ouvrir le fichier.\n");
        exit(EXIT_SUCCESS);
    }

    int count = 0;
    while ((fgets(chaine, MAX, fclient)) != NULL){
        count++;
        if (count == ln){
            fputs(nouveau, ftmp);
        }else
            fputs(chaine, ftmp);
    }
    fclose(fclient);
    fclose(ftmp);

    int res1, res2;
    res1 = remove(fichier);
    res2 = rename("ftmp.txt",fichier);

    if ( res1 == 0 && res2 == 0)
        printf("Le client %d a %ct%c modifi%c avec succ%cs!\n", ln, 130,130,130,138); //Code ASCII: � : 130 - � : 138
    else
        printf("ERREUR: le client n'a pas pu %ctre modifi%c!\n",136,130);

    return 1;
}
int SupprimerClient (char *fichier, int n){
    FILE * fclient;
    FILE * ftmp;

    int x, ln, id, count;
    char chaine[MAX];

    do{
        do{
            printf("Quel client voulez vous supprimer?\n");
            printf("Veuillez entrez son id (ou 0 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == 0) {return 0;}
            ln = idC_n(fichier, id, n);
            if( ln == -1){ printf("Aucun client avec cet id!\n"); }
        }while(ln == -1);
        AfficherClient(fichier, ln);
        printf("Voulez vous supprimer ce client?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3) return 0;

    }while(x != 1 );

    fclient = fopen(fichier, "r");
    ftmp = fopen("ftmp.txt", "w");

    if (fclient == NULL || ftmp == NULL){
        printf("\nImpossible d'ouvrir le fichier.\n");
        exit(0);
    }

    count = 0;
    while ((fgets(chaine, MAX, fclient)) != NULL){
        count++;
        if (count == ln)
            fputs("", ftmp);
        else
            fputs(chaine, ftmp);
    }

    fclose(fclient);
    fclose(ftmp);
    int res1, res2;
    res1 = remove(fichier);
    res2 = rename("ftmp.txt", fichier);
    if ( res1 == 0 && res2 == 0)
        printf("Le client %d a %ct%c supprim%c avec succ%cs!\n", ln, 130,130,130,138); //Code ASCII: � : 130 - � : 138
    else
        printf("ERREUR: le client n'a pas pu %ctre supprim%c!\n",136,130);
    return 1;
}
int nbrClient (char *fichier){
    FILE * fclient;
    char chaine[MAX];
    int count = 0;

    fclient = fopen(fichier, "r");
    if (fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir le fichier!\n");
        exit(0);
    }

    while(fgets(chaine, MAX, fclient) != NULL){
        count++;
    }

    fclose(fclient);

    return count;
}


#endif // GESTIONCLIENT_H_INCLUDED

