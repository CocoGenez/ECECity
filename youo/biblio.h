#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include "stdio.h"
#include "stdlib.h"
#include <allegro.h>
#include <string.h>
#define MODE   GFX_AUTODETECT_WINDOWED

typedef struct eau{

    int x1, x2, y1, y2;
    unsigned int capacite;
    int prix;
    struct eau* next;

}t_eau;

typedef struct electricite{

    int x1, x2, y1, y2;
    int capacite;
    int prix;
    struct electricite* next;

}t_electricite;

typedef struct route{

    int x;
    int y;
    int prix;
    struct route* next;

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
    char nom[20];
    BITMAP* icone;
    struct eau water;
    struct electricite elec;
    struct route road;

}t_bat;

typedef struct Graphe{

    struct eau chateau;
    struct electricite centrale;
    struct route chaussee;

}t_graphe;

typedef struct joueur{

    int argent;
    t_bat* propriete;
    int nbhabitant;
    int nbpropriete;

}t_joueur;

typedef struct pol{
    int x1,x2,y1,y2;
}t_case;
void initialisation_allegro();
BITMAP * creer_Bitmap(int width,int height);
BITMAP * charger_Bitmap(const char*chemin);
int menu(BITMAP *page, BITMAP *detection,BITMAP* accueil);
int nouvellepartie(BITMAP *page, BITMAP *detection,BITMAP* accueil);
void initcase(t_case **plateau);
void init_structure(t_bat *batiment, t_graphe *reseau);

#endif // BIBLIO_H_INCLUDED
