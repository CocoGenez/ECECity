#include "biblio.h"
#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"

int menu(BITMAP* page,BITMAP* detection)
{
    install_mouse();
    show_mouse(screen);

    rectfill(detection,251,479,773,545,makecol(255,0,0));//NEW PARTIE
    rectfill(detection,251,559,773,625,makecol(0,255,0));//CHARGER
    rectfill(detection,251,638,773,704,makecol(0,0,255));// QUITTER

    int modedejeu=0;
    int couleurpixel;
    while(!key[KEY_ESC])
    {
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        if(mouse_b==1)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if(getr(couleurpixel)==255 && getg(couleurpixel)==0 && getb(couleurpixel)==0)
            {
                modedejeu=nouvellepartie(page,detection);
                return modedejeu;
            }
            if(getr(couleurpixel)==0 && getg(couleurpixel)==255 && getb(couleurpixel)==0)
            {

                return modedejeu=3;

            }
            if(getr(couleurpixel)==0 && getg(couleurpixel)==0 && getb(couleurpixel)==255)
            {
                exit(1);
            }
        }
    }
}

int nouvellepartie(BITMAP* page, BITMAP* detection)
{

    clear_bitmap(detection);
    //clear_bitmap(page);

    install_mouse();
    show_mouse(screen);
    rectfill(detection,251,479,773,545,makecol(255,0,0));//CAPITALISTE
    rectfill(detection,251,559,773,625,makecol(0,255,0));//COMMUNISTE
    int modedejeu;
    int couleurpixel;
    while(!key[KEY_ESC])
    {
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(mouse_b==2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if(getr(couleurpixel)==255 && getg(couleurpixel)==0 && getb(couleurpixel)==0)
            {
                return modedejeu=1;
            }
            if(getr(couleurpixel)==0 && getg(couleurpixel)==255 && getb(couleurpixel)==0)
            {
                return modedejeu=2;
            }
        }
    }
}

void init_structure(t_bat* batiment, t_graphe* reseau){
    FILE* f = fopen("batiments.txt", "r");
    
    batiment[0].x1 = 0;
    batiment[0].x2 = batiment[0].x1 + 60;
    batiment[0].y2 = batiment[0].y1 + 60;
    fscanf(f, "%d", &batiment[0].habitant);
    batiment[0].prix = 1000;
    strcpy(batiment[0].nom,"terrain_vague");

    batiment[1].x1 = 0;
    batiment[1].x2 = batiment[1].x1 + 60;
    batiment[1].y2 = batiment[1].y1 + 60;
    fscanf(f, "%d", &batiment[1].habitant);
    strcpy(batiment[1].nom,"cabane");

    batiment[2].x1 = 0;
    batiment[2].x2 = batiment[2].x1 + 60;
    batiment[0].y2 = batiment[2].y1 + 60;
    fscanf(f, "%d", &batiment[2].habitant);
    strcpy(batiment[2].nom,"maison");

    batiment[3].x1 = 0;
    batiment[3].x2 = batiment[3].x1 + 60;
    batiment[3].y2 = batiment[3].y1 + 60;
    fscanf(f, "%d", &batiment[3].habitant);
    strcpy(batiment[3].nom,"immeuble");

    batiment[4].x1 = 0;
    batiment[4].x2 = batiment[4].x1 + 60;
    batiment[4].y2 = batiment[4].y1 + 60;
    fscanf(f, "%d", &batiment[4].habitant);
    strcpy(batiment[4].nom,"gratte_ciel");

    reseau->centrale.x2 = reseau->centrale.x1 + 80;
    reseau->centrale.y2 = reseau->centrale.y1 + 120;
    reseau->centrale.capacite = 5000;
    reseau->centrale.prix = 100000;

    reseau->chateau.x2 = reseau->chateau.x1 + 80;
    reseau->chateau.y2 = reseau->chateau.y1 + 120;
    reseau->chateau.capacite = 5000;
    reseau->chateau.prix = 100000;
}

int main()
{
    BITMAP* page;
    BITMAP* detection;
    BITMAP* accueil;

    int modedejeu=0;

    t_bat* batiment;
    batiment=(t_bat*)malloc(5*sizeof(t_bat));
    t_graphe* reseau;
    reseau=(t_graphe*)malloc(1*sizeof(t_graphe));
    struct joueur player;

    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(screen);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    accueil = load_bitmap("home.bmp",NULL);
    detection = create_bitmap(SCREEN_W,SCREEN_H);
    page = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    rectfill(detection,251,479,773,545,makecol(255,0,0));//NEW PARTIE
    rectfill(detection,251,559,773,625,makecol(0,255,0));//CHARGER
    rectfill(detection,251,638,773,704,makecol(0,0,255));// QUITTER

    if (!accueil)
    {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ESC])
    {
        blit(accueil,page,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        show_mouse(screen);
        while(modedejeu==0)
        {
            modedejeu=menu(page,detection);
        }

        clear_bitmap(detection);
        clear_bitmap(page);
        //placer l'image, la detection et initialiser taille des batiments l et L pareil pour centrale et chateau
        //pour relier des batiments entre eux il faut chopper les intervalles de coordonnes pour trouver le chemin le plus proche
        //pour les centrales et chateaux, on prend leur centre donc x2-x1/2 et y2-y1/2


        if(modedejeu==1)
        {
            //CAPITALISTE
            init_structure(batiment,reseau);
            printf("habitants cabanes : %s",batiment[0].nom);
        }
        else if(modedejeu==2)
        {
            //COMMUNISTE
        }
        else if(modedejeu==3)
        {
            //CHARGER UNE PARTIE
            //recuperer les donnes et les affilier.
        }

    }
    return 0;
}
END_OF_MAIN();
