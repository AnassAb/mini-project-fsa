#ifndef LOCATIONVOITURE_H_INCLUDED
#define LOCATIONVOITURE_H_INCLUDED

//Calcule Le nombre de contrats enregistrer dans un fichier
int CL_ArraySize (char *fname){
    FILE *fcontrat;
    contrat CL;
    int c=0; //c = SIZE_Variable

    fcontrat = fopen(fname, "rb");
    if(fcontrat == NULL){
        return 0;
    }

    while(fread(&CL, sizeof(contrat), 1, fcontrat)){
        c++;
    }

    fclose(fcontrat);

    return c;
}
//Recuperer Les informations sur des contrats
contrat * CL_ExtractData (char * fname){
    FILE *fcontrat;
    contrat *TCL, CL; //TCL: Tableau Contrat Location
    int c=0;

    fcontrat = fopen(fname, "rb");
    if(fcontrat == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    TCL = (contrat *) malloc(sizeof(contrat));
    while(fread(&CL, sizeof(contrat), 1, fcontrat)){
        TCL[c] = CL;
        c++;
        TCL = (contrat *) realloc(TCL,(c+1)*sizeof(contrat));
    }

    fclose(fcontrat);

    return TCL;

}
//Trouver un contrat par son numero
int CL_FindNC (char *fname, float NC){
    contrat *TABCL;
    int i, N;

    N = CL_ArraySize(fname);
    if( N == 0){
        return -2;
    }else{

        TABCL = CL_ExtractData(fname);

        for(i=0; i<N; i++){
            if (TABCL[i].numContrat == NC){
                return i;
            }
        }

    }
    return -2;
}
void AfficherContrat (contrat CL){
    printf("Contrat N%c: %f\n", 248, CL.numContrat);
    printf("\tId Voiture Lou%ce: %d\n", 130, CL.idVoiture);
    printf("\tId Client: %d\n", CL.idClient);
    printf("\tDate de debut: %d/%d/%d\n", CL.debut.jour, CL.debut.mois, CL.debut.annee);
    printf("\tDate de fin: %d/%d/%d\n", CL.fin.jour, CL.fin.mois, CL.fin.annee);
    printf("\tCout Total: %d DHS\n", CL.cout);
}
int VisualiserContrat (char *fname){
    contrat *TCL;
    int i, N;
    float NC;

    N = CL_ArraySize(fname);
    TCL = CL_ExtractData(fname);

    if(N == 0){
        printf("Aucun contrat n'a %ct%c ajout%c.\n", 130,130, 130);
    }else{
        do{
            printf("Entrez le num%cro de contrat: ",130);
            scanf("%f", &NC);
            i = CL_FindNC(fname,NC);
            if (i == -2){printf("Aucun contrat avec ce num%cro!\n", 130);}
        }while(i == -2);

        AfficherContrat(TCL[i]);
    }

    return 1;
}
//Verifier si le client existe
int VerifyC (client C, char *fclient){
    client *TC;
    int N, i;

    N = C_ArraySize(fclient);
    TC = C_ExtractData(fclient);

    if(N == 0){
        return -1;
    }else{
        for(i=0; i<N; i++){
            if(strcmp(TC[i].nom,C.nom) == 0 && strcmp(TC[i].prenom,C.prenom) == 0){
                return i;
            }
        }
    }

    return -1;

}
//Verifier si la voiture existe
int VerifyV (voiture V, char *fvoiture){
    voiture *TV;
    int N, i;

    N = V_ArraySize(fvoiture);
    TV = V_ExtractData(fvoiture);

    if(N == 0){
        return -1;
    }else{
        for(i=0; i<N; i++){
            if(strcmp(TV[i].nomVoiture,V.nomVoiture) == 0 && strcmp(TV[i].marque, V.marque) == 0){
                return i;
            }
        }
    }
    return -1;

}
//Verifier si la voiture est disponiblle
int VerifyDispV (voiture V, char *fvoiture){
    voiture *TV;
    int N, i;

    N = V_ArraySize(fvoiture);
    TV = V_ExtractData(fvoiture);

    if(N == 0){
        return -1;
    }else{
        for(i=0; i<N; i++){
            if(strcmp(TV[i].nomVoiture,V.nomVoiture) == 0 && strcmp(TV[i].marque, V.marque) == 0 && strcmp(TV[i].EnLocation, "Non") == 0 ){
                return i;
            }
        }
    }
    return -1;

}
//Calcule le nombre de jour equivalent pour chaque mois
int JourEq (int mois, int annee){
    switch(mois){
        case 1:
            return 31;
        case 2:
            if((annee%4) == 0)
                return 29;
            else
                return 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }

    return 0;

}
//Calcul le nombre de jour total pour chaquz date (ex: 1/1/1 ==> 366 et 1/1/2022 ==> 738537)
int NbrJourTotal (date d){
    int S=0;
    int i;

    for(i=0; i<d.annee; i++){
        if((i%4) == 0)
          S += 366;
        else
          S += 365;

    }

    for(i=1; i<d.mois; i++)
        S += JourEq(i,d.annee);


    S += d.jour;

    return S;
}
//Modifier l'attribut enLocation de Oui a Non et vice versa
int CL_ModifierV (char * fvoiture, int i){
    FILE * ftmp = NULL;
    voiture *TABV;
    int N;

    TABV = V_ExtractData(fvoiture);

    if(strcmp(TABV[i].EnLocation,"Oui") == 0){
        strcpy(TABV[i].EnLocation,"Non");
    }else{
        strcpy(TABV[i].EnLocation,"Oui");
    }

    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = V_ArraySize(fvoiture);
    fwrite(TABV, sizeof(voiture), N, ftmp);

    fclose(ftmp);

    int res1, res2;
    res1 = remove(fvoiture);   //Suppression fichier original
    res2 = rename("tmp.dat", fvoiture);    //Renommer le fichier temporaire avec le nom d'original

    if ( res1 == 0 && res2 == 0 )
        return 1;


    return 0;
}
int LouerVoiture (char *fcontrat, char *fclient, char * fvoiture){
    client C, *TC;
    voiture V, *TV;
    contrat CL;
    float NC;
    int lg, N;
    int vv, vc, x, y;
    int TJD, TJF, NJT, JEq;

    //Recuperer le nom et prenom du client
    //Verifier si il existe deja dans le fichier client
    //Sinon lui proposer de creer un compte
    do{
        printf("Veuillez saisir vos informations:\n");

        printf("\tNom: ");
        fflush(stdin);
        fgets(C.nom, 20, stdin); //Le nom peut etre compose
        lg = strlen(C.nom);
        C.nom[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

        printf("\tPr%cnom: ",130);
        fflush(stdin);
        fgets(C.prenom, 20, stdin); //Le prenom peut etre compose
        lg = strlen(C.prenom);
        C.prenom[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

        vc = VerifyC(C, fclient);

        if (vc == -1){
            printf("C'est votre premi%cre fois chez nous!\n",138);
            printf("Voulez-vous cr%cer un compte chez nous?\n",130);
            printf("\n1: Oui\t\t2: Non\n");
            printf("\nVotre choix: ");
            scanf("%d", &x);
            if(x == 1){
                printf("\nEntrez vos information:\n");
                AjouterClient(fclient);
                TC = C_ExtractData(fclient);
                N = C_ArraySize(fclient);
                vc = N-1;
            }
            if(x == 2){
                return 0;
            }
        }

        TC = C_ExtractData(fclient);
        printf("\nVotre Profil:\n");
        AfficherClient(TC[vc]);
        printf("\nVoulez vous continuer avec les informations figurez dans ce profil?\n");
        printf("\n1: Oui, c'est moi\t\t2: Non, Ce n'est pas mon profil\n");
        printf("\nVotre choix: ");
        scanf("%d", &x);

    }while( x != 1 );
    //Recuperer l'id du client et la mettre dans le contrat
    CL.idClient = TC[vc].idClient;

    //Recuperer la marque et le nom de la voiture
    //Verifier si il existe si oui verifier si il est disponible
    //Si oui la louer
    //Sinon Quitter
    do{
        printf("\n\nQuelle voiture vous souhaitez louer?\n\n");

        printf("\tMarque: ");
        fflush(stdin);
        fgets(V.marque, 15, stdin); //La marque peut etre compose
        lg = strlen(V.marque);
        V.marque[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

        printf("\tNom Voiture: ");
        fflush(stdin);
        fgets(V.nomVoiture, 15, stdin); //La marque peut etre compose
        lg = strlen(V.nomVoiture);
        V.nomVoiture[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

        vv = VerifyV(V, fvoiture);
        if (vv == -1){
            printf("\nAucune voiture avec ce nom et cette marque\n");
            return 0;
        }else{

            TV = V_ExtractData(fvoiture);
            vv = VerifyDispV(V,fvoiture);

            if(vv != -1){
                printf("\nVoulez vous louer cette voiture?\n");
                AfficherVoiture(TV[vv]);
                printf("\n1: Oui\t\t2: Non\t\t3: Retour\n");
                printf("\nVotre choix: ");
                scanf("%d", &x);

                if( x == 3){return 0;}

            }else{
                printf("\nLa voiture demand%ce n'est pas disponible!\n",130);
                return 0;
            }
        }

    } while(x != 1);

    //Change L'attribut EnLocation de la voiture de Oui ==> Non
    CL_ModifierV(fvoiture, vv);
    //Recuperer l'id de la voiture et la mettre dans le contrat
    CL.idVoiture = TV[vv].idVoiture;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    do{
        printf("\n\nDate de debut:\n");
        do{
            printf("Ann%ce: ",130);
            scanf("%d", &CL.debut.annee);
            if(CL.debut.annee < (tm.tm_year + 1900)){printf("ERREUR: Ann%ce Invalide! (%d < Ann%ce Actuelle).\n", 130, CL.debut.annee, 130);}
        }while(CL.debut.annee < (tm.tm_year + 1900));
        do{
            printf("Mois(1-12): ");
            scanf("%d", &CL.debut.mois);
            if(CL.debut.annee == (tm.tm_year + 1900) && CL.debut.mois < (tm.tm_mon + 1)){
                printf("ERREUR: Mois Invalide! Veuillez entrer un mois compris entre %02d et 12.\n", (tm.tm_mon + 1));
            }
        }while(CL.debut.mois>12 || CL.debut.mois<1 || (CL.debut.annee == (tm.tm_year + 1900) && CL.debut.mois < (tm.tm_mon + 1)) );
        do{
            JEq = JourEq(CL.debut.mois, CL.debut.annee);
            printf("Jour(1-%d): ", JEq);
            scanf("%d", &CL.debut.jour);
            if(CL.debut.annee == (tm.tm_year + 1900) && CL.debut.mois == (tm.tm_mon + 1) && CL.debut.jour < tm.tm_mday){
                printf("ERREUR: Jour Invalide! Veuillez entrer un jour compris entre %02d et %d.\n", tm.tm_mday, JEq);
            }
        }while(CL.debut.jour>JEq || CL.debut.jour<1 || (CL.debut.annee == (tm.tm_year + 1900) && CL.debut.mois == (tm.tm_mon + 1) && CL.debut.jour < tm.tm_mday) );
        TJD = NbrJourTotal(CL.debut);

        printf("\nDate de fin:\n");
        do{
            printf("Ann%ce: ",130);
            scanf("%d", &CL.fin.annee);
            if(CL.fin.annee < CL.debut.annee){printf("ERREUR: Ann%ce Invalide! (%d < Ann%ce Debut).\n", 130, CL.fin.annee, 130);}
        }while(CL.fin.annee < CL.debut.annee);
        do{
            printf("Mois(1-12): ");
            scanf("%d", &CL.fin.mois);
            if(CL.fin.annee == CL.debut.annee && CL.fin.mois < CL.debut.mois){
                printf("ERREUR: Mois Invalide! Veuillez entrer un mois compris entre %02d et 12.\n", CL.debut.mois);
            }
        }while(CL.fin.mois>12 || CL.fin.mois<1 || (CL.fin.annee == CL.debut.annee && CL.fin.mois < CL.debut.mois) );
        do{
            JEq = JourEq(CL.fin.mois, CL.fin.annee);
            printf("Jour(1-%d): ", JEq);
            scanf("%d", &CL.fin.jour);
            if(CL.fin.annee == CL.debut.annee && CL.fin.mois == CL.debut.mois && CL.fin.jour < CL.debut.jour){
                printf("ERREUR: Jour Invalide! Veuillez entrer un jour compris entre %02d et %d.\n", CL.debut.jour, JEq);
            }
        }while(CL.fin.jour>JEq || CL.fin.jour<1 || (CL.fin.annee == CL.debut.annee && CL.fin.mois == CL.debut.mois && CL.fin.jour < CL.debut.jour) );
        TJF = NbrJourTotal(CL.fin);

        NJT = TJF - TJD;

        if(NJT == 0){printf("ERREUR: Vous ne pouvez pas louer moins d'une journ%ce!\n",130);}

    }while(NJT == 0);

    CL.cout = NJT * TV[vv].prixJour;
    printf("\nLe cout total est: %d DHS\n", CL.cout);

    do{
        srand(time(NULL));
        NC = ((10000 - 1) * ((float)rand() / RAND_MAX)) + 1;
        y = CL_FindNC(fcontrat, NC);
    }while(y != -2);
    CL.numContrat = NC;
    printf("\nVotre n%c de contrat est: %f\n", 248, CL.numContrat);
    printf("Veuillez m%cmoriser ce nombre pour pouvoir acc%cder %c votre contrat.\n",130, 138, 133);

    FILE *fptr = NULL;
    fptr = fopen(fcontrat, "ab");
    if(fptr == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    fwrite(&CL, sizeof(contrat), 1, fptr);

    fclose(fptr);

    printf("\nVotre location a %ct%c effectu%ce avec succ%cs!\n",130,130,130,138);

    return 1;
}
//Supprimer un contrat du fichier
int SuppCL(char * fname,int i){
    FILE *ftmp = NULL;
    contrat *TABCL;
    int N, j;

    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    TABCL = CL_ExtractData(fname);
    N = V_ArraySize(fname);

    for(j=0; j<N; j++){
        if (j != i)
            fwrite(&TABCL[j], sizeof(contrat), 1, ftmp);
    }
    fclose(ftmp);

    int res1, res2;
    res1 = remove(fname);
    res2 = rename("tmp.dat", fname);

    if ( res1 == 0 && res2 == 0)
        return 1;
    else
        return 0;

}
//Test si La voiture est rendu et apres supprimer le contrat
int SupprimerContrat (char * fcontrat, char *fvoiture){
    contrat *TABCL;
    voiture *TABV;
    int x, i, j;
    float NC;

    do{
        do{
            printf("Quelle contrat voulez vous supprimer?\n");
            printf("Veuillez entrez son n%c : ", 248);
            scanf("%f", &NC);
            i = CL_FindNC(fcontrat,NC);
            if( i == -2)
                printf("Aucun contrat avec ce num%cro!\n", 130);
        }while(i == -2);

        TABCL = CL_ExtractData(fcontrat);

        AfficherContrat(TABCL[i]);
        printf("Voulez vous supprimer ce contrat?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    j = V_FindId(fvoiture,TABCL[i].idVoiture);
    TABV = V_ExtractData(fvoiture);

    if(strcmp(TABV[j].EnLocation, "Non") == 0){
        int res = SuppCL(fcontrat, i);
        if ( res == 1)
            printf("Le contrat a %ct%c supprim%c avec succ%cs!\n", 130,130,130,138);
        else
            printf("ERREUR: le contrat n'a pas pu %ctre supprimer!\n",136);
    }else{
        printf("\nCe contrat ne peut pas %ctre supprimer.\nVeuillez retourner la voiture avant de supprimer un contrat!\n", 136);
    }



    return 1;


}
void RetournerVoiture (char *fcontrat, char *fvoiture){
    int i, j, idV;
    float NC;
    contrat *TABCL;

    do{
        printf("Veuillez entrez votre n%c de contrat: ", 248);
        scanf("%f", &NC);
        i = CL_FindNC(fcontrat,NC);
        if( i == -2)
            printf("Aucun contrat avec ce num%cro!\n", 130);
    }while(i == -2);

    TABCL = CL_ExtractData(fcontrat);

    idV = TABCL[i].idVoiture;
    j = V_FindId(fvoiture,idV);

    int res = CL_ModifierV(fvoiture, j);

    if ( res == 1 )
        printf("La voiture a %ct%c retourn%ce avec succ%cs!\n", 130,130,130,138);
    else
        printf("ERREUR: la voiture n'a pas pu %ctre retourn%ce!\n",136,130);


}
int ModifierContrat(char * fcontrat, char * fvoiture){
    FILE * ftmp = NULL;
    voiture V, *TV;
    contrat *TABCL;
    float NC;
    int x, i, j, N, c, vv, lg;
    int TJC,TJD, TJF, NJT, JEq;
    do{
        do{
            printf("Quelle contrat voulez vous modifier?\n");
            printf("Veuillez entrez son n%c : ", 248);
            scanf("%f", &NC);
            i = CL_FindNC(fcontrat,NC);
            if( i == -2)
                printf("Aucun contrat avec ce num%cro!\n", 130);
        }while(i == -2);

        TABCL = CL_ExtractData(fcontrat);
        TV = V_ExtractData(fvoiture);

        AfficherContrat(TABCL[i]);
        printf("Voulez vous modifier ce contrat?\n");
        printf("\t1: Oui \t\t2: Non\t\t3: Revenir au menu\n");
        printf("Votre choix(1, 2 ou 3): ");
        scanf("%d", &x);

        if(x == 3)
            return 0;

    }while(x != 1 );

    //Le client est inchangeable
    //tester si la date de debut a passe
    //si oui on ne change que la date de retour
    //si non on peut changer la date de debut, la date de retour et la voiture

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date d;

    d.jour = tm.tm_mday;
    d.mois = tm.tm_mon + 1;
    d.annee = tm.tm_year + 1900;

    TJC = NbrJourTotal(d);
    TJD = NbrJourTotal(TABCL[i].debut);

    if((TJD - TJC) <= 0){
        do{
            printf("\nDate de fin:\n");
            do{
                printf("Ann%ce: ",130);
                scanf("%d", &TABCL[i].fin.annee);
                if(TABCL[i].fin.annee < TABCL[i].debut.annee){printf("ERREUR: Ann%ce Invalide! (%d < Ann%ce Debut).\n", 130, TABCL[i].fin.annee, 130);}
            }while(TABCL[i].fin.annee < TABCL[i].debut.annee);
            do{
                printf("Mois(1-12): ");
                scanf("%d", &TABCL[i].fin.mois);
                if(TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois < TABCL[i].debut.mois){
                    printf("ERREUR: Mois Invalide! Veuillez entrer un mois compris entre %02d et 12.\n", TABCL[i].debut.mois);
                }
            }while(TABCL[i].fin.mois>12 || TABCL[i].fin.mois<1 || (TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois < TABCL[i].debut.mois) );
            do{
                JEq = JourEq(TABCL[i].fin.mois, TABCL[i].fin.annee);
                printf("Jour(1-%d): ", JEq);
                scanf("%d", &TABCL[i].fin.jour);
                if(TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois == TABCL[i].debut.mois && TABCL[i].fin.jour < TABCL[i].debut.jour){
                    printf("ERREUR: Jour Invalide! Veuillez entrer un jour compris entre %02d et %d.\n", TABCL[i].debut.jour, JEq);
                }
            }while(TABCL[i].fin.jour>JEq || TABCL[i].fin.jour<1 || (TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois == TABCL[i].debut.mois && TABCL[i].fin.jour < TABCL[i].debut.jour) );
            TJF = NbrJourTotal(TABCL[i].fin);

            NJT = TJF - TJD;

            if(NJT == 0){printf("ERREUR: Vous ne pouvez pas louer moins d'une journ%ce!\n",130);}

        }while(NJT == 0);

    } else {
        printf("Voulez vous changer la voiture?(1: Oui || 2: Non)\n");
        printf("Votre choix: ");
        scanf("%d", &c);
        if (c == 1){
            do{
                printf("\n\nQuelle voiture vous souhaitez louer?\n\n");

                printf("\tMarque: ");
                fflush(stdin);
                fgets(V.marque, 15, stdin); //La marque peut etre compose
                lg = strlen(V.marque);
                V.marque[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

                printf("\tNom Voiture: ");
                fflush(stdin);
                fgets(V.nomVoiture, 15, stdin); //La marque peut etre compose
                lg = strlen(V.nomVoiture);
                V.nomVoiture[lg-1] = '\0'; //La chaine de caracteres recuperer par fgets() se termine par '\n'

                vv = VerifyV(V, fvoiture);
                if (vv == -1){
                    printf("\nAucune voiture avec ce nom et cette marque\n");
                    return 0;
                }else{

                    vv = VerifyDispV(V,fvoiture);

                    if(vv != -1){
                        printf("\nVoulez vous louer cette voiture?\n");
                        AfficherVoiture(TV[vv]);
                        printf("\n1: Oui\t\t2: Non\t\t3: Retour\n");
                        printf("\nVotre choix: ");
                        scanf("%d", &x);

                        if( x == 3){return 0;}

                    }else{
                        printf("\nLa voiture demand%ce n'est pas disponible!\n",130);
                        return 0;
                    }
                }

            } while(x != 1);

            //Change L'attribut EnLocation de la voiture de Oui ==> Non
            CL_ModifierV(fvoiture, vv);
            //Recuperer l'id de la voiture et la mettre dans le contrat
            TABCL[i].idVoiture = TV[vv].idVoiture;
        }
        do{
            printf("\n\nDate de debut:\n");
            do{
                printf("Ann%ce: ",130);
                scanf("%d", &TABCL[i].debut.annee);
                if(TABCL[i].debut.annee < (tm.tm_year + 1900)){printf("ERREUR: Ann%ce Invalide! (%d < Ann%ce Actuelle).\n", 130, TABCL[i].debut.annee, 130);}
            }while(TABCL[i].debut.annee < (tm.tm_year + 1900));
            do{
                printf("Mois(1-12): ");
                scanf("%d", &TABCL[i].debut.mois);
                if(TABCL[i].debut.annee == (tm.tm_year + 1900) && TABCL[i].debut.mois < (tm.tm_mon + 1)){
                    printf("ERREUR: Mois Invalide! Veuillez entrer un mois compris entre %02d et 12.\n", (tm.tm_mon + 1));
                }
            }while(TABCL[i].debut.mois>12 || TABCL[i].debut.mois<1 || (TABCL[i].debut.annee == (tm.tm_year + 1900) && TABCL[i].debut.mois < (tm.tm_mon + 1)) );
            do{
                JEq = JourEq(TABCL[i].debut.mois, TABCL[i].debut.annee);
                printf("Jour(1-%d): ", JEq);
                scanf("%d", &TABCL[i].debut.jour);
                if(TABCL[i].debut.annee == (tm.tm_year + 1900) && TABCL[i].debut.mois == (tm.tm_mon + 1) && TABCL[i].debut.jour < tm.tm_mday){
                    printf("ERREUR: Jour Invalide! Veuillez entrer un jour compris entre %02d et %d.\n", tm.tm_mday, JEq);
                }
            }while(TABCL[i].debut.jour>JEq || TABCL[i].debut.jour<1 || (TABCL[i].debut.annee == (tm.tm_year + 1900) && TABCL[i].debut.mois == (tm.tm_mon + 1) && TABCL[i].debut.jour < tm.tm_mday) );
            TJD = NbrJourTotal(TABCL[i].debut);

            printf("\nDate de fin:\n");
            do{
                printf("Ann%ce: ",130);
                scanf("%d", &TABCL[i].fin.annee);
                if(TABCL[i].fin.annee < TABCL[i].debut.annee){printf("ERREUR: Ann%ce Invalide! (%d < Ann%ce Debut).\n", 130, TABCL[i].fin.annee, 130);}
            }while(TABCL[i].fin.annee < TABCL[i].debut.annee);
            do{
                printf("Mois(1-12): ");
                scanf("%d", &TABCL[i].fin.mois);
                if(TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois < TABCL[i].debut.mois){
                    printf("ERREUR: Mois Invalide! Veuillez entrer un mois compris entre %02d et 12.\n", TABCL[i].debut.mois);
                }
            }while(TABCL[i].fin.mois>12 || TABCL[i].fin.mois<1 || (TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois < TABCL[i].debut.mois) );
            do{
                JEq = JourEq(TABCL[i].fin.mois, TABCL[i].fin.annee);
                printf("Jour(1-%d): ", JEq);
                scanf("%d", &TABCL[i].fin.jour);
                if(TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois == TABCL[i].debut.mois && TABCL[i].fin.jour < TABCL[i].debut.jour){
                    printf("ERREUR: Jour Invalide! Veuillez entrer un jour compris entre %02d et %d.\n", TABCL[i].debut.jour, JEq);
                }
            }while(TABCL[i].fin.jour>JEq || TABCL[i].fin.jour<1 || (TABCL[i].fin.annee == TABCL[i].debut.annee && TABCL[i].fin.mois == TABCL[i].debut.mois && TABCL[i].fin.jour < TABCL[i].debut.jour) );
            TJF = NbrJourTotal(TABCL[i].fin);

            NJT = TJF - TJD;

            if(NJT == 0){printf("ERREUR: Vous ne pouvez pas louer moins d'une journ%ce!\n",130);}

        }while(NJT == 0);
    }

    j = V_FindId(fvoiture, TABCL[i].idVoiture);
    TABCL[i].cout = NJT * TV[j].prixJour;
    printf("\nVotre nouveau cout total est: %d DHS\n", TABCL[i].cout);


    ftmp = fopen("tmp.dat", "wb");
    if(ftmp == NULL){
        printf("ERREUR: Impossible d'ouvrir ce fichier!\n");
        exit(0);
    }

    N = CL_ArraySize(fcontrat);
    fwrite(TABCL, sizeof(contrat), N, ftmp);

    fclose(ftmp);

    int res1, res2;
    res1 = remove(fcontrat);   //Suppression fichier original
    res2 = rename("tmp.dat", fcontrat);    //Renommer le fichier temporaire avec le nom d'original

    if ( res1 == 0 && res2 == 0)
        printf("Le contrat a %ct%c modifi%c avec succ%cs!\n", 130,130,130,138); //Code ASCII: e (accent aigue) : 130 - e (accent grave) : 138
    else
        printf("ERREUR: le contrat n'a pas pu %ctre modifi%c!\n",136,130);


    return 1;

}
#endif // LOCATIONVOITURE_H_INCLUDED
