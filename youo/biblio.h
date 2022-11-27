#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include "stdio.h"
#include "stdlib.h"
#include <allegro.h>
#include <string.h>
#define MODE   GFX_AUTODETECT_WINDOWED

typedef struct eau
{

    int x1, x2, y1, y2;
    int capacite;
    int id;
    int prix;
    struct eau* next;
    BITMAP* iconeeau;
} t_eau;

typedef struct electricite
{

    int x1, x2, y1, y2;
    int capacite;
    int prix;
    struct electricite* next;
    BITMAP* iconeelec;

} t_electricite;

typedef struct route
{

    int x;
    int y;
    int prix;
    struct route* next;
    BITMAP** iconeroute;
    BITMAP* truc;
    int id;
    int alimente;
    int alimenteau;

} t_route;

typedef struct batiment
{

    int x1;
    int x2;
    int y1;
    int y2;
    int niveau;
    int marqueur;
    int prix;
    int habitant;
    int id;
    int reel; // pour dire si c'est une construction
    char nom[20];
    BITMAP* icone;
    int chateau; // pour dire si c'est chateau
    int centrale; // pour dire si c'est une centrale
    int capacite; // capacité du batiment
    t_eau chateauAlimentant[5];
    struct eau water;
    struct electricite elec;
    struct route road;
    int alimEau; //alimentation en eau du batiment
    int alimElec; //alimentation en elec du batiment
    int position; // position du chateau pour alimentation
} t_bat;


//Structure arrete
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;
};
typedef struct Arc* pArc;
//Structure pour les sommets du graph
struct Sommet
{
    struct Arc* arc;
    int valeur;
    int couleur;
};
typedef struct Sommet* pSommet;
//Structure du graph
typedef struct Graphe
{

    struct eau* chateau;
    struct electricite* centrale;
    struct route* chaussee;
    BITMAP* water;
    BITMAP* road;
    BITMAP* elec;
    int taille;//nb d arretes
    int ordre;//nb de sommets
    int** matricepoids;
    pSommet* pSommet;

} t_graphe;
typedef struct joueur
{

    int argent;
    t_bat* propriete;
    int nbhabitant;
    int nbpropriete;
    int nbroute;
    t_route* bitume;

} t_joueur;

typedef struct pol
{
    int x1,x2,y1,y2;
} t_case;


//Mode de jeu
void mode_capitaliste();
void mode_communiste();
//Graph
int algoDijkstra(int **matrice, int debut, int fin, int ordre, t_joueur* player);
int algoDijkstraElec(int **matrice, int debut, int fin, int ordre, t_joueur* player);
t_graphe *init_graphe(t_graphe *g, t_joueur *player);
t_graphe* CreerGraphe(int ordre);
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids,int** matrice);
//Alim
t_bat alimentation(t_joueur *player, t_graphe *g, t_bat maison, t_bat *chateau, int **distance_chateau, int i, int castle);
t_bat alimentation_centrale(t_joueur *player, t_graphe *g, t_bat maison, t_bat *centrale, int **distance_centrale, int i, int elec);
//Menu
int clicInMenu(BITMAP *detectionAccueil, int couleurPixel);
void selectionModeDeJeu();
void monMenu();
//Initialisation
void initialisation_allegro();
BITMAP * creer_Bitmap(int width,int height);
BITMAP * charger_Bitmap(const char*chemin);
void initcase(t_case **plateau);
void init_structure(t_bat *batiment, t_graphe *reseau);
//Creation
void creation_route(t_joueur *player, t_case case_actu, t_graphe *reseau, int number, int **matrice, t_graphe *g);
void creation_chateau(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g);
void creation_centrale(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g);
void creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment, int **matrice, t_graphe *g);
t_case detecterCase(t_case **plateau, BITMAP *page, BITMAP *batiment, BITMAP *map, t_joueur *player);
int evolution_batiment(t_joueur *player, t_bat *batiment, int *condition);
int evolution_batiment_communiste(t_joueur *player, t_bat *batiment, int *condition);
//Verification
int verifOccupation(int** matrice, t_case caseactu, int mode);
void check_connexion(t_case case_actu, int **matrice, int mode, t_graphe *g);
void check_connexion_centrale(t_case case_actu, int **matrice, int mode, t_graphe *g);
void check_connexion_route(t_case case_actu, int **matrice, int mode, t_graphe *g);
int choix_panel(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, BITMAP *map, BITMAP *page, BITMAP *panel, BITMAP *detection);
#endif // BIBLIO_H_INCLUDED
