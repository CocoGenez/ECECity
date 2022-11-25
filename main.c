#include "allegro.h"
#include "biblio.h"
#include "stdio.h"
#include "stdlib.h"

volatile int timer;
void incrementer_timer() {
    timer++;
}
END_OF_FUNCTION(incrementer_timer)

int menu(BITMAP *page, BITMAP *detection, BITMAP *accueil) {
    install_mouse();
    show_mouse(screen);
    clear_bitmap(detection);
    clear_bitmap(page);
    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0));  // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0));  // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255));  // QUITTER

    int modedejeu = 0;
    int couleurpixel;
    while (!key[KEY_ESC]) {
        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b == 1) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                modedejeu = nouvellepartie(page, detection, accueil);
                return modedejeu;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 255 && getb(couleurpixel) == 0) {
                return modedejeu = 3;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 255) {
                exit(1);
            }
        }
    }
}

int nouvellepartie(BITMAP *page, BITMAP *detection, BITMAP *accueil) {
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

    rectfill(detection, 345, 459, 720, 496, makecol(255, 0, 0));  // CAPITALISTE
    rectfill(detection, 345, 505, 720, 549, makecol(0, 255, 0));  // COMMUNISTE
    rectfill(detection, 519, 576, 701, 620, makecol(254, 245, 0));
    rectfill(detection, 319, 576, 501, 620, makecol(0, 0, 254));
    int modedejeu;
    int couleurpixel;
    int matthieu = 0;
    while (!key[KEY_ESC]) {
        // blit(detection,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_b == 2) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 255 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                clear_bitmap(page);
                blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                blit(capita, page, 0, 0, 299, 451, SCREEN_W, SCREEN_H);
                modedejeu = 1;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 255 && getb(couleurpixel) == 0) {
                clear_bitmap(page);
                blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                blit(commu, page, 0, 0, 299, 497, SCREEN_W, SCREEN_H);
                modedejeu = 2;
            }

            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 245 && getb(couleurpixel) == 0) {
                return modedejeu;
            }

            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 254) {
                menu(page, detection, accueil);
            }
        }
    }
}

void init_structure(t_bat *batiment, t_graphe *reseau) {
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

t_case detecterCase(t_case **plateau, BITMAP *page, BITMAP *batiment, BITMAP *map, t_joueur *player) {
    clear_bitmap(page);
    t_case casecliquee;
    int xsouris = 0;
    int ysouris = 0;
    int casechoisie_x = 0;
    int casechoisie_y = 0;
    while (casechoisie_x == 0) {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(page, batiment, mouse_x, mouse_y);
        for (int z = 0; z < player->nbroute; z++) {
            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        for (int z = 0; z < player->nbpropriete; z++) {
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        }
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b == 1) {
            xsouris = (mouse_x) / 20;
            ysouris = (mouse_y) / 20;
            if (xsouris <= 50 && xsouris >= 6 && ysouris <= 34 && ysouris >= 0) {
                casechoisie_x = xsouris - 6;
                casechoisie_y = ysouris;
                casecliquee = plateau[casechoisie_y][casechoisie_x];
                return casecliquee;
            }
        }
    }
    // blit(pagetemp, decor, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void initcase(t_case **plateau) {
    int depx1 = 124, depx2 = 144, depy1 = 0, depy2 = 20;
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
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

int verifOccupation(int **matrice, t_case caseactu, int mode) {
    if (mode == 1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0) {
                    return 0;
                }
                caseactu.x1 += 20;
            }
            caseactu.y1 += 20;
            caseactu.x1 -= 80;
        }
    } else if (mode == 2) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0) {
                    return 0;
                }
                caseactu.x1 += 20;
            }
            caseactu.y1 += 20;
            caseactu.x1 -= 80;
        }
    } else if (mode == 3) {
        if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0) {
            return 0;
        }
    }
    return 1;
}

