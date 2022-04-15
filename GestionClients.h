#ifndef GESTIONCLIENTS_H_INCLUDED
#define GESTIONCLIENTS_H_INCLUDED

//Calcule Le nombre de clients enregistrer dans un fichier
int C_ArraySize (char *fname){
    FILE *fclient;
    client C;
    int c=0; //c = SIZE_Variable

    fclient = fopen(fname, "rb");
    if(fclient == NULL){
        return 0;
    }

    while(fread(&C, sizeof(client), 1, fclient)){
        c++;
    }

    fclose(fclient);

    return c;
}
//Recuperer Les informations sur les clients
client * C_ExtractData (char * fname){
    FILE *fclient;
    client *TC, C; //TC: Tableau Client
    int c=0;

    fclient = fopen(fname, "rb");
    if(fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    TC = (client *) malloc(sizeof(client));
    while(fread(&C, sizeof(client), 1, fclient)){
        TC[c] = C;
        c++;
        TC = (client *) realloc(TC,(c+1)*sizeof(client));
    }

    fclose(fclient);

    return TC;

}
//Trouver Le client par Id
int C_FindId (char *fname, int id){
    client *TABC;
    int i, N;

    TABC = C_ExtractData(fname);
    N = C_ArraySize(fname);

    for(i=0; i<N; i++){
        if (TABC[i].idClient == id){
            return i;
        }
    }

    return -2;
}
void AfficherClient (client C){
    printf("Client ID: %d\n", C.idClient);
    printf("\tNom: %s\n",C.nom);
    printf("\tPr%cnom: %s\n", 130, C.prenom);
    printf("\tCIN: %s\n",C.cin);
    printf("\tAdresse: %s\n",C.adresse);
    printf("\tN%c Telephone: 0%d\n", 248,C.telephone);
}
void AjouterClient(char * fname){
    FILE *fclient;
    client C;
    int lg,i;

    fclient = fopen(fname, "ab");
    if(fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    //Tester si l'id entre est unique
    do{
        srand(time(NULL));
        C.idClient = rand() % (10000 - 0 + 1) + 0; //n = rand() % (max - min + 1)
        i = C_FindId(fname, C.idClient);
    }while(i != -2);

    printf("Client ID: %d\n", C.idClient);

    printf("\tNom: ");
    fflush(stdin);
    fgets(C.nom, 20, stdin); //Le nom peut etre compose
    lg = strlen(C.nom);
    C.nom[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

    printf("\tPr%cnom: ",130);
    fflush(stdin);
    fgets(C.prenom, 20, stdin);
    lg = strlen(C.prenom);
    C.prenom[lg-1] = '\0';

    printf("\tCIN: ");
    scanf("%s",C.cin);

    printf("\tAdresse: ");
    fflush(stdin);
    fgets(C.adresse, 55, stdin);
    lg = strlen(C.adresse);
    C.adresse[lg-1] = '\0';

    printf("\tN%c Telephone: ",248);
    scanf("%d",&C.telephone);

    fwrite(&C,sizeof(client), 1, fclient);

    fclose(fclient);

    printf("Le client a %ct%c ajout%c avec succ%cs!\n", 130,130,130,138);

}
void ListeClients (char *fname){
    FILE *fclient;
    client C;
    int c=0, N;

    fclient = fopen(fname, "rb");
    if(fclient == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = C_ArraySize(fname);

    if(N == 0){
        printf("Aucun client n'a %ct%c ajout%c.\nVeuillez ajouter des clients!\n", 130,130, 130);
    }else{
        while(fread(&C, sizeof(client), 1, fclient)){
            AfficherClient(C);
            c++;
        }

        fclose(fclient);
    }

}
int ModifierClient (char * fname){
    FILE * ftmp = NULL;
    client *TABC;
    int x, i, id, lg, N;

    TABC = C_ExtractData(fname);

    do{
        do{
            printf("Quel client voulez vous modifier?\n");
            printf("Veuillez entrez son id (ou -1 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == -1) {return 0;}
            i = C_FindId(fname,id);
            if( i == -2)
                printf("Aucun client avec cet id!\n");
        }while(i == -2);

        AfficherClient(TABC[i]);

        printf("Voulez vous modifier ce client?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    printf("Entrez les nouvelles informations du client:\n");

    printf("Client ID: %d\n", TABC[i].idClient);

    printf("\tNom: ");
    fflush(stdin);
    fgets(TABC[i].nom, 15, stdin);
    lg = strlen(TABC[i].nom);
    TABC[i].nom[lg-1] = '\0';

    printf("\tPr%cnom: ", 130);
    fflush(stdin);
    fgets(TABC[i].prenom, 15, stdin);
    lg = strlen(TABC[i].prenom);
    TABC[i].prenom[lg-1] = '\0';

    printf("\tCIN: ");
    scanf("%s",TABC[i].cin);

    printf("\tAdresse: ");
    fflush(stdin);
    fgets(TABC[i].adresse, 55, stdin);
    lg = strlen(TABC[i].adresse);
    TABC[i].adresse[lg-1] = '\0';

    printf("\tN%c Telephone: ",248);
    scanf("%d",&TABC[i].telephone);

    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = C_ArraySize(fname);
    fwrite(TABC, sizeof(client), N, ftmp);

    fclose(ftmp);

    int res1, res2;
    res1 = remove(fname);   //Suppression fichier original
    res2 = rename("tmp.dat", fname);    //Renommer le fichier temporaire avec le nom d'original

    if ( res1 == 0 && res2 == 0)
        printf("Le client a %ct%c modifi%c avec succ%cs!\n", 130,130,130,138); //Code ASCII: e (accent aigue) : 130 - e (accent grave) : 138
    else
        printf("ERREUR: le client n'a pas pu %ctre modifi%c!\n",136,130);


    return 1;
}
int SupprimerClient (char * fname){
    FILE * ftmp = NULL;
    client *TABC;
    int x, i, j, id, N;

    TABC = C_ExtractData(fname);

    do{
        do{
            printf("Quel client voulez vous supprimer?\n");
            printf("Veuillez entrez son id (ou -1 pour revenir au menu): ");
            scanf("%d", &id);
            if (id == -1) {return 0;}
            i = C_FindId(fname,id);
            if( i == -2)
                printf("Aucun client avec cet id!\n");
        }while(i == -2);

        AfficherClient(TABC[i]);

        printf("Voulez vous supprimer ce client?\n");
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

    N = C_ArraySize(fname);
    for(j=0; j<N; j++){
        if (j != i)
            fwrite(&TABC[j], sizeof(client), 1, ftmp);
    }
    fclose(ftmp);

    int res1, res2;
    res1 = remove(fname);
    res2 = rename("tmp.dat", fname);

    if ( res1 == 0 && res2 == 0)
        printf("Le client a %ct%c supprim%c avec succ%cs!\n", 130,130,130,138);
    else
        printf("ERREUR: le client n'a pas pu %ctre supprim%c!\n",136,130);

    return 1;
}


#endif // GESTIONCLIENTS_H_INCLUDED
