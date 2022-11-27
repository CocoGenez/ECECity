#include "allegro.h"
#include "biblio.h"
#include "stdio.h"
#include "stdlib.h"

volatile int timer;
void incrementer_timer() {
    timer++;
}
END_OF_FUNCTION(incrementer_timer)

int clicInMenu(BITMAP *detectionAccueil, int couleurPixel) {
    if (getr(couleurPixel) == 255 && getg(couleurPixel) == 0 && getb(couleurPixel) == 0) {
        printf("\nAffichage du mode de jeu.");
        return 1;

    } else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 255 && getb(couleurPixel) == 0) {
        printf("\nAffichage du chargement d'une partie.");
        return 3;

    } else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 0 && getb(couleurPixel) == 255) {
        exit(1);
    } else {
        return 0;
    }
}

void mode_capitaliste() {
    BITMAP *map = load_bitmap("inGame.bmp", NULL);
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *maison = load_bitmap("images_structure/habitation/maison.bmp", NULL);
    BITMAP *detection = create_bitmap(SCREEN_W, SCREEN_H);

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
    reseau->chaussee->iconeroute = (BITMAP **)malloc(15 * sizeof(BITMAP *));

    t_case case_actu;
    t_case **plateau;
    t_bat *centrale;
    t_bat *chateau;
    t_bat *maisons;
    int **matriceJeu;

    g = init_graphe(g, player);
    init_structure(batiment, reseau);

    matriceJeu = (int **)malloc(35 * sizeof(int *));
    for (int i = 0; i < 35; i++)
        matriceJeu[i] = (int *)malloc(45 * sizeof(int));
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
            if ((j >= 10 && j <= 15 && i == 21) || (j >= 10 && j <= 15 && i == 22) || (j >= 8 && j <= 15 && i == 23) || (j >= 8 && j <= 15 && i == 24) || (j >= 8 && j <= 14 && i == 25) || (j >= 8 && j <= 14 && i == 26) || (j >= 11 && j <= 14 && i == 27)) {
                matriceJeu[i][j] = 999;
            } else
                matriceJeu[i][j] = 0;
        }
    }
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    install_mouse();
    install_timer();

    player->argent = 500000;
    player->nbhabitant = 0;
    BITMAP *panel;
    BITMAP* canalisation;
    BITMAP* filelectric;
    canalisation=load_bitmap("canalisation.bmp",NULL);
    filelectric=load_bitmap("alim_electrique.bmp",NULL);
    panel = load_bitmap("images_structure/panel/route_panel.bmp", NULL);
    if (!panel) {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }
    timer = 0;
    int minutes = 0;
    int secondes = 0;
    int condi = 0, condi2 = 0, condi3 = 0, condi4 = 0;
    int niveau = 0;

    int electric = 0;
    int castle = 0;
    int home = 0;
    int ** distance_centrale;
    int ** distance_chateau;

    int couleurpixel;
    int capaciteElecTot = 0;
    int capaciteEauTot = 0;

    int marqueur1 = timer;
    int marqueur2 = timer;
    int trucpourrouler;
    FONT *arial_rounded = load_font("polices/arial_rounded.pcx", NULL, NULL);
    LOCK_FUNCTION(incrementer_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementer_timer, MSEC_TO_TIMER(1));

    while (!key[KEY_ESC]) {
        capaciteEauTot = 0;
        capaciteElecTot = 0;
        clear_bitmap(detection);
        clear(page);
        rectfill(detection, 24, 202, 101, 279, makecol(254, 0, 0));  // batiment
        rectfill(detection, 24, 296, 101, 373, makecol(253, 0, 0));  // chateau
        rectfill(detection, 24, 390, 101, 467, makecol(252, 0, 0));  // caserne
        rectfill(detection, 24, 484, 101, 561, makecol(251, 0, 0));  // centrale
        rectfill(detection, 24, 108, 101, 185, makecol(250, 0, 0));  // panel route

        rectfill(detection, 6, 727, 41, 762, makecol(250, 1, 0));    // 0
        rectfill(detection, 44, 727, 79, 762, makecol(250, 2, 0));   // 1
        rectfill(detection, 82, 727, 117, 762, makecol(250, 3, 0));  // 2

        for(int i=0; i<player->nbpropriete + player->nbroute; i++){
            if(player->propriete[i].chateau == 1){
                capaciteEauTot += player->propriete[i].capacite;
            }
            if(player->propriete[i].centrale == 1){
                capaciteElecTot += player->propriete[i].capacite;
            }
        }
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_right_ex(page, arial_rounded, 259, 725, makecol(30, 66, 120), -1, "%d", player->nbhabitant);
        textprintf_right_ex(page, arial_rounded, 407, 725, makecol(30, 66, 120), -1, "%d", capaciteEauTot);
        textprintf_right_ex(page, arial_rounded, 555, 725, makecol(30, 66, 120), -1, "%d", capaciteElecTot);
        textprintf_right_ex(page, arial_rounded, 809, 721, makecol(30, 66, 120), -1, "%d", player->argent);
        textprintf_right_ex(page, arial_rounded, 986, 721, makecol(30, 66, 120), -1, "%d : %d", minutes, secondes);
        //textprintf_centre_ex(page, font, 100, 500, makecol(255, 255, 255), -1, "souris : %d %d", mouse_x, mouse_y);
        int condition[100] = {0};
        condi = 0;
        condi2 = 0;
        condi3 = 0;
        condi4 = 0;

        if (mouse_b == 2) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 1 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 0;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 2 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 1;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 3 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 2;
            }
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > batiment[0].prix) {
                    while (condi == 0) {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);
                        // creation_batiment(player, case_actu, batiment,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);
                        // creation_chateau(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi2 = 1;
                    }
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);
                        // creation_centrale(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi3 = 1;
                    }
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

                        while (case_actu.x1 != 99009){
                            case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);
                            if (verifOccupation(matriceJeu, case_actu, 3) == 1) {
                                creation_route(player, case_actu, batiment, reseau, trucpourrouler, matriceJeu, g);
                            }
                        }
                    }
                } else {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
        }
        evolution_batiment(player, batiment, condition);
        if (timer - marqueur1 >= 1000) {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000) {
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        castle = 0;
        chateau = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 1 && player->propriete[i].centrale == 0) {
                chateau[castle] = player->propriete[i];
                castle += 1;
            }
        }
        electric = 0;
        centrale = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 1) {
                centrale[electric] = player->propriete[i];
                electric += 1;
            }
        }
        if (niveau == 0) {
            for (int z = 0; z < player->nbroute; z++) {
                draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
            }
            //textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        } 
        while (niveau == 1) {
            for (int z = 0; z < player->nbroute; z++) {
                //rectfill(page, player->bitume[z].x, player->bitume[z].y, player->bitume[z].x + 20, player->bitume[z].y + 20, makecol(0, 0, 255));
                if(player->bitume[z].alimenteau == 1)
                    draw_sprite(page,canalisation,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                if (player->propriete[z].chateau == 1) {
                    //draw_sprite(page, chateau[z].icone, chateau[z].x1, chateau[z].y1);
                    //textprintf_ex(page,font,chateau[z].x2-30,chateau[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",chateau[z].capacite,5000);
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);
                
                }
                if(player->propriete[z].alimEau>0){
                    
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimEau,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE]){
                niveau = 0;
            }
        } while(niveau == 2) {
            for (int z = 0; z < player->nbroute; z++) {
                //rectfill(page, player->bitume[z].x, player->bitume[z].y, player->bitume[z].x + 20, player->bitume[z].y + 20, makecol(0, 255, 255));
                if(player->bitume[z].alimente == 1)
                    draw_sprite(page,filelectric,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                if (player->propriete[z].centrale == 1) {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);
                
                
                }
                if(player->propriete[z].alimElec>0){
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimElec,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE]){
                niveau = 0;
            }
        }

        distance_chateau = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++) {
            distance_chateau[i] = (int *)malloc(sizeof(int));
        }
        distance_centrale = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++) {
             distance_centrale[i] = (int *)malloc(sizeof(int));
        }

        home = 0;
        maisons = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 0 && player->propriete[i].reel == 1) {
                maisons[home] = player->propriete[i];
                home += 1;
            }
        }

        for (int i = 0; i < home; i++) {
            for (int j = 0; j < castle; j++) {
                 
                distance_chateau[i][j] = algoDijkstra(g->matricepoids, maisons[i].id, chateau[j].id, player->nbpropriete + player->nbroute + 1, player);
                //printf("Distance chateau %d - %d : %d\n", maisons[i].id, chateau[j].id, distance_chateau[i][j]);
            }
            printf("\nAlim eau : %d et nb habitant : %d", player->propriete[maisons[i].position].alimEau, player->propriete[maisons[i].position].habitant);
            if (player->propriete[maisons[i].position].alimEau < player->propriete[maisons[i].position].habitant) {
                maisons[i] = alimentation(player, g, maisons[i], chateau, distance_chateau, i, castle);
                player->propriete[maisons[i].position].alimEau = maisons[i].alimEau;
            }
            printf("////EAU MAISON %d : alimentation = %d\n", i, maisons[i].alimEau);
        }
        for (int i = 0; i < home; i++) {
            for (int j = 0; j < electric; j++) {
                distance_centrale[i][j]=algoDijkstraElec(g->matricepoids,maisons[i].id,centrale[j].id,player->nbpropriete+player->nbroute+1, player);
                //printf("Distance chateau %d - %d : %d\n", maisons[i].id, chateau[j].id, distance_chateau[i][j]);
            }
            printf("\nAlim elec : %d et nb habitant : %d ", player->propriete[maisons[i].position].alimElec, player->propriete[maisons[i].position].habitant);
            if (player->propriete[maisons[i].position].alimElec < player->propriete[maisons[i].position].habitant) {
                maisons[i] = alimentation_centrale(player, g, maisons[i], centrale, distance_centrale, i, electric);
                player->propriete[maisons[i].position].alimElec = maisons[i].alimElec;
            }
            printf("////ELEC MAISON %d : alimentation = %d\n", i, player->propriete[maisons[i].position].alimElec);
        }
        for (int i = 0; i < castle; i++) {
            printf("capa chateau: %d\n",chateau[i].capacite);
        }
        free(chateau);
        free(centrale);
        free(maisons);
        for(int i=0; i<player->nbpropriete + player->nbroute; i++){
            //free(distance_centrale[i]);
            //free(distance_chateau[i]);
        }
        free(distance_centrale);
        free(distance_chateau);
    }
    free(player->bitume);
    free(player->propriete);
    free(player);
    free(batiment);
    free(reseau->centrale);
    free(reseau->chateau);
    free(reseau->chaussee->iconeroute);
    free(reseau->chaussee);
    free(reseau);
    free(g->pSommet);
    for(int i = 0; i < 1000; i++)
        free(g->matricepoids[i]);
    free(g->matricepoids);
    free(g);
    for (int i = 0; i < 35; i++)
        free(plateau[i]);
    free(plateau);
    for (int i = 0; i < 35; i++)
        free(matriceJeu[i]);
    free(matriceJeu);
}

