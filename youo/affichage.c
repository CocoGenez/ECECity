#include "biblio.h"
/***Pour le click du Menu***/
int clicInMenu(BITMAP *detectionAccueil, int couleurPixel)
{
    if (getr(couleurPixel) == 255 && getg(couleurPixel) == 0 && getb(couleurPixel) == 0)
    {
        printf("\nAffichage du mode de jeu.");
        return 1;

    }
    else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 255 && getb(couleurPixel) == 0)
    {
        printf("\nAffichage du chargement d'une partie.");
        return 3;

    }
    else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 0 && getb(couleurPixel) == 255)
    {
        exit(1);
    }
    else
    {
        return 0;
    }
}
/***Pour choisir parmi les 15  routes dans le jeu ***/
int choix_panel(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, BITMAP *map, BITMAP *page, BITMAP *panel, BITMAP *detection)
{
    int choix = 0,z;
    int couleurpixel;
    rectfill(detection, 148, 124, 188, 164, makecol(0, 0, 255));
    rectfill(detection, 201, 124, 241, 164, makecol(0, 0, 254));
    rectfill(detection, 254, 124, 294, 164, makecol(0, 0, 253));
    rectfill(detection, 307, 124, 347, 164, makecol(0, 0, 252));
    rectfill(detection, 148, 173, 188, 213, makecol(0, 0, 251));
    rectfill(detection, 201, 173, 241, 213, makecol(0, 0, 250));
    rectfill(detection, 254, 173, 294, 213, makecol(0, 0, 249));
    rectfill(detection, 307, 173, 347, 213, makecol(0, 0, 248));
    rectfill(detection, 148, 224, 188, 264, makecol(0, 0, 247));
    rectfill(detection, 201, 224, 241, 264, makecol(0, 0, 246));
    rectfill(detection, 254, 224, 294, 264, makecol(0, 0, 245));
    rectfill(detection, 307, 224, 347, 264, makecol(0, 0, 244));
    rectfill(detection, 148, 275, 188, 315, makecol(0, 0, 243));
    rectfill(detection, 201, 275, 241, 315, makecol(0, 0, 242));
    rectfill(detection, 148, 326, 188, 366, makecol(0, 0, 241));
    while(choix==0)
    {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        for (z = 0; z < player->nbpropriete; z++)
        {

            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        }

        for (z = 0; z < player->nbroute; z++)
        {

            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        blit(panel, page, 0, 0, 124, 100, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if(key[KEY_SPACE])//Tant que pas espace on reste dans le choix des routes
            return 25;
        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 255)
            {
                return 0;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 254)
            {
                return 1;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 253)
            {
                return 2;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 252)
            {
                return 3;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 251)
            {
                return 4;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 250)
            {
                return 5;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 249)
            {
                return 6;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 248)
            {
                return 7;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 247)
            {
                return 8;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 246)
            {
                return 9;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 245)
            {
                return 10;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 244)
            {
                return 11;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 243)
            {
                return 12;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 242)
            {
                return 13;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 241)
            {
                return 14;
            }
        }
    }
    return 99;
}
/***Choix du mode de jeu entre communiste et capitaliste***/
void selectionModeDeJeu()
{
    BITMAP *gamemode = charger_Bitmap("gamemode.bmp");
    BITMAP *communisteIMG = charger_Bitmap("communiste_selected.bmp");
    BITMAP *capitalisteIMG = charger_Bitmap("capitaliste_selected.bmp");
    BITMAP *validerHover = charger_Bitmap("images_menu/validerHover.bmp");
    BITMAP *retourHover = charger_Bitmap("images_menu/retourHover.bmp");
    BITMAP *page = creer_Bitmap(SCREEN_W, SCREEN_H);
    BITMAP *detectionGamemode = creer_Bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    rectfill(detectionGamemode, 345, 459, 720, 496, makecol(255, 0, 0));  // CAPITALISTE
    rectfill(detectionGamemode, 345, 505, 720, 549, makecol(0, 255, 0));  // COMMUNISTE
    rectfill(detectionGamemode, 519, 576, 701, 620, makecol(0, 1, 255));  // VALIDER
    rectfill(detectionGamemode, 319, 576, 501, 620, makecol(0, 2, 255));  // RETOUR

    int fenetre = 1;
    int modeDeJeu = 0;
    int couleurPixel;

    while (!key[KEY_ESC] && fenetre == 1)
    {
        if (mouse_b == 2 && fenetre == 1)    // SI un clic est détecté dans la page du mode de jeu
        {
            couleurPixel = getpixel(detectionGamemode, mouse_x, mouse_y);

            if (getr(couleurPixel) == 255 && getg(couleurPixel) == 0 && getb(couleurPixel) == 0)
            {

                modeDeJeu = 0;

            }
            else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 255 && getb(couleurPixel) == 0)
            {

                modeDeJeu = 1;

            }
            else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 1 && getb(couleurPixel) == 255)
            {
                fenetre = 2;

            }
            else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 2 && getb(couleurPixel) == 255)
            {
                fenetre = 0;
            }
        }

        blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (modeDeJeu == 0)
        {
            blit(capitalisteIMG, page, 0, 0, 299, 451, SCREEN_W, SCREEN_H);
        }
        else if (modeDeJeu == 1)
        {
            blit(communisteIMG, page, 0, 0, 299, 497, SCREEN_W, SCREEN_H);
        }

        if (mouse_x >= 519 && mouse_y >= 576 && mouse_x <= 701 && mouse_y <= 620)
        {
            blit(validerHover, page, 0, 0, 519, 576, SCREEN_W, SCREEN_H);

        }
        else if (mouse_x >= 319 && mouse_y >= 576 && mouse_x <= 501 && mouse_y <= 620)
        {
            blit(retourHover, page, 0, 0, 319, 576, SCREEN_W, SCREEN_H);
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    if (fenetre == 0)
    {
        monMenu();
    }
    else if (fenetre == 2)
    {
        if (modeDeJeu == 0)
        {
            mode_capitaliste();
        }
        else if (modeDeJeu == 1)
        {
            mode_communiste();
        }
        else
        {
            printf("\nMode de jeu invalide.");
            exit(EXIT_FAILURE);
        }
    }
}
/***Menu du jeu avec affichage graphique***/
void monMenu()
{
    BITMAP *page = creer_Bitmap(SCREEN_W, SCREEN_H);
    BITMAP *detectionAccueil = creer_Bitmap(SCREEN_W, SCREEN_H);
    BITMAP *accueil = charger_Bitmap("home.bmp");
    BITMAP *nouvellePartieHover = charger_Bitmap("images_menu/newGameHover.bmp");
    BITMAP *chargerPartieHover = charger_Bitmap("images_menu/loadGameHover.bmp");
    BITMAP *quitterPartieHover = charger_Bitmap("images_menu/leaveGameHover.bmp");
    BITMAP* regles = charger_Bitmap("regles.bmp");
    clear_bitmap(page);
    int fenetre = 0;

    rectfill(detectionAccueil, 251, 479, 773, 545, makecol(255, 0, 0));  // NEW PARTIE
    rectfill(detectionAccueil, 251, 559, 773, 625, makecol(0, 255, 0));  // CHARGER
    rectfill(detectionAccueil, 251, 638, 773, 704, makecol(0, 0, 255));  // QUITTER

    while (!key[KEY_ESC] && fenetre == 0)
    {
        while(key[KEY_R])
        {
            blit(regles, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        if (mouse_b == 1 && fenetre == 0)    // SI un clic est détecté dans le menu
        {
            fenetre = clicInMenu(detectionAccueil, getpixel(detectionAccueil, mouse_x, mouse_y));
        }

        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_x >= 251 && mouse_y >= 479 && mouse_x <= 773 && mouse_y <= 545)
        {
            blit(nouvellePartieHover, page, 0, 0, 251, 479, SCREEN_W, SCREEN_H);

        }
        else if (mouse_x >= 251 && mouse_y >= 559 && mouse_x <= 773 && mouse_y <= 625)
        {
            blit(chargerPartieHover, page, 0, 0, 251, 559, SCREEN_W, SCREEN_H);

        }
        else if (mouse_x >= 251 && mouse_y >= 638 && mouse_x <= 773 && mouse_y <= 704)
        {
            blit(quitterPartieHover, page, 0, 0, 251, 638, SCREEN_W, SCREEN_H);
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    if (fenetre == 1)
    {
        selectionModeDeJeu();
    }
    else if (fenetre == 3)
    {

        exit(EXIT_FAILURE);
    }
}
