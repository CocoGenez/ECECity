#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"

typedef struct eau{

    int x1, x2, y1, y2;
    int capacite;
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
    int chateau;
    int centrale;
    int capacite;
    struct eau water;
    struct electricite elec;
    struct route road;

}t_bat;

typedef struct Graphe{

    struct eau* chateau;
    struct electricite* centrale;
    struct route* chaussee;
    BITMAP* water;
    BITMAP* road;
    BITMAP* elec;

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


#endif // BIBLIO_H_INCLUDED