int evolution_batiment_communiste(t_joueur *player, t_bat *batiment, int *condition) {
    for (int z = 0; z < player->nbpropriete + player->nbroute; z++) {
        if(player->propriete[z].alimEau == player->propriete[z].habitant && player->propriete[z].alimElec == player->propriete[z].habitant && player->propriete[z].alimElec != 0 && player->propriete[z].alimEau != 0){
            if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau < 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0) {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
                player->propriete[z].icone = batiment[player->propriete[z].niveau + 1].icone;
                player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].niveau += 1;
                player->propriete[z].marqueur = timer;
                // if(player->propriete[z].niveau > 1) a rajouter si loyer commence apres terrain vague
                player->argent = player->argent + player->propriete[z].habitant * 10;
                condition[z] = 1;
                return 1;
            }

            if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau == 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0) {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau].habitant;
                player->nbhabitant += batiment[player->propriete[z].niveau].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].marqueur = timer;
                player->argent = player->argent + player->propriete[z].habitant * 10;
                condition[z] = 1;
                return 1;
            }
        }
        else if(player->propriete[z].alimEau == player->propriete[z].habitant && player->propriete[z].alimElec == player->propriete[z].habitant && player->propriete[z].alimElec == 0 && player->propriete[z].alimEau == 0){
            player->propriete[z].habitant = 10;
        }
    }
    return 0;
}

