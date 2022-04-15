#ifndef GESTIONVOITURES_H_INCLUDED
#define GESTIONVOITURES_H_INCLUDED

//Calcule Le nombre de voitures enregistrer dans un fichier
int V_ArraySize (char *fname){
    FILE *fvoiture;
    voiture V;
    int c=0; //c = SIZE_Variable

    fvoiture = fopen(fname, "rb");
    if(fvoiture == NULL){
        return 0;
    }

    while(fread(&V, sizeof(voiture), 1, fvoiture)){
        c++;
    }

    fclose(fvoiture);

    return c;
}
//Recuperer Les informations sur les voitures
voiture * V_ExtractData (char * fname){
    FILE *fvoiture;
    voiture *TV, V; //TV: Tableau Voiture
    int c=0;

    fvoiture = fopen(fname, "rb");
    if(fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    TV = (voiture *) malloc(sizeof(voiture));
    while(fread(&V, sizeof(voiture), 1, fvoiture)){
        TV[c] = V;
        c++;
        TV = (voiture *) realloc(TV,(c+1)*sizeof(voiture));
    }

    fclose(fvoiture);

    return TV;

}
//Trouver La voiture par Id
int V_FindId (char *fname, int id){
    voiture *TABV;
    int i, N;

    TABV = V_ExtractData(fname);
    N = V_ArraySize(fname);

    for(i=0; i<N; i++){
        if (TABV[i].idVoiture == id){
            return i;
        }
    }

    return -2;
}
void AfficherVoiture (voiture V){
    printf("Voiture ID: %d\n", V.idVoiture);
    printf("\tMarque: %s\n",V.marque);
    printf("\tNom: %s\n",V.nomVoiture);
    printf("\tCouleur: %s\n",V.couleur);
    printf("\tNombre de places: %d\n",V.nbplaces);
    printf("\tPrix par jour: %d DH/JOUR\n",V.prixJour);
    printf("\tEn Location: %s\n",V.EnLocation);
}
void AjouterVoiture(char * fname){
    FILE *fvoiture;
    voiture V;
    int lg,i;

    fvoiture = fopen(fname, "ab");
    if(fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    printf("Entrez les informations de la voiture:\n");

    //Tester si l'id entre est unique
    do{
        srand(time(NULL));
        V.idVoiture = rand() % (10000 - 0 + 1) + 0; //n = rand() % (max - min + 1) + min;
        i = V_FindId(fname, V.idVoiture);
    }while(i != -2);

    printf("Voiture ID: %d\n", V.idVoiture);

    printf("\tMarque: ");
    fflush(stdin);
    fgets(V.marque, 15, stdin); //La marque peut etre un nom compose
    lg = strlen(V.marque);
    V.marque[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

    printf("\tNom: ");
    fflush(stdin);
    fgets(V.nomVoiture, 15, stdin);
    lg = strlen(V.nomVoiture);
    V.nomVoiture[lg-1] = '\0';

    printf("\tCouleur: ");
    scanf("%s",V.couleur);

    printf("\tNombre de places: ");
    scanf("%d",&V.nbplaces);

    printf("\tPrix par jour: ");
    scanf("%d",&V.prixJour);

    /*printf("\tEst ce qu'il est en location? ( Oui || Non )\n");
    printf("\tVotre choix: ");
    scanf("%s",V.EnLocation);*/
    //L'etat enLocation est determine automatiquement
    //Si la voiture est louer (menu location) il egale a Oui
    //Sinon il egale a Non et par defaut il egale a Non

    strcpy(V.EnLocation,"Non");

    fwrite(&V,sizeof(voiture), 1, fvoiture);

    fclose(fvoiture);

    printf("La voiture a %ct%c ajout%ce avec succ%cs!\n", 130,130,130,138);

}
void ListeVoitures (char *fname){
    FILE *fvoiture;
    voiture V;
    int c=0, N;

    fvoiture = fopen(fname, "rb");
    if(fvoiture == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = V_ArraySize(fname);
    if(N == 0){
        printf("Aucune voiture n'a %ct%c ajout%ce.\nVeuillez ajouter des voitures\n", 130,130, 130);
    }else{
        while(fread(&V, sizeof(voiture), 1, fvoiture)){
            AfficherVoiture(V);
            c++;
        }

        fclose(fvoiture);
    }

}
int ModifierVoiture (char * fname){
    FILE * ftmp = NULL;
    voiture *TABV;
    int x, i, id, lg, N;

    TABV = V_ExtractData(fname);

    do{
        do{
            printf("Quelle voiture voulez vous modifier?\n");
            printf("Veuillez entrez son id (ou -1 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == -1) {return 0;}
            i = V_FindId(fname,id);
            if( i == -2)
                printf("Aucune voiture avec cet id!\n");
        }while(i == -2);

        AfficherVoiture(TABV[i]);

        printf("Voulez vous modifier cette voiture?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    printf("Entrez les nouvelles informations de la voiture:\n");

    printf("Voiture ID: %d\n", TABV[i].idVoiture);

    printf("\tMarque: ");
    fflush(stdin);
    fgets(TABV[i].marque, 15, stdin);
    lg = strlen(TABV[i].marque);
    TABV[i].marque[lg-1] = '\0';

    printf("\tNom: ");
    fflush(stdin);
    fgets(TABV[i].nomVoiture, 15, stdin);
    lg = strlen(TABV[i].nomVoiture);
    TABV[i].nomVoiture[lg-1] = '\0';

    printf("\tCouleur: ");
    scanf("%s",TABV[i].couleur);

    printf("\tNombre de places: ");
    scanf("%d",&TABV[i].nbplaces);

    printf("\tPrix par jour: ");
    scanf("%d",&TABV[i].prixJour);

    printf("\tEst ce qu'il est en location? ( Oui || Non )\n");
    printf("\tVotre choix: ");
    scanf("%s",TABV[i].EnLocation);

    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = V_ArraySize(fname);
    fwrite(TABV, sizeof(voiture), N, ftmp);

    fclose(ftmp);

    int res1, res2;
    res1 = remove(fname);   //Suppression fichier original
    res2 = rename("tmp.dat", fname);    //Renommer le fichier temporaire avec le nom d'original

    if ( res1 == 0 && res2 == 0)
        printf("La voiture a %ct%c modifi%ce avec succ%cs!\n", 130,130,130,138); //Code ASCII: e (accent aigue) : 130 - e (accent grave) : 138
    else
        printf("ERREUR: la voiture n'a pas pu %ctre modifi%ce!\n",136,130);


    return 1;
}
int SupprimerVoiture (char * fname){
    FILE * ftmp = NULL;
    voiture *TABV;
    int x, i, j, id, N;

    TABV = V_ExtractData(fname);

    do{
        do{
            printf("Quelle voiture voulez vous supprimer?\n");
            printf("Veuillez entrez son id (ou -1 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == -1) {return 0;}
            i = V_FindId(fname,id);
            if( i == -2)
                printf("Aucune voiture avec cet id!\n");
        }while(i == -2);

        AfficherVoiture(TABV[i]);

        printf("Voulez vous supprimer cette voiture?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = V_ArraySize(fname);
    for(j=0; j<N; j++){
        if (j != i)
            fwrite(&TABV[j], sizeof(voiture), 1, ftmp);
    }
    fclose(ftmp);

    int res1, res2;
    res1 = remove(fname);
    res2 = rename("tmp.dat", fname);

    if ( res1 == 0 && res2 == 0)
        printf("La voiture a %ct%c supprim%ce avec succ%cs!\n", 130,130,130,138);
    else
        printf("ERREUR: la voiture n'a pas pu %ctre supprim%ce!\n",136,130);

    return 1;
}

#endif // GESTIONVOITURES_H_INCLUDED
