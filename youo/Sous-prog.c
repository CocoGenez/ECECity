#include "biblio.h"
/***Sous programme lie aux graphe***/
/**Algorithme de djkstra permettant de calculer le plus court chemin***/
int algoDijkstra(int **matrice, int debut, int fin, int ordre, t_joueur* player)
{
    int min, d, m = 0, j = 0;  // min = cout minimal, d = cout actuel, m : sommet suivant
    int cout[ordre];
    int chemin[ordre];  // tableau des sommets du chemin
    int preds[ordre];
    int marque[ordre];  // 1 si sommet explore, sinon 0
    for (int i = 0; i < ordre; i++)
    {
        marque[i] = 0;  // on initialise les sommets comme non-marques
    }
    for (int i = 0; i < ordre; i++)
    {
        cout[i] = 400;   // on marque tous les sommets a un cout infini (ici 400)
        preds[i] = -1;  // on marque les predecesseurs de chaque sommet à -1
    }
    marque[debut] = 1;
    cout[debut] = 0;

    // printf("marque[fin] = %d", marque[fin]);
    while (marque[fin] == 0)  // tant qu'on n'a pas explore le sommet de fin
    {
        min = 400;                        // cout minimal = infini
        for (int i = 0; i < ordre; i++)  // parcours de tous les sommets
        {
            d = cout[debut] + matrice[debut][i];  // cout actuel = cout jusqu'a present + cout vers sommet i
            // printf("MATRICE [%d] [%d] : %d\n", debut, i, matrice[debut][i]);
            if (d < cout[i] && marque[i] == 0)  // si cout actuel < cout vers sommet i et si sommet i n'est pas explore
            {
                cout[i] = d;       // cout vers sommet i = cout actuel
                preds[i] = debut;  // predecesseur de i = sommet explore actuellement
            }
            if (min > cout[i] && marque[i] == 0)  // si cout minimal > cout vers sommet i et si sommet i n'est pas explore
            {
                min = cout[i];  // cout minimal = cout vers sommet i
                m = i;          // sommet suivant = sommet i
            }
            if (i == ordre - 1 && min == 400)
            {
                return 400;
            }
        }
        debut = m;          // on passe au sommet suivant
        marque[debut] = 1;  // le sommet suivant est explore
    }

    debut = fin;         // on commence par la fin du chemin
    while (debut != -1)  // tant qu'il reste au moins un predecesseur
    {
        chemin[j] = debut;  // on ajoute le sommet parcouru au chemin
        // printf("preds[debut] = %d\n", preds[debut]);
        debut = preds[debut];  // on passe au sommet precedent
        j += 1;
    }
    //Quelle route est relie a un chateau
    for (int k=0; k<j; k++)
    {
        for(int z=0; z<ordre; z++)
        {
            if(player->bitume[z].id==chemin[k] )
            {
                player->bitume[z].alimenteau=1;
            }
        }

    }
    return cout[fin];  // on retourne le cout du chemin
}

int algoDijkstraElec(int **matrice, int debut, int fin, int ordre, t_joueur* player)
{
    int min, d, m = 0, j = 0;  // min = cout minimal, d = cout actuel, m : sommet suivant
    int cout[ordre];
    int chemin[ordre];  // tableau des sommets du chemin
    int preds[ordre];
    int marque[ordre];  // 1 si sommet explore, sinon 0
    for (int i = 0; i < ordre; i++)
    {
        marque[i] = 0;  // on initialise les sommets comme non-marques
    }
    for (int i = 0; i < ordre; i++)
    {
        cout[i] = 400;   // on marque tous les sommets a un cout infini (ici 99)
        preds[i] = -1;  // on marque les predecesseurs de chaque sommet à -1
    }
    marque[debut] = 1;
    cout[debut] = 0;

    // printf("marque[fin] = %d", marque[fin]);
    while (marque[fin] == 0)  // tant qu'on n'a pas explore le sommet de fin
    {
        min = 400;                        // cout minimal = infini
        for (int i = 0; i < ordre; i++)  // parcours de tous les sommets
        {
            d = cout[debut] + matrice[debut][i];  // cout actuel = cout jusqu'a present + cout vers sommet i
            // printf("MATRICE [%d] [%d] : %d\n", debut, i, matrice[debut][i]);
            if (d < cout[i] && marque[i] == 0)  // si cout actuel < cout vers sommet i et si sommet i n'est pas explore
            {
                cout[i] = d;       // cout vers sommet i = cout actuel
                preds[i] = debut;  // predecesseur de i = sommet explore actuellement
            }
            if (min > cout[i] && marque[i] == 0)  // si cout minimal > cout vers sommet i et si sommet i n'est pas explore
            {
                min = cout[i];  // cout minimal = cout vers sommet i
                m = i;          // sommet suivant = sommet i
            }
            if (i == ordre - 1 && min == 400)
            {
                return 400;
            }
        }
        debut = m;          // on passe au sommet suivant
        marque[debut] = 1;  // le sommet suivant est explore
    }

    debut = fin;         // on commence par la fin du chemin
    while (debut != -1)  // tant qu'il reste au moins un predecesseur
    {
        chemin[j] = debut;  // on ajoute le sommet parcouru au chemin
        // printf("preds[debut] = %d\n", preds[debut]);
        debut = preds[debut];  // on passe au sommet precedent
        j += 1;
    }
    //Quelle route relie a une centrale
    for (int k=0; k<j; k++)
    {
        for(int z=0; z<ordre; z++)
        {
            if(player->bitume[z].id==chemin[k] )
            {
                player->bitume[z].alimente=1;
            }
        }

    }


    return cout[fin];  // on retourne le cout du chemin
}

/***Initialise la matrice poids et toutes les info du graphs***/
t_graphe *init_graphe(t_graphe *g, t_joueur *player)
{
    int ordre = 1000;//nb de sommet
    g = CreerGraphe(ordre);  // créer le graphe d'ordre sommets
    g->ordre = 0;
    g->matricepoids = (int **)malloc(ordre * sizeof(int *));
    for (int i = 0; i < ordre; i++)
    {
        g->matricepoids[i] = (int *)malloc(ordre * sizeof(int));
        for (int j = 0; j < ordre; j++)
        {
            g->matricepoids[i][j] = 99;//Distance de 99 pour tout les sommet  par defaut (simuler l'infini) tant que pas relier
        }
    }

    return g;
}
/*** Cree les arretes entre chaque sommets s1 et S2 ***/
pSommet *CreerArete(pSommet *sommet, int s1, int s2, int poids, int **matricepoids)
{
    if (sommet[s1]->arc == NULL)
    {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = poids;
        matricepoids[s1][s2] = matricepoids[s2][s1] = poids;

        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    }

    else
    {
        pArc temp = sommet[s1]->arc;
        while (!(temp->arc_suivant == NULL))
        {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = poids;
        matricepoids[s1][s2] = matricepoids[s2][s1] = poids;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2)
        {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->poids = poids;
            matricepoids[s1][s2] = matricepoids[s2][s1] = poids;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

/***Cree le graph de tout le projet ***/
t_graphe *CreerGraphe(int ordre)
{
    t_graphe *Newgraphe = (t_graphe *)malloc(sizeof(t_graphe));//Allocation dynamique
    Newgraphe->pSommet = (pSommet *)malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++)
    {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}