void mode_communiste() {
    BITMAP *map = load_bitmap("inGame.bmp", NULL);
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *maison = load_bitmap("images_structure/habitation/maison.bmp", NULL);
    BITMAP *detection = create_bitmap(SCREEN_W, SCREEN_H);

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
    reseau->chaussee->iconeroute = (BITMAP **)malloc(15 * sizeof(BITMAP *));

    t_case case_actu;
    t_case **plateau;
    t_bat *centrale;
    t_bat *chateau;
    t_bat *maisons;
    int **matriceJeu;

    g = init_graphe(g, player);
    init_structure(batiment, reseau);

    matriceJeu = (int **)malloc(35 * sizeof(int *));
    for (int i = 0; i < 35; i++)
        matriceJeu[i] = (int *)malloc(45 * sizeof(int));
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
            if ((j >= 10 && j <= 15 && i == 21) || (j >= 10 && j <= 15 && i == 22) || (j >= 8 && j <= 15 && i == 23) || (j >= 8 && j <= 15 && i == 24) || (j >= 8 && j <= 14 && i == 25) || (j >= 8 && j <= 14 && i == 26) || (j >= 11 && j <= 14 && i == 27)) {
                matriceJeu[i][j] = 999;
            } else
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
    BITMAP* canalisation;
    BITMAP* filelectric;
    canalisation=load_bitmap("canalisation.bmp",NULL);
    filelectric=load_bitmap("alim_electrique.bmp",NULL);
    panel = load_bitmap("images_structure/panel/route_panel.bmp", NULL);
    if (!panel) {
        allegro_message("Erreur image Accueil");
        exit(EXIT_FAILURE);
    }
    timer = 0;
    int minutes = 0;
    int secondes = 0;
    int condi = 0, condi2 = 0, condi3 = 0, condi4 = 0;
    int niveau = 0;

    int electric = 0;
    int castle = 0;
    int home = 0;
    int ** distance_chateau;
    int ** distance_centrale;

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

        rectfill(detection, 6, 727, 41, 762, makecol(250, 1, 0));    // 0
        rectfill(detection, 44, 727, 79, 762, makecol(250, 2, 0));   // 1
        rectfill(detection, 82, 727, 117, 762, makecol(250, 3, 0));  // 2

        int couleurpixel;
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_centre_ex(page, font, 930, 726, makecol(0, 0, 0), -1, "%d :", minutes);
        textprintf_centre_ex(page, font, 960, 726, makecol(0, 0, 0), -1, "%d", secondes);
        textprintf_centre_ex(page, font, 750, 726, makecol(0, 0, 0), -1, "%d ECEflouz", player->argent);
        textprintf_centre_ex(page, font, 250, 726, makecol(0, 0, 0), -1, "%d", player->nbhabitant);
        //textprintf_centre_ex(page, font, 100, 500, makecol(255, 255, 255), -1, "souris : %d %d", mouse_x, mouse_y);
        int condition[100] = {0};
        condi = 0;
        condi2 = 0;
        condi3 = 0;
        condi4 = 0;

        if (mouse_b == 2) {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 1 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 0;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 2 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 1;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 3 && getb(couleurpixel) == 0) {  // Clique niveau 0
                niveau = 2;
            }
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0) {
                if (player->argent > batiment[0].prix) {
                    while (condi == 0) {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);
                        // creation_batiment(player, case_actu, batiment,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);
                        // creation_chateau(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi2 = 1;
                    }
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);
                        // creation_centrale(player, case_actu, batiment, reseau,matriceJeu);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi3 = 1;
                    }
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

                        while (case_actu.x1 != 99009){
                            case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);
                            if (verifOccupation(matriceJeu, case_actu, 3) == 1) {
                                creation_route(player, case_actu, batiment, reseau, trucpourrouler, matriceJeu, g);
                            }
                        }
                    }
                } else {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
        }
        evolution_batiment_communiste(player, batiment, condition);
        if (timer - marqueur1 >= 1000) {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000) {
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        castle = 0;
        chateau = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 1 && player->propriete[i].centrale == 0) {
                chateau[castle] = player->propriete[i];
                castle += 1;
            }
        }
        electric = 0;
        centrale = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 1) {
                centrale[electric] = player->propriete[i];
                electric += 1;
            }
        }
        if (niveau == 0) {
            for (int z = 0; z < player->nbroute; z++) {
                draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
            }
            //textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        } while (niveau == 1) {
            for (int z = 0; z < player->nbroute; z++) {
                //rectfill(page, player->bitume[z].x, player->bitume[z].y, player->bitume[z].x + 20, player->bitume[z].y + 20, makecol(0, 0, 255));
                if(player->bitume[z].alimenteau == 1)
                    draw_sprite(page,canalisation,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                if (player->propriete[z].chateau == 1) {
                    //draw_sprite(page, chateau[z].icone, chateau[z].x1, chateau[z].y1);
                    //textprintf_ex(page,font,chateau[z].x2-30,chateau[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",chateau[z].capacite,5000);
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);
                
                }
                if(player->propriete[z].alimEau>0){
                    
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimEau,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE]){
                niveau = 0;
            }
        } while(niveau == 2) {
            for (int z = 0; z < player->nbroute; z++) {
                //rectfill(page, player->bitume[z].x, player->bitume[z].y, player->bitume[z].x + 20, player->bitume[z].y + 20, makecol(0, 255, 255));
                if(player->bitume[z].alimente == 1)
                    draw_sprite(page,filelectric,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++) {
                if (player->propriete[z].centrale == 1) {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);
                
                
                }
                if(player->propriete[z].alimElec>0){
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimElec,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE]){
                niveau = 0;
            }
        }

        distance_chateau = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++) {
            distance_chateau[i] = (int *)malloc(sizeof(int));
        }
        distance_centrale = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++) {
             distance_centrale[i] = (int *)malloc(sizeof(int));
        }

        home = 0;
        maisons = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++) {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 0 && player->propriete[i].reel == 1) {
                maisons[home] = player->propriete[i];
                home += 1;
            }
        }
        for (int i = 0; i < home; i++) {
            for (int j = 0; j < castle; j++) {
                 
                distance_chateau[i][j] = algoDijkstra(g->matricepoids, maisons[i].id, chateau[j].id, player->nbpropriete + player->nbroute + 1, player);
                //printf("Distance chateau %d - %d : %d\n", maisons[i].id, chateau[j].id, distance_chateau[i][j]);
            }
            printf("\nAlim eau : %d et nb habitant : %d", player->propriete[maisons[i].position].alimEau, player->propriete[maisons[i].position].habitant);
            if (player->propriete[maisons[i].position].alimEau < player->propriete[maisons[i].position].habitant) {
                maisons[i] = alimentation(player, g, maisons[i], chateau, distance_chateau, i, castle);
                player->propriete[maisons[i].position].alimEau = maisons[i].alimEau;
            }
            printf("//// MAISON %d : alimentation = %d\n", i, maisons[i].alimEau);
        }
        for (int i = 0; i < home; i++) {
            for (int j = 0; j < electric; j++) {
                distance_centrale[i][j]=algoDijkstraElec(g->matricepoids,maisons[i].id,centrale[j].id,player->nbpropriete+player->nbroute+1, player);
                //printf("Distance chateau %d - %d : %d\n", maisons[i].id, chateau[j].id, distance_chateau[i][j]);
            }
            printf("\nAlim elec : %d et nb habitant : %d ", player->propriete[maisons[i].position].alimElec, player->propriete[maisons[i].position].habitant);
            if (player->propriete[maisons[i].position].alimElec < player->propriete[maisons[i].position].habitant) {
                maisons[i] = alimentation_centrale(player, g, maisons[i], centrale, distance_centrale, i, electric);
                player->propriete[maisons[i].position].alimElec = maisons[i].alimElec;
            }
            printf("////ELEC MAISON %d : alimentation = %d\n", i, player->propriete[maisons[i].position].alimElec);
        }
        for (int i = 0; i < castle; i++) {
            printf("capa chateau: %d\n",chateau[i].capacite);
            // afficher_successeurs(g->pSommet, i);
            // printf("\n");
        }
        free(chateau);
        free(centrale);
        free(maisons);
        for(int i=0; i<player->nbpropriete + player->nbroute; i++){
            //free(distance_centrale[i]);
            //free(distance_chateau[i]);
        }
        free(distance_centrale);
        free(distance_chateau);
    }
    for (int i = 0; i < 35; i++)
        free(plateau[i]);
    free(plateau);
    for (int i = 0; i < 35; i++)
        free(matriceJeu[i]);
    free(matriceJeu);
}

