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

int menu(BITMAP *page, BITMAP *detection, BITMAP *accueil)
{
    install_mouse();
    show_mouse(screen);
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
                modedejeu = nouvellepartie(page, detection, accueil);
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

int nouvellepartie(BITMAP *page, BITMAP *detection, BITMAP *accueil)
{

    clear_bitmap(detection);
    clear_bitmap(page);
    BITMAP *gamemode;
    BITMAP *capita;
    BITMAP *commu;
    capita = load_bitmap("capitaliste_selected.bmp", NULL);
    commu = load_bitmap("communiste_selected.bmp", NULL);
    gamemode = load_bitmap("gamemode.bmp", NULL);
    blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    install_mouse();
    show_mouse(screen);

    rectfill(detection, 345, 459, 720, 496, makecol(255, 0, 0)); // CAPITALISTE
    rectfill(detection, 345, 505, 720, 549, makecol(0, 255, 0)); // COMMUNISTE
    rectfill(detection, 519, 576, 701, 620, makecol(254, 245, 0));
    rectfill(detection, 319, 576, 501, 620, makecol(0, 0, 254));
    int modedejeu;
    int couleurpixel;
    int matthieu = 0;
    while (!key[KEY_ESC])
    {
        // blit(detection,screen,0,0,0,0,SCREEN_W,SCREEN_H);
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
                menu(page, detection, accueil);
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
    batiment[0].icone = load_bitmap("images_structure/habitation/terrain_vague.bmp", NULL);

    batiment[1].x1 = 0;
    batiment[1].x2 = batiment[1].x1 + 60;
    batiment[1].y2 = batiment[1].y1 + 60;
    fscanf(f, "%d", &batiment[1].habitant);
    strcpy(batiment[1].nom, "cabane");
    batiment[1].icone = load_bitmap("images_structure/habitation/cabane.bmp", NULL);

    batiment[2].x1 = 0;
    batiment[2].x2 = batiment[2].x1 + 60;
    batiment[0].y2 = batiment[2].y1 + 60;
    fscanf(f, "%d", &batiment[2].habitant);
    strcpy(batiment[2].nom, "maison");
    batiment[2].icone = load_bitmap("images_structure/habitation/maison.bmp", NULL);

    batiment[3].x1 = 0;
    batiment[3].x2 = batiment[3].x1 + 60;
    batiment[3].y2 = batiment[3].y1 + 60;
    fscanf(f, "%d", &batiment[3].habitant);
    strcpy(batiment[3].nom, "immeuble");
    batiment[3].icone = load_bitmap("images_structure/habitation/immeuble.bmp", NULL);

    batiment[4].x1 = 0;
    batiment[4].x2 = batiment[4].x1 + 60;
    batiment[4].y2 = batiment[4].y1 + 60;
    fscanf(f, "%d", &batiment[4].habitant);
    strcpy(batiment[4].nom, "gratte_ciel");
    batiment[4].icone = load_bitmap("images_structure/habitation/gratte_ciel.bmp", NULL);

    reseau->centrale->x2 = reseau->centrale->x1 + 80;
    reseau->centrale->y2 = reseau->centrale->y1 + 120;
    reseau->centrale->capacite = 5000;
    reseau->centrale->prix = 100000;
    batiment->elec.iconeelec = load_bitmap("images_structure/centrale_electrique.bmp", NULL);

    reseau->chateau->x1 = 0;
    reseau->chateau->x2 = reseau->chateau->x1 + 80;
    reseau->chateau->y2 = reseau->chateau->y1 + 120;
    reseau->chateau->capacite = 5000;
    reseau->chateau->prix = 100000;
    batiment->water.iconeeau = load_bitmap("images_structure/chateau_eau.bmp", NULL);

    reseau->chaussee->prix = 10;
    reseau->chaussee->iconeroute[0] = load_bitmap("images_structure/routes/virage1.bmp", NULL);
    reseau->chaussee->iconeroute[1] = load_bitmap("images_structure/routes/virage4.bmp", NULL);
    reseau->chaussee->iconeroute[2] = load_bitmap("images_structure/routes/virage3.bmp", NULL);
    reseau->chaussee->iconeroute[3] = load_bitmap("images_structure/routes/virage2.bmp", NULL);
    reseau->chaussee->iconeroute[4] = load_bitmap("images_structure/routes/impasse3.bmp", NULL);
    reseau->chaussee->iconeroute[5] = load_bitmap("images_structure/routes/impasse2.bmp", NULL);
    reseau->chaussee->iconeroute[6] = load_bitmap("images_structure/routes/impasse4.bmp", NULL);
    reseau->chaussee->iconeroute[7] = load_bitmap("images_structure/routes/impasse1.bmp", NULL);
    reseau->chaussee->iconeroute[8] = load_bitmap("images_structure/routes/virage_double1.bmp", NULL);
    reseau->chaussee->iconeroute[9] = load_bitmap("images_structure/routes/virage_double4.bmp", NULL);
    reseau->chaussee->iconeroute[10] = load_bitmap("images_structure/routes/virage_double3.bmp", NULL);
    reseau->chaussee->iconeroute[11] = load_bitmap("images_structure/routes/virage_double2.bmp", NULL);
    reseau->chaussee->iconeroute[12] = load_bitmap("images_structure/routes/normal1.bmp", NULL);
    reseau->chaussee->iconeroute[13] = load_bitmap("images_structure/routes/normal2.bmp", NULL);
    reseau->chaussee->iconeroute[14] = load_bitmap("images_structure/routes/carrefour.bmp", NULL);
}

t_case detecterCase(t_case **plateau, BITMAP *page, BITMAP *batiment, BITMAP *map, t_joueur *player)
{
    clear_bitmap(page);
    t_case casecliquee;
    int xsouris = 0;
    int ysouris = 0;
    int casechoisie_x = 0;
    int casechoisie_y = 0;
    while (casechoisie_x == 0)
    {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(page, batiment, mouse_x, mouse_y);
        for (int z = 0; z < player->nbroute; z++)
        {
            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        for (int z = 0; z < player->nbpropriete; z++)
        {
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        }
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b == 1)
        {
            xsouris = (mouse_x) / 20;
            ysouris = (mouse_y) / 20;
            if (xsouris <= 50 && xsouris >= 6 && ysouris <= 34 && ysouris >= 0)
            {
                casechoisie_x = xsouris - 6;
                casechoisie_y = ysouris;
                casecliquee = plateau[casechoisie_y][casechoisie_x];
                return casecliquee;
            }
        }
    }
    // blit(pagetemp, decor, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void initcase(t_case **plateau)
{

    int depx1 = 124, depx2 = 144, depy1 = 0, depy2 = 20;
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
        depx1 = 124;
        depx2 = 144;
        depy1 += 20;
        depy2 += 20;
    }
}

int verifOccupation(int **matrice, t_case caseactu, int mode)
{
    if (mode == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0)
                {
                    return 0;
                }
                caseactu.x1 += 20;
            }
            caseactu.y1 += 20;
            caseactu.x1 -= 80;
        }
    }
    else if (mode == 2)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0)
                {
                    return 0;
                }
                caseactu.x1 += 20;
            }
            caseactu.y1 += 20;
            caseactu.x1 -= 80;
        }
    }
    else if (mode == 3)
    {
        if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0)
        {
            return 0;
        }
    }
    return 1;
}

