#include "biblio.h"
/**Fonction qui gere le timer ***/
volatile int timer;
void incrementer_timer()
{
    timer++;
}
END_OF_FUNCTION(incrementer_timer)

/***Fonction qui detecte la case clique sur la map ***/
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
        if(key[KEY_SPACE])
        {
            casecliquee.x1 = 99009;
            return casecliquee;
        }
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(page, batiment, mouse_x, mouse_y);
        for (int z = 0; z < player->nbroute; z++)
        {
            draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);//Permet que la route suive la souris
        }
        for (int z = 0; z < player->nbpropriete; z++)
        {
            draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);//Permet que le batiment  suive la souris
        }
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (mouse_b == 1)
        {
            xsouris = (mouse_x) / 20;//Chaque case
            ysouris = (mouse_y) / 20;
            if (xsouris <= 50 && xsouris >= 5 && ysouris <= 34 && ysouris >= 0)
            {
                casechoisie_x = xsouris - 6;
                casechoisie_y = ysouris;
                casecliquee = plateau[casechoisie_y][casechoisie_x];
                return casecliquee;
            }
        }
    }
}

/**Fonction qui vérifie que l'on puisse poser sur une case pas deja occuper return 0 pas bon **/
int verifOccupation(int **matrice, t_case caseactu, int mode)
{
    if(caseactu.x1 == 984 || caseactu.x1 == 1004 || caseactu.y1 == 660 ||caseactu.y1 == 680)
    {
        return 0;
    }
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
            caseactu.x1 -= 60;
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

/***Choix de mode capitaliste **/
void mode_capitaliste()
{
    BITMAP *map = charger_Bitmap("inGame.bmp");
    BITMAP *page = creer_Bitmap(SCREEN_W, SCREEN_H);

    BITMAP *detection = creer_Bitmap(SCREEN_W, SCREEN_H);

    t_bat *batiment;
    //Allocationdynamique
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
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            if ((j >= 10 && j <= 15 && i == 21) || (j >= 10 && j <= 15 && i == 22) || (j >= 8 && j <= 15 && i == 23) || (j >= 8 && j <= 15 && i == 24) || (j >= 8 && j <= 14 && i == 25) || (j >= 8 && j <= 14 && i == 26) || (j >= 11 && j <= 14 && i == 27))
            {
                matriceJeu[i][j] = 999;
            }
            else
                matriceJeu[i][j] = 0;
        }
    }
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    player->argent = 500000;
    player->nbhabitant = 0;
    BITMAP *panel;
    BITMAP* canalisation;
    BITMAP* filelectric;
    canalisation=charger_Bitmap("canalisation.bmp");
    filelectric=charger_Bitmap("alim_electrique.bmp");
    panel = charger_Bitmap("images_structure/PANEL_DES_ROUTES/route_panel.bmp");

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

    while (!key[KEY_ESC])
    {
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

        for(int i=0; i<player->nbpropriete + player->nbroute; i++)
        {
            if(player->propriete[i].chateau == 1)
            {
                capaciteEauTot += player->propriete[i].capacite;
            }
            if(player->propriete[i].centrale == 1)
            {
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

        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 1 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 0;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 2 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 1;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 3 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 2;
            }
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > batiment[0].prix)
                {
                    while (condi == 0)
                    {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);

                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 1) == 1)
                    {
                        creation_batiment(player, case_actu, batiment, matriceJeu, g);
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);

                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi2 = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_chateau(player, case_actu, batiment, reseau, matriceJeu, g);
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);

                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi3 = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_centrale(player, case_actu, batiment, reseau, matriceJeu, g);
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

                        while (case_actu.x1 != 99009)
                        {
                            case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);
                            if (verifOccupation(matriceJeu, case_actu, 3) == 1)
                            {
                                creation_route(player, case_actu, reseau, trucpourrouler, matriceJeu, g);
                            }
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
        if (timer - marqueur1 >= 1000)
        {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000)
        {
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        castle = 0;
        chateau = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 1 && player->propriete[i].centrale == 0)
            {
                chateau[castle] = player->propriete[i];
                castle += 1;
            }
        }
        electric = 0;
        centrale = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 1)
            {
                centrale[electric] = player->propriete[i];
                electric += 1;
            }
        }
        if (niveau == 0)
        {
            for (int z = 0; z < player->nbroute; z++)
            {
                draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
            }

            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        while (niveau == 1)
        {
            for (int z = 0; z < player->nbroute; z++)
            {

                if(player->bitume[z].alimenteau == 1)
                    draw_sprite(page,canalisation,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                if (player->propriete[z].chateau == 1)
                {

                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);

                }
                if(player->propriete[z].alimEau>0)
                {

                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimEau,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE])
            {
                niveau = 0;
            }
        }
        while(niveau == 2)
        {
            for (int z = 0; z < player->nbroute; z++)
            {

                if(player->bitume[z].alimente == 1)
                    draw_sprite(page,filelectric,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                if (player->propriete[z].centrale == 1)
                {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);


                }
                if(player->propriete[z].alimElec>0)
                {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);

                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimElec,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE])
            {
                niveau = 0;
            }
        }

        distance_chateau = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++)
        {
            distance_chateau[i] = (int *)malloc(sizeof(int));
        }
        distance_centrale = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++)
        {
            distance_centrale[i] = (int *)malloc(sizeof(int));
        }

        home = 0;
        maisons = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 0 && player->propriete[i].reel == 1)
            {
                maisons[home] = player->propriete[i];
                home += 1;
            }
        }

        for (int i = 0; i < home; i++)
        {
            for (int j = 0; j < castle; j++)
            {

                distance_chateau[i][j] = algoDijkstra(g->matricepoids, maisons[i].id, chateau[j].id, player->nbpropriete + player->nbroute + 1, player);

            }

            if (player->propriete[maisons[i].position].alimEau < player->propriete[maisons[i].position].habitant)
            {
                maisons[i] = alimentation(player, g, maisons[i], chateau, distance_chateau, i, castle);
                player->propriete[maisons[i].position].alimEau = maisons[i].alimEau;
            }

        }
        for (int i = 0; i < home; i++)
        {
            for (int j = 0; j < electric; j++)
            {
                distance_centrale[i][j]=algoDijkstraElec(g->matricepoids,maisons[i].id,centrale[j].id,player->nbpropriete+player->nbroute+1, player);

            }

            if (player->propriete[maisons[i].position].alimElec < player->propriete[maisons[i].position].habitant)
            {
                maisons[i] = alimentation_centrale(player, g, maisons[i], centrale, distance_centrale, i, electric);
                player->propriete[maisons[i].position].alimElec = maisons[i].alimElec;
            }

        }

        free(chateau);
        free(centrale);
        free(maisons);
        for(int i=0; i<player->nbpropriete + player->nbroute; i++)
        {
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
/***Meme evolution que capitaliste mais n'eolue pas si ressources pas dispo***/
int evolution_batiment_communiste(t_joueur *player, t_bat *batiment, int *condition){
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

void mode_communiste()
{
    BITMAP *map = charger_Bitmap("inGame.bmp");
    BITMAP *page = creer_Bitmap(SCREEN_W, SCREEN_H);
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
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            if ((j >= 10 && j <= 15 && i == 21) || (j >= 10 && j <= 15 && i == 22) || (j >= 8 && j <= 15 && i == 23) || (j >= 8 && j <= 15 && i == 24) || (j >= 8 && j <= 14 && i == 25) || (j >= 8 && j <= 14 && i == 26) || (j >= 11 && j <= 14 && i == 27))
            {
                matriceJeu[i][j] = 999;
            }
            else
                matriceJeu[i][j] = 0;
        }
    }
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    show_mouse(screen);

    player->argent = 500000;
    player->nbhabitant = 0;
    BITMAP *panel;
    BITMAP* canalisation;
    BITMAP* filelectric;
    canalisation=charger_Bitmap("canalisation.bmp");
    filelectric=charger_Bitmap("alim_electrique.bmp");
    panel = charger_Bitmap("images_structure/PANEL_DES_ROUTES/route_panel.bmp");
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

    while (!key[KEY_ESC])
    {
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

        int condition[100] = {0};
        condi = 0;
        condi2 = 0;
        condi3 = 0;
        condi4 = 0;

        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 1 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 0;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 2 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 1;
            }
            if (getr(couleurpixel) == 250 && getg(couleurpixel) == 3 && getb(couleurpixel) == 0)    // Clique niveau 0
            {
                niveau = 2;
            }
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                if (player->argent > batiment[0].prix)
                {
                    while (condi == 0)
                    {
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment[0].icone, map, player);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 1) == 1)
                    {
                        creation_batiment(player, case_actu, batiment, matriceJeu, g);
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->water.iconeeau, map, player);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi2 = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_chateau(player, case_actu, batiment, reseau, matriceJeu, g);
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
                        case_actu.x1 = 0;
                        case_actu = detecterCase(plateau, page, batiment->elec.iconeelec, map, player);
                        if (case_actu.x1 != 0 && case_actu.x1 != 99009)
                            condi3 = 1;
                    }
                    if (verifOccupation(matriceJeu, case_actu, 2) == 1)
                    {
                        creation_centrale(player, case_actu, batiment, reseau, matriceJeu, g);
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

                        while (case_actu.x1 != 99009)
                        {
                            case_actu = detecterCase(plateau, page, reseau->chaussee->iconeroute[trucpourrouler], map, player);
                            if (verifOccupation(matriceJeu, case_actu, 3) == 1)
                            {
                                creation_route(player, case_actu, reseau, trucpourrouler, matriceJeu, g);
                            }
                        }
                    }
                }
                else
                {
                    textprintf_centre_ex(page, font, 500, 100, makecol(255, 0, 0), -1, "MANQUE DE MOULA");
                }
            }
        }
        evolution_batiment_communiste(player, batiment, condition);
        if (timer - marqueur1 >= 1000)
        {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000)
        {
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        castle = 0;
        chateau = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 1 && player->propriete[i].centrale == 0)
            {
                chateau[castle] = player->propriete[i];
                castle += 1;
            }
        }
        electric = 0;
        centrale = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 1)
            {
                centrale[electric] = player->propriete[i];
                electric += 1;
            }
        }
        if (niveau == 0)
        {
            for (int z = 0; z < player->nbroute; z++)
            {
                draw_sprite(page, player->bitume[z].truc, player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
            }

            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        while (niveau == 1)
        {
            for (int z = 0; z < player->nbroute; z++)
            {
                if(player->bitume[z].alimenteau == 1)
                    draw_sprite(page,canalisation,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                if (player->propriete[z].chateau == 1)
                {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);

                }
                if(player->propriete[z].alimEau>0)
                {

                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimEau,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE])
            {
                niveau = 0;
            }
        }
        while(niveau == 2)
        {
            for (int z = 0; z < player->nbroute; z++)
            {
                if(player->bitume[z].alimente == 1)
                    draw_sprite(page,filelectric,player->bitume[z].x, player->bitume[z].y);
            }
            for (int z = 0; z < player->nbpropriete; z++)
            {
                if (player->propriete[z].centrale == 1)
                {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);
                    textprintf_ex(page,font,player->propriete[z].x2-30,player->propriete[z].y2+100,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].capacite,5000);


                }
                if(player->propriete[z].alimElec>0)
                {
                    draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);

                    textprintf_centre_ex(page,font,player->propriete[z].x1+10,player->propriete[z].y2+10,makecol(255, 255, 255), -1,"%d / %d",player->propriete[z].alimElec,player->propriete[z].habitant);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(key[KEY_SPACE])
            {
                niveau = 0;
            }
        }

        distance_chateau = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++)
        {
            distance_chateau[i] = (int *)malloc(sizeof(int));
        }
        distance_centrale = (int **)malloc((player->nbpropriete + player->nbroute) * sizeof(int *));
        for (int i = 0; i < (player->nbpropriete + player->nbroute); i++)
        {
            distance_centrale[i] = (int *)malloc(sizeof(int));
        }

        home = 0;
        maisons = (t_bat *)malloc((player->nbpropriete + player->nbroute) * sizeof(t_bat));
        for (int i = 0; i < player->nbpropriete + player->nbroute; i++)
        {
            if (player->propriete[i].chateau == 0 && player->propriete[i].centrale == 0 && player->propriete[i].reel == 1)
            {
                maisons[home] = player->propriete[i];
                home += 1;
            }
        }
        for (int i = 0; i < home; i++)
        {
            for (int j = 0; j < castle; j++)
            {

                distance_chateau[i][j] = algoDijkstra(g->matricepoids, maisons[i].id, chateau[j].id, player->nbpropriete + player->nbroute + 1, player);

            }

            if (player->propriete[maisons[i].position].alimEau < player->propriete[maisons[i].position].habitant)
            {
                maisons[i] = alimentation(player, g, maisons[i], chateau, distance_chateau, i, castle);
                player->propriete[maisons[i].position].alimEau = maisons[i].alimEau;
            }

        }
        for (int i = 0; i < home; i++)
        {
            for (int j = 0; j < electric; j++)
            {
                distance_centrale[i][j]=algoDijkstraElec(g->matricepoids,maisons[i].id,centrale[j].id,player->nbpropriete+player->nbroute+1, player);

            }

            if (player->propriete[maisons[i].position].alimElec < player->propriete[maisons[i].position].habitant)
            {
                maisons[i] = alimentation_centrale(player, g, maisons[i], centrale, distance_centrale, i, electric);
                player->propriete[maisons[i].position].alimElec = maisons[i].alimElec;
            }

        }

        free(chateau);
        free(centrale);
        free(maisons);
        for(int i=0; i<player->nbpropriete + player->nbroute; i++)
        {
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

/***Fonction qui gere l'alimentation en eau de chaque maison ***/
t_bat alimentation(t_joueur *player, t_graphe *g, t_bat maison, t_bat *chateau, int **distance_chateau, int i, int castle)
{
    int a, j, tmp, tmp2;
    int cpt_chateau = 0;
    int tab_indices[castle]; // tableau des indices des chateaux
    for(int b=0; b<castle; b++)
    {
        tab_indices[b] = b;
    }
    for (a = 0; a < castle; a++)
    {
        for (j = 0; j < castle - a; j++)
        {
            if (distance_chateau[i][j] > distance_chateau[i][j + 1] && distance_chateau[i][j + 1] > 0 && distance_chateau[i][j + 1] < 1000)
            {
                tmp = distance_chateau[i][j];
                distance_chateau[i][j] = distance_chateau[i][j + 1];
                distance_chateau[i][j + 1] = tmp;
                tmp2 = tab_indices[j];
                tab_indices[j] = tab_indices[j+1];
                tab_indices[j+1] = tmp2;
            }
        }
    }

    for (a = 0; a < castle; ++a)
    {
        if (distance_chateau[i][a] != 400)
        {
            cpt_chateau += 1;

        }
    }

    for (int k = 0; k < cpt_chateau; k++)
    {
        if (player->propriete[chateau[tab_indices[k]].position].capacite - (maison.habitant - maison.alimEau) > 0)
        {
            if (maison.alimEau + player->propriete[chateau[tab_indices[k]].position].capacite <= maison.habitant)
            {
                maison.alimEau += player->propriete[chateau[tab_indices[k]].position].capacite;
                player->propriete[chateau[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[chateau[tab_indices[k]].position].capacite += maison.alimEau;
            }
            else
            {
                player->propriete[chateau[tab_indices[k]].position].capacite -= maison.habitant;
                player->propriete[chateau[tab_indices[k]].position].capacite += maison.alimEau;
                maison.alimEau = maison.habitant;
            }
        }
        else
        {
            if (player->propriete[chateau[tab_indices[k]].position].capacite >= 0)
            {
                maison.alimEau += player->propriete[chateau[tab_indices[k]].position].capacite;
                player->propriete[chateau[tab_indices[k]].position].capacite = 0;
            }
        }

    }
    return maison;
}
/***Meme fonction que alim eau mais alimente soit tout ou rien le flux est perdu si il est pas utilisé***/
t_bat alimentation_centrale(t_joueur *player, t_graphe *g, t_bat maison, t_bat *centrale, int **distance_centrale, int i, int elec)
{
    int a, j, tmp, tmp2;
    int cpt_centrale = 0;
    int tab_indices[elec]; // tableau des indices des chateaux
    for(int b=0; b<elec; b++)
    {
        tab_indices[b] = b;
    }
    for (a = 0; a < elec; a++)
    {
        for (j = 0; j < elec - a; j++)
        {
            if (distance_centrale[i][j] > distance_centrale[i][j + 1] && distance_centrale[i][j + 1] > 0 && distance_centrale[i][j + 1] < 1000)
            {
                tmp = distance_centrale[i][j];
                distance_centrale[i][j] = distance_centrale[i][j + 1];
                distance_centrale[i][j + 1] = tmp;
                tmp2 = tab_indices[j];
                tab_indices[j] = tab_indices[j+1];
                tab_indices[j+1] = tmp2;
            }
        }
    }

    for (a = 0; a < elec; ++a)
    {
        if (distance_centrale[i][a] != 400)
        {
            cpt_centrale += 1;

        }
    }

    for (int k = 0; k < cpt_centrale; k++)
    {

        if(player->propriete[centrale[tab_indices[k]].position].capacite >=maison.habitant-maison.alimElec && maison.alimElec!=maison.habitant)
        {

            player->propriete[centrale[tab_indices[k]].position].capacite -= maison.habitant;
            player->propriete[centrale[tab_indices[k]].position].capacite += maison.alimElec;
            maison.alimElec = maison.habitant;

        }

    }
    return maison;
}

void check_connexion_route(t_case case_actu, int **matrice, int mode, t_graphe *g)
{

    if(case_actu.y1 != 0)
    {
        if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0)
        {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.x1 != 1004)
    {
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20] != 0)
        {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 + 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.y1 != 680)
    {
        if (matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20] != 0)
        {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 + 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
    if(case_actu.x1 != 124)
    {
        if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0)
        {
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
        }
    }
}
void creation_route(t_joueur *player, t_case case_actu, t_graphe *reseau, int number, int **matrice, t_graphe *g)
{
    int shesh;
    player->argent -= 10;
    t_route new;
    new.x = case_actu.x1;
    new.y = case_actu.y1;

    new.prix = 10;
    new.truc = reseau->chaussee->iconeroute[number];
    if (player->bitume[0].prix != 10)
    {
        player->nbroute = 1;
        player->bitume[0] = new;
        player->bitume[0].id = player->nbpropriete + player->nbroute;
        printf("%d", player->bitume[0].id);
        shesh = player->nbpropriete + player->nbroute;
    }
    else if (player->bitume[0].prix == 10)
    {
        for (int i = 0; i < 1500; i++)
        {
            if (player->bitume[i].prix != 10)    // condition verifiant si la propriete existe deja
            {
                player->nbroute += 1;

                player->bitume[i] = new;
                player->bitume[i].id = player->nbpropriete + player->nbroute;
                player->bitume[i].prix = 10;
                shesh = player->bitume[i].id;

                i = 1502;
            }
        }
    }
    matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;
    check_connexion_route(case_actu, matrice, 0, g);
}
/***Permet de faire augmnter le niveau du batiment et fait payer les impot au habitant***/
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
void creation_chateau(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g)
{
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

    for (int i = 0; i < 1500; i++)
    {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000)    // condition verifiant si la propriete existe deja
        {

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
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;

            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 80;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;
    check_connexion_centrale(case_actu, matrice, 0, g);
}
void creation_centrale(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau, int **matrice, t_graphe *g)
{
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
    for (int i = 0; i < 1500; i++)
    {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000)    // condition verifiant si la propriete existe deja
        {
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
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
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

void check_connexion(t_case case_actu, int **matrice, int mode, t_graphe *g)
{
    int x1 = case_actu.x1;
    int y1 = case_actu.y1;
    if(case_actu.y1 != 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 += 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }



    if(case_actu.x1 != 964)
    {
        case_actu.x1 += 60;
        for (int j = 0; j < 3; j++)
        {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 += 20;
        }
        case_actu.y1 = y1;
        case_actu.x1 = x1;
    }


    if(case_actu.y1 != 640)
    {
        case_actu.y1 += 60;
        case_actu.x1 += 60;
        for (int j = 0; j < 3; j++)
        {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }


    if(case_actu.x1 != 124)
    {
        case_actu.y1 += 60;
        for (int j = 0; j < 3; j++)
        {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }
}
void check_connexion_centrale(t_case case_actu, int **matrice, int mode, t_graphe *g)
{
    int x1 = case_actu.x1;
    int y1 = case_actu.y1;
    if(case_actu.y1 != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20] != 0)
            {
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 += 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }




    if(case_actu.x1 != 944)
    {
        case_actu.x1 += 80;
        for (int j = 0; j < 6; j++)
        {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20] != 0)
            {
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 += 20;
        }
        case_actu.y1 = y1;
        case_actu.x1 = x1;
    }



    if(case_actu.y1 != 580)
    {
        case_actu.y1 += 120;
        case_actu.x1 += 80;
        for (int j = 0; j < 4; j++)
        {
            if (matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.x1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }



    if(case_actu.x1 != 124)
    {
        case_actu.y1 += 120;
        for (int j = 0; j < 6; j++)
        {
            if (matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20] != 0)
            {

                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], 1, g->matricepoids);
                g->pSommet = CreerArete(g->pSommet, matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 20 - 124) / 20], matrice[(case_actu.y1 - 20) / 20][(case_actu.x1 - 124) / 20], 1, g->matricepoids);
            }
            case_actu.y1 -= 20;
        }
        case_actu.x1 = x1;
        case_actu.y1 = y1;
    }
}


void creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment, int **matrice, t_graphe *g)
{
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
    for (int i = 0; i <1500; i++)
    {
        if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000)    // condition verifiant si la propriete existe deja
        {
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
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrice[(case_actu.y1 / 20)][(case_actu.x1 - 124) / 20] = shesh;

            case_actu.x1 += 20;
        }
        case_actu.y1 += 20;
        case_actu.x1 -= 60;
    }
    case_actu.y1 = new.y1;
    case_actu.x1 = new.x1;

    check_connexion(case_actu, matrice, 0, g);
}


int main()
{
    initialisation_allegro();
    show_mouse(screen);

    monMenu();

    return 0;
}
END_OF_MAIN();