int algoDijkstraElec(int **matrice, int debut, int fin, int ordre, t_joueur* player) {
    int min, d, m = 0, j = 0;  // min = cout minimal, d = cout actuel, m : sommet suivant
    int cout[ordre];
    int chemin[ordre];  // tableau des sommets du chemin
    int preds[ordre];
    int marque[ordre];  // 1 si sommet explore, sinon 0
    for (int i = 0; i < ordre; i++) {
        marque[i] = 0;  // on initialise les sommets comme non-marques
    }
    for (int i = 0; i < ordre; i++) {
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
            if (i == ordre - 1 && min == 400) {
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

    for (int k=0;k<j;k++){
        for(int z=0;z<ordre;z++){
            if(player->bitume[z].id==chemin[k] ){
                player->bitume[z].alimente=1;
            }
        }

    }

    // affichage du chemin
    /*
    printf("\n");
    for (int i = j - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%d", chemin[i]);
        } else {
            printf("%d <-- ", chemin[i]);
        }
    }*/
    return cout[fin];  // on retourne le cout du chemin
}

int algoDijkstra(int **matrice, int debut, int fin, int ordre, t_joueur* player) {
    int min, d, m = 0, j = 0;  // min = cout minimal, d = cout actuel, m : sommet suivant
    int cout[ordre];
    int chemin[ordre];  // tableau des sommets du chemin
    int preds[ordre];
    int marque[ordre];  // 1 si sommet explore, sinon 0
    for (int i = 0; i < ordre; i++) {
        marque[i] = 0;  // on initialise les sommets comme non-marques
    }
    for (int i = 0; i < ordre; i++) {
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
            if (i == ordre - 1 && min == 400) {
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

    for (int k=0;k<j;k++){
        for(int z=0;z<ordre;z++){
            if(player->bitume[z].id==chemin[k] ){
                player->bitume[z].alimenteau=1;
            }
        }

    }
    return cout[fin];  // on retourne le cout du chemin
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
        if(key[KEY_SPACE]){
            casecliquee.x1 = 99009;
            return casecliquee;
        }
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
            if (xsouris <= 50 && xsouris >= 5 && ysouris <= 34 && ysouris >= 0) {
                casechoisie_x = xsouris - 6;
                casechoisie_y = ysouris;
                casecliquee = plateau[casechoisie_y][casechoisie_x];
                return casecliquee;
            }
        }
    }
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
    if(caseactu.x1 < 124){
        return 0;
    }
    if (mode == 1) {
        if(caseactu.x1 == 984 || caseactu.y1 == 660 ||caseactu.y1 == 680 || caseactu.x1 == 1004)
            return 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matrice[(caseactu.y1 / 20)][(caseactu.x1 - 124) / 20] != 0) {
                    return 0;
                }
                caseactu.x1 += 20;
            }
            caseactu.y1 += 20;
            caseactu.x1 -= 60;
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

void selectionModeDeJeu() {
    BITMAP *gamemode = load_bitmap("gamemode.bmp", NULL);
    BITMAP *communisteIMG = load_bitmap("communiste_selected.bmp", NULL);
    BITMAP *capitalisteIMG = load_bitmap("capitaliste_selected.bmp", NULL);
    BITMAP *validerHover = load_bitmap("images_menu/validerHover.bmp", NULL);
    BITMAP *retourHover = load_bitmap("images_menu/retourHover.bmp", NULL);
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *detectionGamemode = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    printf("\nAffichage du mode de jeu.");

    if (!gamemode || !communisteIMG || !capitalisteIMG || !validerHover || !retourHover) {
        allegro_message("\nErreur avec une des images du mode de jeu.");
        exit(EXIT_FAILURE);
    }

    rectfill(detectionGamemode, 345, 459, 720, 496, makecol(255, 0, 0));  // CAPITALISTE
    rectfill(detectionGamemode, 345, 505, 720, 549, makecol(0, 255, 0));  // COMMUNISTE
    rectfill(detectionGamemode, 519, 576, 701, 620, makecol(0, 1, 255));  // VALIDER
    rectfill(detectionGamemode, 319, 576, 501, 620, makecol(0, 2, 255));  // RETOUR

    int fenetre = 1;
    int modeDeJeu = 0;
    int couleurPixel;

    while (!key[KEY_ESC] && fenetre == 1) {
        if (mouse_b == 2 && fenetre == 1) {  // SI un clic est détecté dans la page du mode de jeu
            couleurPixel = getpixel(detectionGamemode, mouse_x, mouse_y);

            if (getr(couleurPixel) == 255 && getg(couleurPixel) == 0 && getb(couleurPixel) == 0) {
                printf("\nCapitaliste");
                modeDeJeu = 0;

            } else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 255 && getb(couleurPixel) == 0) {
                printf("\nCommuniste");
                modeDeJeu = 1;

            } else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 1 && getb(couleurPixel) == 255) {
                fenetre = 2;

            } else if (getr(couleurPixel) == 0 && getg(couleurPixel) == 2 && getb(couleurPixel) == 255) {
                fenetre = 0;
            }
        }

        blit(gamemode, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (modeDeJeu == 0) {
            blit(capitalisteIMG, page, 0, 0, 299, 451, SCREEN_W, SCREEN_H);
        } else if (modeDeJeu == 1) {
            blit(communisteIMG, page, 0, 0, 299, 497, SCREEN_W, SCREEN_H);
        }

        if (mouse_x >= 519 && mouse_y >= 576 && mouse_x <= 701 && mouse_y <= 620) {
            blit(validerHover, page, 0, 0, 519, 576, SCREEN_W, SCREEN_H);

        } else if (mouse_x >= 319 && mouse_y >= 576 && mouse_x <= 501 && mouse_y <= 620) {
            blit(retourHover, page, 0, 0, 319, 576, SCREEN_W, SCREEN_H);
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    if (fenetre == 0) {
        monMenu();
    } else if (fenetre == 2) {
        if (modeDeJeu == 0) {
            mode_capitaliste();
        } else if (modeDeJeu == 1) {
            mode_communiste();
        } else {
            printf("\nMode de jeu invalide.");
            exit(1);
        }
    }
}

void monMenu() {
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *detectionAccueil = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *accueil = load_bitmap("home.bmp", NULL);
    BITMAP *nouvellePartieHover = load_bitmap("images_menu/newGameHover.bmp", NULL);
    BITMAP *chargerPartieHover = load_bitmap("images_menu/loadGameHover.bmp", NULL);
    BITMAP *quitterPartieHover = load_bitmap("images_menu/leaveGameHover.bmp", NULL);
    BITMAP* regles = load_bitmap("regles.bmp", NULL);
    clear_bitmap(page);
    printf("\nAffichage du menu.");
    int fenetre = 0;

    if (!accueil || !nouvellePartieHover || !chargerPartieHover || !quitterPartieHover) {
        allegro_message("\nErreur avec une des images du menu.");
        exit(EXIT_FAILURE);
    }

    rectfill(detectionAccueil, 251, 479, 773, 545, makecol(255, 0, 0));  // NEW PARTIE
    rectfill(detectionAccueil, 251, 559, 773, 625, makecol(0, 255, 0));  // CHARGER
    rectfill(detectionAccueil, 251, 638, 773, 704, makecol(0, 0, 255));  // QUITTER

    while (!key[KEY_ESC] && fenetre == 0) {
        while(key[KEY_R]){
            blit(regles, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        if (mouse_b == 1 && fenetre == 0) {  // SI un clic est détecté dans le menu
            fenetre = clicInMenu(detectionAccueil, getpixel(detectionAccueil, mouse_x, mouse_y));
        }

        blit(accueil, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        if (mouse_x >= 251 && mouse_y >= 479 && mouse_x <= 773 && mouse_y <= 545) {
            blit(nouvellePartieHover, page, 0, 0, 251, 479, SCREEN_W, SCREEN_H);

        } else if (mouse_x >= 251 && mouse_y >= 559 && mouse_x <= 773 && mouse_y <= 625) {
            blit(chargerPartieHover, page, 0, 0, 251, 559, SCREEN_W, SCREEN_H);

        } else if (mouse_x >= 251 && mouse_y >= 638 && mouse_x <= 773 && mouse_y <= 704) {
            blit(quitterPartieHover, page, 0, 0, 251, 638, SCREEN_W, SCREEN_H);
        }

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    if (fenetre == 1) {
        selectionModeDeJeu();
    } else if (fenetre == 3) {
        printf("\nCHARGER UNE PARTIE.");
        exit(1);
    }
}

t_bat alimentation(t_joueur *player, t_graphe *g, t_bat maison, t_bat *chateau, int **distance_chateau, int i, int castle) {
    int a, j, tmp, tmp2;
    int cpt_chateau = 0;
    int tab_indices[castle]; // tableau des indices des chateaux
    for(int b=0; b<castle; b++){
        tab_indices[b] = b;
    }
    for (a = 0; a < castle; a++) {
        for (j = 0; j < castle - a; j++) {
            if (distance_chateau[i][j] > distance_chateau[i][j + 1] && distance_chateau[i][j + 1] > 0 && distance_chateau[i][j + 1] < 1000) {
                tmp = distance_chateau[i][j];
                distance_chateau[i][j] = distance_chateau[i][j + 1];
                distance_chateau[i][j + 1] = tmp;
                tmp2 = tab_indices[j];
                tab_indices[j] = tab_indices[j+1];
                tab_indices[j+1] = tmp2;
            }
        }
    }

    for (a = 0; a < castle; ++a) {
        if (distance_chateau[i][a] != 400) {
            cpt_chateau += 1;
            //printf("DISTANCE LA PLUS COURTE EST A INDICE %d\n", tab_indices[a]);
        }
    }

    for (int k = 0; k < cpt_chateau; k++) {
        if (player->propriete[chateau[tab_indices[k]].position].capacite - (maison.habitant - maison.alimEau) > 0) {
            if (maison.alimEau + player->propriete[chateau[tab_indices[k]].position].capacite <= maison.habitant) {
                maison.alimEau += player->propriete[chateau[tab_indices[k]].position].capacite;
                player->propriete[chateau[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[chateau[tab_indices[k]].position].capacite += maison.alimEau;
            } else {
                player->propriete[chateau[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[chateau[tab_indices[k]].position].capacite += maison.alimEau;
                maison.alimEau = maison.habitant;
            }
        } else {
            if (player->propriete[chateau[tab_indices[k]].position].capacite >= 0) {
                maison.alimEau += player->propriete[chateau[tab_indices[k]].position].capacite;
                player->propriete[chateau[tab_indices[k]].position].capacite = 0;
            }
        }
        printf("\nCAPACITE chateau %d = %d\n", chateau[k].id, player->propriete[chateau[k].position].capacite);
    }
    return maison;
}
t_bat alimentation_centrale(t_joueur *player, t_graphe *g, t_bat maison, t_bat *centrale, int **distance_centrale, int i, int elec) {
    int a, j, tmp, tmp2;
    int cpt_centrale = 0;
    int tab_indices[elec]; // tableau des indices des chateaux
    for(int b=0; b<elec; b++){
        tab_indices[b] = b;
    }
    for (a = 0; a < elec; a++) {
        for (j = 0; j < elec - a; j++) {
            if (distance_centrale[i][j] > distance_centrale[i][j + 1] && distance_centrale[i][j + 1] > 0 && distance_centrale[i][j + 1] < 1000) {
                tmp = distance_centrale[i][j];
                distance_centrale[i][j] = distance_centrale[i][j + 1];
                distance_centrale[i][j + 1] = tmp;
                tmp2 = tab_indices[j];
                tab_indices[j] = tab_indices[j+1];
                tab_indices[j+1] = tmp2;
            }
        }
    }

    for (a = 0; a < elec; ++a) {
        if (distance_centrale[i][a] != 400) {
            cpt_centrale += 1;
            printf("DISTANCE LA PLUS COURTE DE LA MAISON %d EST A INDICE %d : %d\n", i, tab_indices[a], distance_centrale[i][tab_indices[a]]);
        }
    }

    for (int k = 0; k < cpt_centrale; k++) {
        /*if (player->propriete[centrale[tab_indices[k]].position].capacite - (maison.habitant - maison.alimElec) >= 0) {
            if (maison.alimElec + player->propriete[centrale[tab_indices[k]].position].capacite <= maison.habitant) {
                maison.alimElec += player->propriete[centrale[tab_indices[k]].position].capacite;
                player->propriete[centrale[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[centrale[tab_indices[k]].position].capacite += maison.alimElec;
            } else {
                
            }
        } */
        if(player->propriete[centrale[tab_indices[k]].position].capacite >=maison.habitant-maison.alimElec && maison.alimElec!=maison.habitant){
            //maison.alimElec += player->propriete[centrale[tab_indices[k]].position].capacite;
            
            player->propriete[centrale[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[centrale[tab_indices[k]].position].capacite += maison.alimElec;
                maison.alimElec = maison.habitant;
            
        }
        printf("\nCAPACITE centrale %d = %d\n", centrale[k].id, player->propriete[centrale[k].position].capacite);
    }
    return maison;
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

void check_connexion_route(t_case case_actu, int **matrice, int mode, t_graphe *g) {
    int x1 = case_actu.x1;
    int y1 = case_actu.y1;
    if(case_actu.y1 != 0){
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.x1 != 1004){
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20] != 0) {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.y1 != 680){
        if (matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.x1 != 124){
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
}

void creation_route(t_joueur *player, t_case case_actu, t_route *route, t_graphe *reseau, int number, int **matrice, t_graphe *g) {
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
        for (int i = 0; i < 1500; i++) {
            if (player->bitume[i].prix != 10) {  // condition verifiant si la propriete existe deja
                player->nbroute += 1;

                player->bitume[i] = new;
                player->bitume[i].id = player->nbpropriete + player->nbroute;
                player->bitume[i].prix = 10;
                shesh = player->bitume[i].id;

                // printf("%d",player->bitume[i].id);
                i = 1502;
            }
        }
    }
    matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
    check_connexion_route(case_actu, matrice, 0, g);
}
int evolution_batiment(t_joueur *player, t_bat *batiment, int *condition) {
    for (int z = 0; z < player->nbpropriete + player->nbroute; z++) {
        if(player->propriete[z].alimEau > 0 && player->propriete[z].alimElec > 0){
            if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau < 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0) {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
                player->propriete[z].icone = batiment[player->propriete[z].niveau + 1].icone;
                player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].niveau += 1;
                player->propriete[z].marqueur = timer;
                player->argent = player->argent + player->propriete[z].habitant * 10;
                condition[z] = 1;
                return 1;
            }

            if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau == 4 && condition[z] == 0 && player->propriete[z].centrale == 0 && player->propriete[z].chateau == 0) {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau].habitant;
                player->nbhabitant += batiment[player->propriete[z].niveau].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].marqueur = timer;
                player->argent = player->argent + player->propriete[z].habitant * 10;
                condition[z] = 1;
                return 1;
            }
        }
        else if (player->propriete[z].alimEau == 0 && player->propriete[z].alimElec == 0){
            player->propriete[z].habitant = 10;
        }
    }
    return 0;
}
int check_connexion_centrale(t_case case_actu, int **matrice, int mode, t_graphe *g) {
    int x1 = case_actu.x1;
    int y1 = case_actu.y1;
    if(case_actu.y1 != 0){
        for (int i = 0; i < 4; i++) {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
                printf("TOUCHEEEE(1)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 += 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }

    printf("X1 = %d ; Y1 = %d\n", case_actu.x1, case_actu.y1);


    if(case_actu.x1 != 944){
        case_actu.x1 += 80;
        for (int j = 0; j < 6; j++) {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(2)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 += 20;
        }
        case_actu.y1 = y1;
        case_actu.x1 = x1;
    }

    printf("X1 = %d ; Y1 = %d\n", case_actu.x1, case_actu.y1);

    if(case_actu.y1 != 580){
        case_actu.y1 += 120;
        case_actu.x1 += 80;
        for (int j = 0; j < 4; j++) {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(3)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }

    printf("X1 = %d ; Y1 = %d", case_actu.x1, case_actu.y1);
    
    if(case_actu.x1 != 124){
        case_actu.y1 += 120;
        for (int j = 0; j < 6; j++) {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(4)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
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

    for (int i = 0; i < 1500; i++) {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000) {  // condition verifiant si la propriete existe deja

            player->nbpropriete += 1;

            player->propriete[i] = new;
            player->propriete[i].reel = 1;
            player->propriete[i].alimEau = -1;
            player->propriete[i].alimElec = -1;
            player->propriete[i].id = player->nbpropriete + player->nbroute;
            player->propriete[i].position = i;
            shesh = player->propriete[i].id;
            i = 1502;
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

    new.prix = 100000;
    new.chateau = 0;
    new.centrale = 1;  // precise que c'est une centrale;
    new.icone = batiment->elec.iconeelec;
    new.capacite = 5000;
    for (int i = 0; i < 1500; i++) {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000) {  // condition verifiant si la propriete existe deja
            player->nbpropriete += 1;
            
            player->propriete[i] = new;
            player->propriete[i].reel = 1;
            player->propriete[i].alimEau = -1;
            player->propriete[i].alimElec = -1;
            player->propriete[i].id = player->nbpropriete + player->nbroute;
            player->propriete[i].position = i;
            shesh = player->propriete[i].id;
            i = 1502;
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
    int x1 = case_actu.x1;
    int y1 = case_actu.y1;
    if(case_actu.y1 != 0){
        for (int i = 0; i < 3; i++) {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0) {
                printf("TOUCHEEEE(1)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 += 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }

    printf("X1 = %d ; Y1 = %d\n", case_actu.x1, case_actu.y1);


    if(case_actu.x1 != 964){
        case_actu.x1 += 60;
        for (int j = 0; j < 3; j++) {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(2)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 += 20;
        }
        case_actu.y1 = y1;
        case_actu.x1 = x1;
    }

    printf("X1 = %d ; Y1 = %d\n", case_actu.x1, case_actu.y1);

    if(case_actu.y1 != 640){
        case_actu.y1 += 60;
        case_actu.x1 += 60;
        for (int j = 0; j < 3; j++) {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(3)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }

    printf("X1 = %d ; Y1 = %d", case_actu.x1, case_actu.y1);
    
    if(case_actu.x1 != 124){
        case_actu.y1 += 60;
        for (int j = 0; j < 3; j++) {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0) {
                printf("TOUCHEEEEE(4)");
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }
}

void creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment, int **matrice, t_graphe *g) {
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
    printf("%d", player->propriete[0].prix);
    for (int i = 0; i <1500; i++) {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000) {  // condition verifiant si la propriete existe deja
            player->nbpropriete += 1;
            player->propriete[i] = new;
            player->propriete[i].reel = 1;
            player->propriete[i].alimEau = 0;
            player->propriete[i].alimElec = 0;
            player->propriete[i].position = i;
            player->propriete[i].id = player->nbpropriete + player->nbroute;
            shesh = player->propriete[i].id;
            player->propriete[i].marqueur = timer;
            i = 1502;
        }
    }
    // on met les cases de la matrice à id du batiment
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

t_graphe *init_graphe(t_graphe *g, t_joueur *player) {
    int ordre = 1000;
    g = CreerGraphe(ordre);  // créer le graphe d'ordre sommets
    g->ordre = 0;
    g->matricepoids = (int **)malloc(ordre * sizeof(int *));
    for (int i = 0; i < ordre; i++) {
        g->matricepoids[i] = (int *)malloc(ordre * sizeof(int));
        for (int j = 0; j < ordre; j++) {
            g->matricepoids[i][j] = 400;
            // printf("%d", g->matricepoids[i][j]);
        }
    }

    return g;
}
pSommet *CreerArete(pSommet *sommet, int s1, int s2, int poids, int **matricepoids) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->poids = poids;
        //printf("\n%d-%d\n", s1, s2);
        matricepoids[s1][s2] = matricepoids[s2][s1] = poids;
        //printf("Matrice poids v1 : %d ; matrice poids v2 : %d", matricepoids[s1][s2], matricepoids[s2][s1]);
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
        // Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}

int main() {
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    set_window_title("ECE City");

    show_mouse(screen);

    monMenu();

    return 0;
}
END_OF_MAIN();