void mode_capitaliste(BITMAP *page, BITMAP *detection, t_bat *batiment, t_joueur *player, BITMAP *map, t_graphe *reseau)
{

    player->nbhabitant = 0;

    t_case case_actu;
    t_case **plateau;
    int **matriceJeu;
    matriceJeu = (int **)malloc(35 * sizeof(int *));
    for (int i = 0; i < 35; i++)
        matriceJeu[i] = (int *)malloc(45 * sizeof(int));
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            matriceJeu[i][j] = 0;
        }
    }
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    install_mouse();
    install_timer();
    show_mouse(screen);

    player->argent = 500000;
    player->nbhabitant = 0;
    BITMAP *panel;
    panel = load_bitmap("images_structure/panel/route_panel.bmp", NULL);
    if (!panel)
    {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }
    timer = 0;
    int minutes = 0;
    int secondes = 0;
    int condi = 0, condi2 = 0, condi3 = 0, condi4 = 0;

    int marqueur1 = timer;
    int marqueur2 = timer;
    int trucpourrouler;
    LOCK_FUNCTION(incrementer_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementer_timer, MSEC_TO_TIMER(1));

    while (!key[KEY_ESC])
    {
        clear_bitmap(detection);
        clear(page);
        rectfill(detection, 24, 202, 101, 279, makecol(254, 0, 0)); // batiment
        rectfill(detection, 24, 296, 101, 373, makecol(253, 0, 0)); // chateau
        rectfill(detection, 24, 390, 101, 467, makecol(252, 0, 0)); // caserne
        rectfill(detection, 24, 484, 101, 561, makecol(251, 0, 0)); // centrale
        rectfill(detection, 24, 108, 101, 185, makecol(250, 0, 0)); // panel route

        int couleurpixel;
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_centre_ex(page, font, 930, 726, makecol(0, 0, 0), -1, "%d :", minutes);
        textprintf_centre_ex(page, font, 960, 726, makecol(0, 0, 0), -1, "%d", secondes);
        textprintf_centre_ex(page, font, 750, 726, makecol(0, 0, 0), -1, "%d ECEflouz", player->argent);
        textprintf_centre_ex(page, font, 250, 726, makecol(0, 0, 0), -1, "%d", player->nbhabitant);
        textprintf_centre_ex(page, font, 100, 500, makecol(255, 255, 255), -1, "souris : %d %d", mouse_x, mouse_y);
        int condition[30] = {0};
        condi = 0;
        condi2 = 0;
        condi3 = 0;
        condi4 = 0;

        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > batiment[0].prix)
                {

                    while (condi == 0)
                    {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);
                        // creation_batiment(player, case_actu, batiment,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 1) == 1)
                    {
                        creation_batiment(player, case_actu, batiment, matriceJeu);
                    }
                }
                else
                {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 253 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > reseau->chateau->prix)
                {

                    while (condi2 == 0)
                    {
                        printf("/%d", condi2);
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);
                        // creation_chateau(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi2 = 1;
                    }
                    printf("/%d", condi2);
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_chateau(player, case_actu, batiment, reseau, matriceJeu);
                    }
                }
                else
                {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 251 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > reseau->centrale->prix)
                {

                    while (condi3 == 0)
                    {
                        printf("/%d", condi3);
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);
                        // creation_centrale(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi3 = 1;
                    }
                    printf("/%d", condi3);
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_centrale(player, case_actu, batiment, reseau, matriceJeu);
                    }
                }
                else
                {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > reseau->chaussee->prix)
                {

                    while (condi4 == 0)
                    {

                        trucpourrouler = choix_panel(player, case_actu, batiment, reseau, map, page, panel, detection);
                        if (trucpourrouler == 25)
                            break;
                        case_actu.x1 = 0;

                        case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);

                        if (verifOccupation(matriceJeu, case_actu, 3) == 1)
                        {
                            creation_route(player, case_actu, batiment, reseau, trucpourrouler, matriceJeu);
                        }
                    }
                }
                else
                {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
        }
        evolution_batiment(player, batiment, condition);
        /*
        if (timer >= 60000)
        {

            timer = 0;
            marqueur = timer;
            minutes += 1;
        }*/
        if (timer - marqueur1 >= 1000)
        {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000)
        {
            // timer = 0;
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        for (int z = 0; z < player->nbroute; z++)
        {

            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        for (int z = 0; z < player->nbpropriete; z++)
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    for (int i = 0; i < 35; i++)
        free(plateau[i]);
    free(plateau);
}
int choix_panel(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, BITMAP *map, BITMAP *page, BITMAP *panel, BITMAP *detection)
{
    int choix = 0, z;
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
    while (choix == 0)
    {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        for (z = 0; z < player->nbpropriete; z++)
        {
            printf("---%dTT%d---", player->nbpropriete, z);
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        }

        for (z = 0; z < player->nbroute; z++)
        {

            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        blit(panel, page, 0, 0, 124, 100, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (key[KEY_SPACE])
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
}

int creation_route(t_joueur *player, t_case case_actu, t_route *route, t_graphe *reseau, int number, int **matrice)
{
    player->argent -= 10;
    t_route new;
    new.x = case_actu.x1;
    new.y = case_actu.y1;
    matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = 2;

    new.prix = 10;
    new.truc = reseau->chaussee->iconeroute[number];
    if (player->bitume[0].prix != 10)
    {
        player->bitume[0] = new;
        player->nbroute = 1;
    }
    else if (player->bitume[0].prix == 10)
    {
        for (int i = 0; i < 200; i++)
        {

            if (player->bitume[i].prix != 10)
            { // condition verifiant si la propriete existe deja

                player->nbroute += 1;
                player->bitume[i] = new;
                player->bitume[i].prix = 10;
                i = 202;
            }
        }
    }
}
int evolution_batiment(t_joueur *player, t_bat *batiment, int *condition)
{
    for (int z = 0; z < player->nbpropriete; z++)
    {
        // printf("%d : %d \n", z, player->propriete[z].niveau);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau + 1].habitant-batiment[player->propriete[z].niveau].habitant);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau].habitant);
        if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau < 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0)
        {
            player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
            player->propriete[z].icone = batiment[player->propriete[z].niveau + 1].icone;
            player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
            player->propriete[z].niveau += 1;
            player->propriete[z].marqueur = timer;
            condition[z] = 1;
        }
    }
}
int creation_chateau(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice)
{
    player->argent -= 100000;
    t_bat new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1; // intialisation nouvelle case
    new.y2 = case_actu.y2;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = 1;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 80;
    }

    new.prix = 1000;
    new.chateau = 1;
    new.centrale = 0; // precise que c un chateau;
    new.icone = batiment->water.iconeeau;
    new.capacite = 5000;
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

                player->nbpropriete += 1;

                player->propriete[i] = new;
                i = 32;
            }
        }
    }
}
int creation_centrale(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice)
{
    player->argent -= 100000;
    t_bat new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1; // intialisation nouvelle case
    new.y2 = case_actu.y2;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = 1;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 80;
    }

    new.prix = 1000;
    new.chateau = 0;
    new.centrale = 1; // precise que c un chateau;
    new.icone = batiment->elec.iconeelec;
    new.capacite = 5000;
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

                player->nbpropriete += 1;
                player->propriete[i] = new;
                i = 32;
            }
            reseau->chateau->next = (t_eau *)malloc(1 * sizeof(t_eau));
            reseau->chateau->next = &new;
        }
    }
}

