#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct date {
    int jour;
    int mois;
    int annee;
}date;
typedef struct Voiture{
    int idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char EnLocation[4];
}voiture;
typedef struct contratLocation{
    float numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date fin;
    int cout;
}contrat;
typedef struct Client{
    int idClient;
    char nom[20];
    char prenom[20];
    char cin[10];
    char adresse[55];
    int telephone;
}client;


#endif // STRUCTURES_H_INCLUDED
