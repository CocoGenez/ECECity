#include "biblio.h"
int menu(BITMAP *page, BITMAP *detection,BITMAP* accueil)
{

    clear_bitmap(detection);
    clear_bitmap(page);
    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255)); // QUITTER
    t_joueur *player;
    int modedejeu = 0;
    int couleurpixel;
    while (!key[KEY_ESC])
    {
        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


        if (mouse_b == 1)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                modedejeu = nouvellepartie(page, detection,accueil);
                return modedejeu;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 255 && getb(couleurpixel) == 0)
            {
                charger_sauvegarde(player);
                modedejeu = nouvellepartie(page, detection,accueil);
                return modedejeu ;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 255)
            {
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}

int nouvellepartie(BITMAP *page, BITMAP *detection,BITMAP* accueil)
{

    clear_bitmap(detection);
    clear_bitmap(page);
    BITMAP *gamemode;
    BITMAP *capita;
    BITMAP *commu;
    capita = charger_Bitmap("capitaliste_selected.bmp");
    commu = charger_Bitmap("communiste_selected.bmp");
    gamemode = charger_Bitmap("gamemode.bmp");
    blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


    rectfill(detection, 345, 459, 720, 496, makecol(255, 0, 0)); // CAPITALISTE
    rectfill(detection, 345, 505, 720, 549, makecol(0, 255, 0)); // COMMUNISTE
    rectfill(detection, 519, 576, 701, 620, makecol(254, 245, 0));
    rectfill(detection, 319, 576, 501, 620, makecol(0, 0, 254));
    int modedejeu;
    int couleurpixel;

    while (!key[KEY_ESC])
    {
        //blit(detection,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                clear_bitmap(page);
                blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                blit(capita, page, 0, 0, 299, 451, SCREEN_W, SCREEN_H);
                modedejeu = 1;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 255 && getb(couleurpixel) == 0)
            {
                clear_bitmap(page);
                blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                blit(commu, page, 0, 0, 299, 497, SCREEN_W, SCREEN_H);
                modedejeu = 2;
            }

            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 245 && getb(couleurpixel) == 0)
            {
                return modedejeu;
            }

            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 254)
            {
                menu(page, detection,accueil);
            }
        }
    }
    return 0;
}
/*** menu pause a finir ***/
int menu_pause()
{
    clear_bitmap(screen);
    BITMAP *pause;
    pause = creer_Bitmap(SCREEN_W,SCREEN_H);
    int retour_jeu = 1;
    rest(100);
    while (retour_jeu != 0 )
    {

        show_mouse(pause);
        blit(pause,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rectfill(pause, 250, 200, 550, 250, makecol(255,255,255));
        rectfill(pause, 250, 300, 550, 350, makecol(255,255,255));
        rectfill(pause, 250, 400, 550, 450, makecol(255,255,255));
        textprintf_ex(pause,font,300,225,makecol(0,0,0),-1,"Reprendre Partie");
        textprintf_ex(pause,font,300,325,makecol(0,0,0),-1,"sauvegarder");
        textprintf_ex(pause,font,300,425,makecol(0,0,0),-1,"Revenir au menu Principale");
        if (mouse_b == 2 && ((mouse_x>250)&&(mouse_x<550))&&(mouse_y>200)&&(mouse_y<250) )
        {
            return 3;
        }
        if (mouse_b == 2 && ((mouse_x>250)&&(mouse_x<550))&&(mouse_y>300)&&(mouse_y<350) )
        {
            //sauvegarder la partie
        }
        if (mouse_b == 2 && ((mouse_x>250)&&(mouse_x<550))&&(mouse_y>400)&&(mouse_y<450) )
        {
            return 1;
        }

    }
    return 0;
}