int check_connexion(t_case case_actu, int **matrice, int mode)
{
    for (int i = 0; i < 3; i++)
    {
        printf("Cote haut : %d %d\n" ,(case_actu.y1-20) / 20, (case_actu.x1 - 124) / 20 );
        if (matrice[(case_actu.y1-20) / 20][(case_actu.x1 - 124) / 20] == 2)
        {
            printf("TOUCHEEEE(1)");
        }
        case_actu.x1+=20;
    } 

    for (int j = 0; j < 3; j++)
    {
        printf("Cote droit : %d %d\n" ,(case_actu.y1) / 20, (case_actu.x1 - 124) / 20 );
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] == 2)
        {
            printf("TOUCHEEEEE(2)");
        }
        case_actu.y1+=20;
    } 

    for (int j = 0; j < 3; j++)
    {
         printf("Cote bas : %d %d\n" ,(case_actu.y1) / 20, (case_actu.x1 - 20 - 124) / 20 );
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] == 2)
        {
            printf("TOUCHEEEEE(3)");
        }
        case_actu.x1-=20;
    } 

    for (int j = 0; j < 3; j++)
    {
         printf("Cote gauche : %d %d\n" ,(case_actu.y1-20) / 20, (case_actu.x1 - 20 - 124) / 20 );
        if (matrice[(case_actu.y1-20) / 20][(case_actu.x1 - 20 - 124) / 20] == 2)
        {
            printf("TOUCHEEEEE(4)");
        }
        case_actu.y1-=20;
    } 
}

int creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment, int **matrice)
{

    player->argent -= 1000;

    t_bat new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1; // intialisation nouvelle case
    new.y2 = case_actu.y2;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = 1;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 60;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;

    check_connexion(case_actu, matrice, 0);

    strcpy(new.nom, batiment[0].nom);
    new.prix = batiment[0].prix,
    new.centrale = 0;
    new.chateau = 0;
    new.niveau = 0;
    new.icone = batiment[0].icone;
    new.habitant = batiment[0].habitant;
    // printf("%d", player->propriete[0].prix);
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

                player->nbpropriete += 1;

                player->propriete[i] = new;
                player->propriete[i].marqueur = timer;
                i = 32;
            }
        }
    }
}

int main()
{
    BITMAP *page;
    BITMAP *detection;
    BITMAP *accueil;
    BITMAP *map;
    int modedejeu = 0;

    t_bat *batiment;
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    reseau->centrale = (t_electricite *)malloc(1 * sizeof(t_electricite));
    reseau->chateau = (t_eau *)malloc(1 * sizeof(t_eau));
    reseau->chaussee = (t_route *)malloc(1 * sizeof(t_route));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(100 * sizeof(t_bat));
    player->bitume = (t_route *)malloc(200 * sizeof(t_route));
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
    reseau->chaussee->iconeroute = (BITMAP **)malloc(15 * sizeof(BITMAP *));
    accueil = load_bitmap("home.bmp", NULL);
    detection = create_bitmap(SCREEN_W, SCREEN_H);
    page = create_bitmap(SCREEN_W, SCREEN_H);
    map = load_bitmap("ingame.bmp", NULL);
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
            modedejeu = menu(page, detection, accueil);
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

            mode_capitaliste(page, detection, batiment, player, map, reseau);
        }
        else if (modedejeu == 2)
        {
            // COMMUNISTE
            init_structure(batiment, reseau);
            // mode_capitaliste(page, detection, batiment, player,map);
        }
        else if (modedejeu == 3)
        {
            // CHARGER UNE PARTIE
            // recuperer les donnes et les affilier.
        }
    }
    free(player->propriete);
    free(player);
    free(batiment);
    free(reseau->centrale);
    free(reseau->chateau);
    free(reseau->chaussee);
    free(reseau);
    return 0;
}
END_OF_MAIN();
