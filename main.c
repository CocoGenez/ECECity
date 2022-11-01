#include "biblio.h"
#include "stdio.h"
#include "stdlib.h"
#include "allegro.h"

volatile int timer;
void incrementer_timer()
{
    timer++;
}
END_OF_FUNCTION(incrementer_timer)

int menu(BITMAP *page, BITMAP *detection)
{
    install_mouse();
    show_mouse(screen);

    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255)); // QUITTER

    int modedejeu = 0;
    int couleurpixel;
    while (!key[KEY_ESC])
    {
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b == 1)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                modedejeu = nouvellepartie(page, detection);
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
}

int nouvellepartie(BITMAP *page, BITMAP *detection)
{

    clear_bitmap(detection);
    // clear_bitmap(page);

    install_mouse();
    show_mouse(screen);
    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // CAPITALISTE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // COMMUNISTE
    int modedejeu;
    int couleurpixel;
    while (!key[KEY_ESC])
    {
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                return modedejeu = 1;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 255 && getb(couleurpixel) == 0)
            {
                return modedejeu = 2;
            }
        }
    }
}

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

void mode_capitaliste(BITMAP *page, BITMAP *detection, t_bat *batiment, t_joueur *player)
{

    BITMAP *iconbat;
    iconbat = load_bitmap("cabane.bmp", NULL);
    t_case case_actu;
    t_case **plateau;
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    install_mouse();
    install_timer();
    show_mouse(screen);

    player->argent = 500000;
    player->nbhabitant = 0;

    timer = 0;
    int minutes = 0;
    int condi = 0;
    int marqueur = timer;
    LOCK_FUNCTION(incrementer_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementer_timer, MSEC_TO_TIMER(1));
    printf("yo");

    while (!key[KEY_ESC])
    {
        rectfill(detection, 0, 540, 60, 600, makecol(254, 0, 0));
        int couleurpixel;
        blit(iconbat, page, 0, 0, 0, 540, SCREEN_W, SCREEN_H);
        textprintf_centre_ex(page, font, SCREEN_W / 2 - 25, 10, makecol(255, 255, 255), -1, "%d :", minutes);
        textprintf_centre_ex(page, font, SCREEN_W / 2, 10, makecol(255, 255, 255), -1, "%d", timer / 1000);
        textprintf_centre_ex(page, font, 100, 50, makecol(255, 255, 255), -1, "%d ECEflouz", player->argent);
        textprintf_centre_ex(page, font, 500, 50, makecol(255, 255, 255), -1, "%d", player->nbhabitant);
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
                new.niveau=0;
                new.habitant = batiment[0].habitant;
                // printf("%d", player->propriete[0].prix);
                if (player->propriete[0].prix != 1000)
                {
                    player->propriete[0] = new;
                    player->nbpropriete=1;
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
                            player->nbpropriete+=1;
                            player->propriete = (t_bat *)malloc(i * sizeof(t_bat));
                            player->propriete = temp;
                            player->propriete[i] = new;
                            player->propriete[i].marqueur = timer;
                            i = 32;
                        }
                    }
                }
                for (int z = 0; z < player->nbpropriete; z++)
                {
                    if (timer - player->propriete[z].marqueur >= 15000)
                    {
                        player->propriete[z].habitant=batiment[player->propriete[z].niveau+1].habitant;
                        player->propriete[z].niveau+=1;
                        player->nbhabitant+=(batiment[player->propriete[z].niveau+1].habitant-batiment[player->propriete[z].niveau].habitant);
                        marqueur = timer;
                    }
                    
                }
                if (timer >= 60000)
                    {
                       
                        timer = 0;
                        marqueur = timer;
                        minutes += 1;
                    }
            }
        }
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear(page);
    }
}

int main()
{
    BITMAP *page;
    BITMAP *detection;
    BITMAP *accueil;

    int modedejeu = 0;

    t_bat *batiment;
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(1 * sizeof(t_bat));
    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(screen);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0) != 0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    set_window_title("ECE City");

    accueil = load_bitmap("home.bmp", NULL);
    detection = create_bitmap(SCREEN_W, SCREEN_H);
    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0)); // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0)); // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255)); // QUITTER

    if (!accueil)
    {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ESC])
    {
        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        show_mouse(screen);
        while (modedejeu == 0)
        {
            modedejeu = menu(page, detection);
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

            mode_capitaliste(page, detection, batiment, player);
        }
        else if (modedejeu == 2)
        {
            // COMMUNISTE
            init_structure(batiment, reseau);
        }
        else if (modedejeu == 3)
        {
            // CHARGER UNE PARTIE
            // recuperer les donnes et les affilier.
        }
    }
    return 0;
}
END_OF_MAIN();