void mode_capitaliste(BITMAP *page, BITMAP *detection, t_bat *batiment, t_joueur *player, BITMAP *map, t_graphe *reseau, t_graphe *g) {
    player->nbhabitant = 0;

    t_case case_actu;
    t_case **plateau;
    int **matriceJeu;
    int *prev;
    prev = (int *)malloc(200 * sizeof(int));
    matriceJeu = (int **)malloc(35 * sizeof(int *));
    for (int i = 0; i < 35; i++)
        matriceJeu[i] = (int *)malloc(45 * sizeof(int));
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
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
    if (!panel) {
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

    while (!key[KEY_ESC]) {
        clear_bitmap(detection);
        clear(page);
        rectfill(detection, 24, 202, 101, 279, makecol(254, 0, 0));  // batiment
        rectfill(detection, 24, 296, 101, 373, makecol(253, 0, 0));  // chateau
        rectfill(detection, 24, 390, 101, 467, makecol(252, 0, 0));  // caserne
        rectfill(detection, 24, 484, 101, 561, makecol(251, 0, 0));  // centrale
        rectfill(detection, 24, 108, 101, 185, makecol(250, 0, 0));  // panel route

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

        if (mouse_b == 2) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > batiment[0].prix) {
                    while (condi == 0) {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);
                        // creation_batiment(player, case_actu, batiment,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 1) == 1) {
                        creation_batiment(player, case_actu, batiment, matriceJeu, g);
                    }
                } else {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 253 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > reseau->chateau->prix) {
                    while (condi2 == 0) {
                        printf("/%d", condi2);
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);
                        // creation_chateau(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi2 = 1;
                    }
                    printf("/%d", condi2);
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1) {
                        creation_chateau(player, case_actu, batiment, reseau, matriceJeu, g);
                    }
                } else {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 251 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > reseau->centrale->prix) {
                    while (condi3 == 0) {
                        printf("/%d", condi3);
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);
                        // creation_centrale(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0)
                            condi3 = 1;
                    }
                    printf("/%d", condi3);
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1) {
                        creation_centrale(player, case_actu, batiment, reseau, matriceJeu, g);
                    }
                } else {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > reseau->chaussee->prix) {
                    while (condi4 == 0) {
                        trucpourrouler = choix_panel(player, case_actu, batiment, reseau, map, page, panel, detection);
                        if (trucpourrouler == 25)
                            break;
                        case_actu.x1 = 0;

                        case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);

                        if (verifOccupation(matriceJeu, case_actu, 3) == 1) {
                            creation_route(player, case_actu, batiment, reseau, trucpourrouler, matriceJeu, g);
                        }
                    }
                } else {
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
        if (timer - marqueur1 >= 1000) {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000) {
            // timer = 0;
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        for (int z = 0; z < player->nbroute; z++) {
            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        for (int z = 0; z < player->nbpropriete; z++)
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        int **distance_chateau;
        distance_chateau = (int **)malloc(player->nbpropriete + player->nbroute * sizeof(int *));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            distance_chateau[i] = (int *)malloc(sizeof(int));
        }
        t_bat *maisons;
        int home = 0;
        maisons = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 0 && player->propriete[i].reel == 1) {
                maisons[home] = player->propriete[i];
                home += 1;
            }
        }

        t_bat *chateau;
        int castle = 0;
        chateau = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 1 && player->propriete[i].centrale == 0) {
                chateau[castle] = player->propriete[i];
                castle += 1;
            }
        }

        t_bat *centrale;
        int electric = 0;
        centrale = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 1) {
                centrale[electric] = player->propriete[i];
                electric += 1;
            }
        }
        printf("\nNb chateau : %d / Nb centrale : %d / Nb maison : %d", castle, electric, home);
        for (int i = 0; i < home; i++) {
            for (int j = 0; j < castle; j++) {
                printf("IDDD:%d",maisons[i].id);
                distance_chateau[i][j] = alimentation(player, g, maisons[i].id, chateau[j].id);
                
                printf("Distance chateau i j : %d\n", distance_chateau[i][j]);
                // distance_chateau[i][j] = algoDijkstra(g->ordre, maisons[i].id, chateau[j].id);
            }
        }

        for (int i = 1; i < player->nbpropriete + player->nbroute; i++) {
            // afficher_successeurs(g->pSommet, i);
            // printf("\n");
        }
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
               // printf("%d\t",g->matricepoids[i][j]);
            }
            //printf("\n");
        }
    }
    /*for (int i = 0; i < 35; i++)
        free(plateau[i]);
    free(plateau);*/
}

