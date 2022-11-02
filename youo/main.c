#include "biblio.h"
/**Timer pour gerer les cycles***/
volatile int timer;
void incrementer_timer()
{
    timer++;
}
END_OF_FUNCTION(incrementer_timer)
/***Detecte chaque case***/
t_case detecterCase(t_case **plateau)
{
    t_case casecliquee;
    int xsouris = 0;
    int ysouris = 0;
    int casechoisie_x = 0;
    int casechoisie_y = 0;
    if (mouse_b == 1)
    {
        xsouris = (mouse_x) / 20;
        ysouris = (mouse_y) / 20;
        if (xsouris <= 44 && xsouris >= 0 && ysouris <= 34 && ysouris >= 0)
        {
            casechoisie_x = xsouris;
            casechoisie_y = ysouris;
            casecliquee = plateau[casechoisie_y][casechoisie_x];
            return casecliquee;
        }
    }
    // blit(pagetemp, decor, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
/***Mode de jeu capitaliste***/
void mode_capitaliste(BITMAP *page, BITMAP *detection, t_bat *batiment, t_joueur *player,BITMAP* map)
{

    BITMAP *iconbat;
    player->nbhabitant=0;
    iconbat = charger_Bitmap("cabane.bmp");
    t_case case_actu;
    t_case **plateau;
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    player->argent = 500000;
    player->nbhabitant = 0;
    timer = 0;
    int minutes = 0;
    int condi = 0;
    int marqueur = timer;
    LOCK_FUNCTION(incrementer_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementer_timer, MSEC_TO_TIMER(1));

    while (!key[KEY_ESC])
    {
        rectfill(detection, 0, 540, 60, 600, makecol(254, 0, 0));
        int couleurpixel;
        blit(map,page,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(iconbat, page, 0, 0, 0, 540, SCREEN_W, SCREEN_H);
        textprintf_centre_ex(page, font, 930, 726, makecol(0, 0, 0), -1, "%d :", minutes);
        textprintf_centre_ex(page, font, 960, 726, makecol(0, 0 ,0), -1, "%d", timer / 1000);
        textprintf_centre_ex(page, font, 750, 726, makecol(0, 0, 0), -1, "%d ECEflouz", player->argent);
        textprintf_centre_ex(page, font, 250, 726, makecol(0, 0, 0), -1, "%d", player->nbhabitant);
        textprintf_centre_ex(page, font, 100, 500, makecol(255, 255, 255), -1, "souris : %d %d", mouse_x, mouse_y);


        condi = 0;

        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {

                while (condi == 0)
                {
                    case_actu.x1 = 0;
                    case_actu = detecterCase(plateau);
                    if (case_actu.x1 != 0)
                        condi = 1;
                }
                player->argent -= 1000;

                t_bat new;
                new.x1 = case_actu.x1;
                new.x2 = case_actu.x2;
                new.y1 = case_actu.y1; // intialisation nouvelle case
                new.y2 = case_actu.y2;
                strcpy(new.nom, batiment[0].nom);
                new.prix = batiment[0].prix,
                new.niveau = 0;
                new.habitant = batiment[0].habitant;

                if (player->propriete[0].prix != 1000)
                {
                    player->propriete[0] = new;
                    player->nbpropriete = 1;
                    player->propriete[0].marqueur = timer;
                    printf("%d", player->propriete[0].x1);
                }
                else if (player->propriete[0].prix == 1000)
                {
                    for (int i = 0; i < 30; i++)
                    {

                        if (player->propriete[i].prix != 1000)
                        { // condition verifiant si la propriete existe deja
                            t_bat *temp;
                            temp = player->propriete;
                            player->nbpropriete += 1;
                            player->propriete = (t_bat *)malloc(i * sizeof(t_bat));
                            player->propriete = temp;
                            player->propriete[i] = new;
                            player->propriete[i].marqueur = timer;
                            i = 32;
                        }
                    }
                }
            }
        }
        for (int z = 0; z < player->nbpropriete; z++)
        {
            printf("%d : %d \n", z, player->propriete[z].niveau);
            printf("%d : %d \n", z, batiment[player->propriete[z].niveau + 1].habitant-batiment[player->propriete[z].niveau].habitant);
            //printf("%d : %d \n", z, batiment[player->propriete[z].niveau].habitant);
            if (timer - player->propriete[z].marqueur >= 15000 && timer - player->propriete[z].marqueur <= 15100 && player->propriete[z].niveau < 4)
            {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
                player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].niveau += 1;
                player->propriete[z].marqueur = timer;
            }
        }
        if (timer >= 60000)
        {

            timer = 0;
            marqueur = timer;
            minutes += 1;
        }
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear(page);
    }
}

int main()
{
    initialisation_allegro();
    BITMAP *page;
    BITMAP *detection;
    BITMAP *accueil;
    BITMAP* map;
    int modedejeu = 0;
    t_bat *batiment;
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(1 * sizeof(t_bat));
    accueil = charger_Bitmap("home.bmp");
    detection = creer_Bitmap(SCREEN_W, SCREEN_H);
    page = creer_Bitmap(SCREEN_W, SCREEN_H);
    map=charger_Bitmap("ingame.bmp");

    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255)); // QUITTER

    while (!key[KEY_ESC])
    {
        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        show_mouse(screen);
        while (modedejeu == 0)
        {
            modedejeu = menu(page, detection,accueil);
        }

        clear_bitmap(detection);
        clear_bitmap(page);
        // placer l'image, la detection et initialiser taille des batiments l et L pareil pour centrale et chateau
        // pour relier des batiments entre eux il faut chopper les intervalles de coordonnes pour trouver le chemin le plus proche
        // pour les centrales et chateaux, on prend leur centre donc x2-x1/2 et y2-y1/2

        if (modedejeu == 1)
        {
            // CAPITALISTE

            init_structure(batiment, reseau);

            mode_capitaliste(page, detection, batiment, player,map);
        }
        else if (modedejeu == 2)
        {
            // COMMUNISTE
            init_structure(batiment, reseau);
            //mode_capitaliste(page, detection, batiment, player,map);

        }
        else if (modedejeu == 3)
        {
            // CHARGER UNE PARTIE
            // recuperer les donnes et les affilier.
        }
    }
    /*free(batiment);NE PAS OUBLIER DE FREE, PEUT ETRE RAISON DES  CRASH
    free(reseau);
    free(player);*/
    return 0;
}
END_OF_MAIN();
