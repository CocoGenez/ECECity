#include "biblio.h"
int menu(BITMAP *page, BITMAP *detection,BITMAP* accueil)
{

    clear_bitmap(detection);
    clear_bitmap(page);
    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255)); // QUITTER

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

                return modedejeu = 3;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 255)
            {
                exit(1);
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