int algoDijkstra(int source, int target, int ordre) {
    int m, min, debut, d, j;
    int dist[ordre], prev[ordre];
    int chemin[ordre];
    int choisi[ordre];
    for (int i = 0; i < ordre; i++) {
        choisi[i] = 0;
    }
    for (int i = 0; i < ordre; i++) {
        dist[i] = 99;
        prev[i] = -1;
    }
    debut = source;
    choisi[debut] = 1;
    dist[debut] = 0;
    while (choisi[target] == 0) {
        min = 99;
        m = 0;
        for (int i = 0; i < ordre; i++) {
            d = dist[debut] + 1;
            if (d < dist[i] && choisi[i] == 0) {
                dist[i] = d;
                prev[i] = debut;
            }
            if (min > dist[i] && choisi[i] == 0) {
                min = dist[i];
                m = i;
            }
        }
        debut = m;
        choisi[debut] = 1;
    }
    debut = target;
    j = 0;
    while (debut != -1) {
        chemin[j] = debut;
        debut = prev[debut];
        j += 1;
    }

    printf("\n");
    for (int i = j - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%d", chemin[i]);
        } else {
            printf("%d <-- ", chemin[i]);
        }
    }
    return dist[target];
}

int alimentation(t_joueur *player, t_graphe *g, int debut, int fin) {
    int taille = player->nbroute + player->nbpropriete;
    int *select = (int)malloc(taille * sizeof(int));
    for (int k = 0; k < taille; k++) {
        select[k] = 0;
    }
    
    int distance[taille], prev[taille], i, m, minimum, start, d, j = 0;
    int chemin[taille];  /// initialisation des différentes variables
    for (i = 0; i < taille; i++) {
        distance[i] = 99;  // Simulation de l infini
        prev[i] = -1;
    }
    start = debut;
    select[start] = 1;
    distance[start] = 0;
    printf("START: %d[[[",start);
    while (select[fin] == 0) {
         // Tant que le sommet de fin n'est pas marqué on effectue la boucle
        minimum = 1000;
        m = 0;
        for (i = 1; i < taille; i++) {
            //printf("MATRICE:%d/%d :%d",start,fin,g->matricepoids[start][fin]);
            if(start!=i ){
            d = distance[start] + g->matricepoids[start][i];
            printf("\nSTART: %d \t I: %d \t g->matricepoids: %d\n",start,i,g->matricepoids[start][i]);
            //printf("\nDISTANCE: I : %d\n d: %d",distance[i],d);    /// on additionne les poids de chaque arrete au fur et a mesure du parcours
            if (d < distance[i] && select[i] == 0 && d != 0) {  /// Si le poids est inferieur au poids de ref(99) on associe les grandeurs
                distance[i] = d;
                prev[i] = start;
                
            }
            

            if (minimum > distance[i] && select[i] == 0 && d != 0) {  /// si le minimum est superieur alors on prend ce chemin et on redefinit le minimum
                minimum = distance[i];
                m = i;  /// On choisit alors ce chemin puis on l'assigne cid essous à start pour marquer le bon sommet.
            }
        }
        
        
        
        start = m;
        select[start] = 1;
        
        
        
        }

    }

    while (start != -1) {
        chemin[j] = start;
       
        start = prev[start];  /// Tant que on est pas arrive au sommet original on continue de remplir le tableau.
        j++;
    }

    printf("\n\nLe chemin le plus court pour aller du sommet %d au sommet %d est : \n", debut, fin);
    for (i = j - 1; i >= 0; i--) {
        printf("%d", chemin[i]);  /// affichage du chemin
        if (i != 0) {
            printf("<--");
        }
    }
    printf("\n");
    free(select);
    return distance[fin];
}

