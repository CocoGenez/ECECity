#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"

typedef struct eau{

    int x1, x2, y1, y2;
    int capacite;
    int id;
    int prix;
    struct eau* next;
    BITMAP* iconeeau;
}t_eau;

typedef struct electricite{

    int x1, x2, y1, y2;
    int capacite;
    int prix;
    struct electricite* next;
    BITMAP* iconeelec;

}t_electricite;

typedef struct route{

    int x;
    int y;
    int prix;
    struct route* next;
    BITMAP** iconeroute;
    BITMAP* truc;
    int id;

}t_route;

typedef struct batiment{

    int x1;
    int x2;
    int y1;
    int y2;
    int niveau;
    int marqueur;
    int prix;
    int habitant;
    int id;
    int reel;
    char nom[20];
    BITMAP* icone;
    int chateau;
    int centrale;
    int capacite;
    t_eau chateauAlimentant[5];
    struct eau water;
    struct electricite elec;
    struct route road;

}t_bat;



struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc;
struct Sommet
{
    struct Arc* arc;
    int valeur;
    int couleur;
};
typedef struct Sommet* pSommet;
typedef struct Graphe{

    struct eau* chateau;
    struct electricite* centrale;
    struct route* chaussee;
    BITMAP* water;
    BITMAP* road;
    BITMAP* elec;
    int taille;
    int ordre;
    int** matricepoids;
    pSommet* pSommet;

}t_graphe;
typedef struct joueur{

    int argent;
    t_bat* propriete;
    int nbhabitant;
    int nbpropriete;
    int nbroute;
    t_route* bitume;

}t_joueur;

typedef struct pol{
    int x1,x2,y1,y2;
}t_case;
typedef struct maillon{
    //numéro du sommet
    int num;
    //pointeur sur la maillon suivant
    struct maillon*suiv;
}Maillon;

//structure regroupant les ancres de tete et de fin de liste
typedef struct file{
    Maillon*tete; //pointeur sur le premier maillon
    Maillon*fin; //pointeur sur le dernier maillon
}FileM;


t_graphe* CreerGraphe(int ordre);
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids,int** matrice);
int* bfs(t_graphe* graphe, int s,t_joueur* player);
void affichage_bfs_chateau(t_graphe* graphe, int* pred,t_joueur* player);
#endif // BIBLIO_H_INCLUDED
