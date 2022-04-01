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
}Voiture;
typedef struct contratLocation{
    float numContrat;
    int idVoiture;
    int idClient;
    date debut;
    date fin;
    int cout;
}Contrat;
typedef struct Client{
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
}Client;

#endif // STRUCTURES_H_INCLUDED