void afficher_successeurs(pSommet *sommet, int num) {
    printf(" sommet %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("%d ", arc->sommet);
        arc = arc->arc_suivant;
    }
}
int choix_panel(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, BITMAP *map, BITMAP *page, BITMAP *panel, BITMAP *detection) {
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
    while (choix == 0) {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        for (z = 0; z < player->nbpropriete; z++) {
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
        }

        for (z = 0; z < player->nbroute; z++) {
            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
        }
        blit(panel, page, 0, 0, 124, 100, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (key[KEY_SPACE])
            return 25;
        if (mouse_b == 2) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 255) {
                return 0;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 254) {
                return 1;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 253) {
                return 2;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 252) {
                return 3;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 251) {
                return 4;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 250) {
                return 5;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 249) {
                return 6;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 248) {
                return 7;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 247) {
                return 8;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 246) {
                return 9;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 245) {
                return 10;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 244) {
                return 11;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 243) {
                return 12;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 242) {
                return 13;
            }
            if (getr(couleurpixel) == 0 && getg(couleurpixel) == 0 && getb(couleurpixel) == 241) {
                return 14;
            }
        }
    }
}
int check_connexion_route(t_case case_actu, int **matrice, int mode, t_graphe *g) {
    for (int i = 0; i < 1; i++) {
        printf("Cote haut : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEE(1)");
            printf("%d", matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20]);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 += 20;
    }

    for (int j = 0; j < 1; j++) {
        printf("Cote droit : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(2)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 += 20;
    }

    for (int j = 0; j < 1; j++) {
        printf("Cote bas : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(3)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 -= 20;
    }

    for (int j = 0; j < 1; j++) {
        printf("Cote gauche : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(4)");
            printf("%d", matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20]);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 -= 20;
    }
}
int creation_route(t_joueur *player, t_case case_actu, t_route *route, t_graphe *reseau, int number, int **matrice, t_graphe *g) {
    int shesh;
    player->argent -= 10;
    t_route new;
    new.x = case_actu.x1;
    new.y = case_actu.y1;

    new.prix = 10;
    new.truc = reseau->chaussee->iconeroute[number];
    if (player->bitume[0].prix != 10) {
        player->nbroute = 1;
        player->bitume[0] = new;
        player->bitume[0].id = player->nbpropriete + player->nbroute;
        printf("%d", player->bitume[0].id);
        shesh = player->nbpropriete + player->nbroute;
    } else if (player->bitume[0].prix == 10) {
        for (int i = 0; i < 200; i++) {
            if (player->bitume[i].prix != 10) {  // condition verifiant si la propriete existe deja
                player->nbroute += 1;

                player->bitume[i] = new;
                player->bitume[i].id = player->nbpropriete + player->nbroute;
                player->bitume[i].prix = 10;
                shesh = player->bitume[i].id;

                // printf("%d",player->bitume[i].id);
                i = 202;
            }
        }
    }
    matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
    check_connexion_route(case_actu, matrice, 0, g);
}
int evolution_batiment(t_joueur *player, t_bat *batiment, int *condition) {
    for (int z = 0; z < player->nbpropriete; z++) {
        // printf("%d : %d \n", z, player->propriete[z].niveau);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau + 1].habitant-batiment[player->propriete[z].niveau].habitant);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau].habitant);
        if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau < 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0) {
            player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
            player->propriete[z].icone = batiment[player->propriete[z].niveau + 1].icone;
            player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
            player->propriete[z].niveau += 1;
            player->propriete[z].marqueur = timer;
            condition[z] = 1;
        }
    }
}
int check_connexion_centrale(t_case case_actu, int **matrice, int mode, t_graphe *g) {
    for (int i = 0; i < 4; i++) {
        printf("Cote haut : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEE(1)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 += 20;
    }

    for (int j = 0; j < 6; j++) {
        printf("Cote droit : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(2)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 += 20;
    }

    for (int j = 0; j < 4; j++) {
        printf("Cote bas : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(3)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 -= 20;
    }

    for (int j = 0; j < 6; j++) {
        printf("Cote gauche : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(4)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 -= 20;
    }
}

int creation_chateau(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g) {
    player->argent -= 100000;
    t_bat new;
    int shesh;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1;  // intialisation nouvelle case
    new.y2 = case_actu.y2;

    new.prix = 1000;
    new.chateau = 1;
    new.centrale = 0;  // precise que c un chateau;
    new.icone = batiment->water.iconeeau;
    new.capacite = 5000;
    if (player->propriete[0].prix != 1000) {
        player->propriete[0] = new;
        player->nbpropriete = 1;
        player->propriete[0].id = player->nbpropriete + player->nbroute;
        player->propriete[0].reel = 1;
        new.id = player->nbpropriete + player->nbroute;
        player->propriete[0].marqueur = timer;
        printf("%d", player->propriete[0].x1);
    } else if (player->propriete[0].prix == 1000) {
        for (int i = 0; i < 30; i++) {
            if (player->propriete[i].prix != 1000) {  // condition verifiant si la propriete existe deja

                player->nbpropriete += 1;

                player->propriete[i].reel = 1;
                player->propriete[i] = new;
                player->propriete[i].id = player->nbpropriete + player->nbroute;
                shesh = player->propriete[i].id;
                i = 32;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 80;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;
    check_connexion_centrale(case_actu, matrice, 0, g);
}
int creation_centrale(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g) {
    player->argent -= 100000;
    t_bat new;
    int shesh;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1;  // intialisation nouvelle case
    new.y2 = case_actu.y2;

    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;

    new.prix = 1000;
    new.chateau = 0;
    new.centrale = 1;  // precise que c un chateau;
    new.icone = batiment->elec.iconeelec;
    new.capacite = 5000;
    if (player->propriete[0].prix != 1000) {
        player->propriete[0] = new;
        player->nbpropriete = 1;
        player->propriete[0].id = player->nbpropriete + player->nbroute;
        player->propriete[0].reel = 1;
        new.id = player->nbpropriete + player->nbroute;
        player->propriete[0].marqueur = timer;
        printf("%d", player->propriete[0].x1);
    } else if (player->propriete[0].prix == 1000) {
        for (int i = 0; i < 30; i++) {
            if (player->propriete[i].prix != 1000) {  // condition verifiant si la propriete existe deja
                player->nbpropriete += 1;

                player->propriete[i].reel = 1;
                player->propriete[i] = new;
                player->propriete[i].id = player->nbpropriete + player->nbroute;
                shesh = player->propriete[i].id;
                i = 32;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 80;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;
    check_connexion_centrale(case_actu, matrice, 0, g);
}

int check_connexion(t_case case_actu, int **matrice, int mode, t_graphe *g) {
    for (int i = 0; i < 3; i++) {
        printf("Cote haut : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEE(1)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 += 20;
    }

    for (int j = 0; j < 3; j++) {
        printf("Cote droit : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(2)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 += 20;
    }

    for (int j = 0; j < 3; j++) {
        printf("Cote bas : %d %d\n", (case_actu.y1) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(3)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.x1 -= 20;
    }

    for (int j = 0; j < 3; j++) {
        printf("Cote gauche : %d %d\n", (case_actu.y1 - 20) / 20, (case_actu.x1 - 20 - 124) / 20);
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            printf("TOUCHEEEEE(4)");
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
        case_actu.y1 -= 20;
    }
}

int creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment, int **matrice, t_graphe *g) {
    player->argent -= 1000;
    int shesh;
    t_bat new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1;  // intialisation nouvelle case
    new.y2 = case_actu.y2;

    strcpy(new.nom, batiment[0].nom);
    new.prix = batiment[0].prix,
    new.centrale = 0;
    new.chateau = 0;
    new.niveau = 0;
    new.icone = batiment[0].icone;
    new.habitant = batiment[0].habitant;
    // printf("%d", player->propriete[0].prix);
    if (player->propriete[0].prix != 1000) {
        player->propriete[0] = new;
        player->nbpropriete = 1;
        player->propriete[0].id = player->nbpropriete + player->nbroute;
        player->propriete[0].reel = 1;
        shesh = player->nbpropriete + player->nbroute;
        player->propriete[0].marqueur = timer;
        printf("[[%d", player->propriete[0].id);
    } else if (player->propriete[0].prix == 1000) {
        for (int i = 0; i < 30; i++) {
            if (player->propriete[i].prix != 1000) {  // condition verifiant si la propriete existe deja

                player->nbpropriete += 1;

                player->propriete[i].reel = 1;
                player->propriete[i] = new;
                player->propriete[i].id = player->nbpropriete + player->nbroute;
                shesh = player->propriete[i].id;
                player->propriete[i].marqueur = timer;
                i = 32;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
            printf("MATRICE %d - %d = %d\n", case_actu.y1 / 20, (case_actu.x1 - 124) / 20, matrice[case_actu.y1 / 20][(case_actu.x1 - 124) / 20]);
            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 60;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;

    check_connexion(case_actu, matrice, 0, g);
}
int *bfs(t_graphe *g, int s0, t_joueur *player) {
    for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        g->pSommet[i]->couleur = 0;  // on demarque tous les sommets
    int *prev = (int *)malloc(200 * sizeof(int));
    for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        prev[i] = -1;
    FileM f;
    f.tete = f.fin = NULL;
    enfiler(&f, s0);
    g->pSommet[s0]->couleur = 1;

    while (f.tete != NULL) {
        int num = defiler(&f);
        struct Arc *temp = g->pSommet[num]->arc;
        while (temp != NULL) {
            // on récupère le numéro du sommet relié par l'arc
            int num2 = temp->sommet;
            // si ce sommet n'est pas marqué
            if (g->pSommet[num2]->couleur == 0) {
                enfiler(&f, num2);
                g->pSommet[num2]->couleur = 1;
                prev[num2] = num;
            }
            temp = temp->arc_suivant;
        }
    }
    return prev;
}

void affichage_bfs_chateau(t_graphe *g, int *prev, t_joueur *player) {
    int temp;
    int i;
    for (i = 0; i < player->nbpropriete + player->nbroute; i++) {
        if (prev[i] != -1 && player->propriete[i].chateau == 1)  // c'est un chateau
        {
            printf("\n%d", i);  /// Affiche les sommets enregistrés dans le tableau tant que les cases ne sont pas "vides"
            temp = prev[i];
            while (temp != -1) {
                printf("<-%d", temp);
                temp = prev[temp];
            }
        }
    }
}

void enfiler(FileM *file, int nouv) {
    Maillon *next = malloc(sizeof(*next));
    if (file == NULL || next == NULL) {
        exit(EXIT_FAILURE);
    }

    next->num = nouv;
    next->suiv = NULL;

    if (file->tete != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Maillon *actu = file->tete;
        while (actu->suiv != NULL) {
            actu = actu->suiv;
        }
        actu->suiv = next;
    } else /* La file est vide, notre élément est le tete */
    {
        file->tete = next;
    }
}

int defiler(FileM *file) {
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    int cptFile = 0;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->tete != NULL) {
        Maillon *element = file->tete;

        cptFile = element->num;
        file->tete = element->suiv;
        free(element);
    }

    return cptFile;
}

t_graphe *init_graphe(t_graphe *g, t_joueur *player) {
    int ordre = 1000;
    g = CreerGraphe(ordre);  // créer le graphe d'ordre sommets
    g->ordre = player->nbpropriete + player->nbroute;
    g->matricepoids = (int **)malloc(45 * sizeof(int *));
    for (int i = 0; i < 45; i++) {
        g->matricepoids[i] = (int *)malloc(45 * sizeof(int));
        for (int j = 0; j < 45; j++) {
            g->matricepoids[i][j] = 0;
            //printf("%d", g->matricepoids[i][j]);
        }
    }

    return g;
}
pSommet *CreerArete(pSommet *sommet, int s1, int s2, int poids, int **matricepoids) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = poids;
        printf("\n%d-%d\n", s1, s2);
        matricepoids[s1][s2] = matricepoids[s2][s1] = poids;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    }

    else {
        pArc temp = sommet[s1]->arc;
        while (!(temp->arc_suivant == NULL)) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = poids;
        matricepoids[s1][s2] = matricepoids[s2][s1] = poids;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2) {
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
t_graphe *CreerGraphe(int ordre) {
    t_graphe *Newgraphe = (t_graphe *)malloc(sizeof(t_graphe));
    Newgraphe->pSommet = (pSommet *)malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}
int main() {
    BITMAP *page;
    BITMAP *detection;
    BITMAP *accueil;
    BITMAP *map;
    int modedejeu = 0;

    t_bat *batiment;
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    t_graphe *g;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    reseau->centrale = (t_electricite *)malloc(1 * sizeof(t_electricite));
    reseau->chateau = (t_eau *)malloc(1 * sizeof(t_eau));
    reseau->chaussee = (t_route *)malloc(1 * sizeof(t_route));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(100 * sizeof(t_bat));
    player->bitume = (t_route *)malloc(200 * sizeof(t_route));
    player->nbpropriete = 0;
    player->nbroute = 0;
    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(screen);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0) != 0) {
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

    rectfill(detection, 251, 479, 773, 545, makecol(255, 0, 0));  // NEW PARTIE
    rectfill(detection, 251, 559, 773, 625, makecol(0, 255, 0));  // CHARGER
    rectfill(detection, 251, 638, 773, 704, makecol(0, 0, 255));  // QUITTER

    if (!accueil) {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ESC]) {
        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        show_mouse(screen);
        while (modedejeu == 0) {
            modedejeu = menu(page, detection, accueil);
        }

        clear_bitmap(detection);
        clear_bitmap(page);
        // placer l'image, la detection et initialiser taille des batiments l et L pareil pour centrale et chateau
        // pour relier des batiments entre eux il faut chopper les intervalles de coordonnes pour trouver le chemin le plus proche
        // pour les centrales et chateaux, on prend leur centre donc x2-x1/2 et y2-y1/2

        if (modedejeu == 1) {
            // CAPITALISTE
            g = init_graphe(g, player);
            init_structure(batiment, reseau);

            mode_capitaliste(page, detection, batiment, player, map, reseau, g);
        } else if (modedejeu == 2) {
            // COMMUNISTE
            init_structure(batiment, reseau);
            // mode_capitaliste(page, detection, batiment, player,map);
        } else if (modedejeu == 3) {
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
