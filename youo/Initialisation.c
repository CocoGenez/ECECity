#include "biblio.h"

/****Pour initialiser allegro(souris,clavier...)***/
void initialisation_allegro()
{
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    set_uformat(U_ASCII);//accent
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("Prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);//son
    set_config_int("sound", "quality", 1);
    set_window_title("ECE City");
    install_timer();    

}
/*** creer les bITMAP en verifiant qu'il y a d'erreur***/
BITMAP * creer_Bitmap(int width,int height){
    BITMAP*nvx = create_bitmap(width,height);
    if(!nvx){
         allegro_message("Probleme lors de la création de la BITMAP!!");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    clear_bitmap(nvx);
    return nvx;
}
/***Charge les bITMAP en verifiant qu'il y a d'erreur***/
BITMAP * charger_Bitmap(const char*chemin){
    BITMAP*nvx = load_bitmap(chemin,NULL);
    if(!nvx){
         allegro_message("Probleme lors du chargement de la BITMAP!!");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return nvx;
}
/***Initialise les cases de la map***/
void initcase(t_case **plateau)
{

    int depx1 = 0, depx2 = 20, depy1 = 0, depy2 = 20;
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            plateau[i][j].x1 = depx1;
            depx1 += 20;
            plateau[i][j].x2 = depx2;
            depx2 += 20;
            plateau[i][j].y1 = depy1;
            plateau[i][j].y2 = depy2;
        }
        depx1 = 0;
        depx2 = 20;
        depy1 += 20;
        depy2 += 20;
    }
}
/***Initialisation des structures***/
void init_structure(t_bat *batiment, t_graphe *reseau)
{
    FILE *f = fopen("batiments.txt", "r");

    batiment[0].x1 = 0;
    batiment[0].x2 = batiment[0].x1 + 60;
    batiment[0].y2 = batiment[0].y1 + 60;
    fscanf(f, "%d", &batiment[0].habitant);
    batiment[0].prix = 1000;
    strcpy(batiment[0].nom, "terrain_vague");

    batiment[1].x1 = 0;
    batiment[1].x2 = batiment[1].x1 + 60;
    batiment[1].y2 = batiment[1].y1 + 60;
    fscanf(f, "%d", &batiment[1].habitant);
    strcpy(batiment[1].nom, "cabane");

    batiment[2].x1 = 0;
    batiment[2].x2 = batiment[2].x1 + 60;
    batiment[0].y2 = batiment[2].y1 + 60;
    fscanf(f, "%d", &batiment[2].habitant);
    strcpy(batiment[2].nom, "maison");

    batiment[3].x1 = 0;
    batiment[3].x2 = batiment[3].x1 + 60;
    batiment[3].y2 = batiment[3].y1 + 60;
    fscanf(f, "%d", &batiment[3].habitant);
    strcpy(batiment[3].nom, "immeuble");

    batiment[4].x1 = 0;
    batiment[4].x2 = batiment[4].x1 + 60;
    batiment[4].y2 = batiment[4].y1 + 60;
    fscanf(f, "%d", &batiment[4].habitant);
    strcpy(batiment[4].nom, "gratte_ciel");

    reseau->centrale.x2 = reseau->centrale.x1 + 80;
    reseau->centrale.y2 = reseau->centrale.y1 + 120;
    reseau->centrale.capacite = 5000;
    reseau->centrale.prix = 100000;

    reseau->chateau.x2 = reseau->chateau.x1 + 80;
    reseau->chateau.y2 = reseau->chateau.y1 + 120;
    reseau->chateau.capacite = 5000;
    reseau->chateau.prix = 100000;
}
