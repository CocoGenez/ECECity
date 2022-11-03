#include "allegro.h"
#include "biblio.h"
#include "stdio.h"
#include "stdlib.h"

volatile int timer;
void incrementer_timer() {
    timer++;
}
END_OF_FUNCTION(incrementer_timer)

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
}

t_case detecterCase(t_case **plateau, BITMAP *page, BITMAP *batiment, BITMAP *map, t_joueur *player) {
    clear_bitmap(page);
    t_case casecliquee;
    int xsouris = 0;
    int ysouris = 0;
    int casechoisie_x = 0;
    int casechoisie_y = 0;
    blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    draw_sprite(page, batiment, mouse_x, mouse_y);
    printf("nombre propriétés : %d \n\n", player->nbpropriete);
    for(int z=0;z<player->nbpropriete;z++)
    {
        if(player->propriete[z].prix == 1000){
            printf("z = %d ; big maison ; x1 : %d ; y1 : %d", z, player->propriete[z].x1,player->propriete[z].y1);
            draw_sprite(page,player->propriete[z].icone,player->propriete[z].x1,player->propriete[z].y1);
        }
        else if(player->propriete[z].water.prix == 100000){
            printf("z = %d ; WATERRRR", z);
            draw_sprite(page,player->propriete[z].water.iconeeau,player->propriete[z].water.x1,player->propriete[z].water.y1);
        }
    }
    /*
    for (int z = 0; z < player->nbpropriete; z++)
        draw_sprite(page, player->propriete[z].icone, player->propriete[z].x1, player->propriete[z].y1);*/
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
    // blit(pagetemp, decor, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void initcase(t_case **plateau) {
    int depx1 = 124, depx2 = 20, depy1 = 0, depy2 = 20;
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
        depx2 = 20;
        depy1 += 20;
        depy2 += 20;
    }
}

int evolution_batiment(t_joueur *player, t_bat *batiment, int *condition) {
    for (int z = 0; z < player->nbpropriete; z++) {
        // printf("%d : %d \n", z, player->propriete[z].niveau);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau + 1].habitant-batiment[player->propriete[z].niveau].habitant);
        // printf("%d : %d \n", z, batiment[player->propriete[z].niveau].habitant);
        if (timer - player->propriete[z].marqueur >= 15000 && player->propriete[z].niveau < 4 && condition[z] == 0) {
            player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
            player->propriete[z].icone = batiment[player->propriete[z].niveau + 1].icone;
            player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
            player->propriete[z].niveau += 1;
            player->propriete[z].marqueur = timer;
            condition[z] = 1;
        }
    }
}

int creation_chateau(t_joueur *player, t_case case_actu, t_bat *batiment, t_graphe *reseau) {
    player->argent -= 100000;
    t_eau new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1;  // intialisation nouvelle case
    new.y2 = case_actu.y2;
    new.prix = 100000;
    new.capacite = 5000;
    //new.next ?
    new.iconeeau = batiment->water.iconeeau;
    if (reseau->chateau->x1 == 0) 
    {
        reseau->chateau = &new;
        reseau->chateau->next = NULL;
        for (int i = 0; i < 30; i++) 
        {
            if(player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000){
                t_bat *temp;
                temp = player->propriete;
                player->nbpropriete += 1;
                player->propriete = (t_bat *)malloc(i * sizeof(t_bat));
                player->propriete = temp;
                player->propriete[i].water = new;
                i=32;
            }
        }
    } else 
    {
        while (reseau->chateau->next != NULL) 
        {
            reseau->chateau = reseau->chateau->next;
        }
        reseau->chateau->next = (t_eau *)malloc(1 * sizeof(t_eau));
        reseau->chateau->next = &new;
    }
}

int creation_batiment(t_joueur *player, t_case case_actu, t_bat *batiment) {
    player->argent -= 1000;

    t_bat new;
    new.x1 = case_actu.x1;
    new.x2 = case_actu.x2;
    new.y1 = case_actu.y1;  // intialisation nouvelle case
    new.y2 = case_actu.y2;
    strcpy(new.nom, batiment[0].nom);
    new.prix = batiment[0].prix,
    new.niveau = 0;
    new.icone = batiment[0].icone;
    new.habitant = batiment[0].habitant;
    if (player->propriete[0].prix != 1000 && player->propriete[0].prix != 100000) {
        player->propriete[0] = new;
        player->nbpropriete = 1;
        player->propriete[0].marqueur = timer;
        //printf("%d", player->propriete[0].x1);
    } else if (player->propriete[0].prix == 1000 || player->propriete[0].prix == 100000) {
        for (int i = 0; i < 30; i++) {
            if (player->propriete[i].prix != 1000 && player->propriete[i].prix != 100000) {  // condition verifiant si la propriete existe deja
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

void lancementPartieCapitaliste() {
    BITMAP *map = load_bitmap("inGame.bmp", NULL);
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *maison = load_bitmap("images_structure/habitation/maison.bmp", NULL);
    BITMAP *detection = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    printf("\nAffichage de la map.");

    if (!map) {
        allegro_message("\nErreur avec l'image de la map.");
        exit(EXIT_FAILURE);
    }

    FONT *arial_rounded = load_font("polices/arial_rounded.pcx", NULL, NULL);
    FONT *itc = load_font("polices/itc_font.pcx", NULL, NULL);
    
    // Début lignes du main
    t_bat *batiment;
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    reseau->centrale=(t_electricite*)malloc(1*sizeof(t_electricite));
    reseau->chateau=(t_eau*)malloc(1*sizeof(t_eau));
    reseau->chaussee=(t_route*)malloc(1*sizeof(t_route));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(1 * sizeof(t_bat));
    // Fin lignes deu main


    // Début lignes initialisation de la fonction mode_capitaliste
    player->nbhabitant=0;
    player->nbpropriete=0;
    
    t_case case_actu;
    t_case **plateau;
    plateau = (t_case **)calloc(35, sizeof(t_case *));
    for (int i = 0; i < 35; i++)
        plateau[i] = calloc(45, sizeof(t_case));
    initcase(plateau);
    init_structure(batiment, reseau);
    player->argent = 500000;

    timer = 0;
    int minutes = 0;
    int secondes = 0;
    int condi = 0;
    int couleurpixel;
    
    int marqueur1 = timer;
    int marqueur2 = timer;
    LOCK_FUNCTION(incrementer_timer);
    LOCK_VARIABLE(timer);
    install_int_ex(incrementer_timer, MSEC_TO_TIMER(1));
    // Fin lignes initialisation de la fonction mode_capitaliste

    rectfill(detection, 24, 202, 101, 279, makecol(254, 0, 0)); //batiment
    rectfill(detection, 24, 296, 101, 373, makecol(253, 0, 0));//chateau
    rectfill(detection, 24, 390, 101, 467, makecol(252, 0, 0));//caserne
    rectfill(detection, 24, 484, 101, 561, makecol(251, 0, 0));//centrale

    while (!key[KEY_ESC] && 1 == 1) {
        blit(map, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_right_ex(page, arial_rounded, 259, 725, makecol(30, 66, 120), -1, "%d", player->nbhabitant);
        textprintf_right_ex(page, arial_rounded, 407, 725, makecol(30, 66, 120), -1, "%d", 99111);
        textprintf_right_ex(page, arial_rounded, 555, 725, makecol(30, 66, 120), -1, "%d", 99111);
        textprintf_right_ex(page, arial_rounded, 809, 721, makecol(30, 66, 120), -1, "%d", player->argent);
        textprintf_right_ex(page, arial_rounded, 986, 721, makecol(30, 66, 120), -1, "%d : %d", minutes, secondes);

        int condition[30]={0};
        condi = 0;
        
        if (mouse_b == 2)
        {
            couleurpixel = getpixel(detection, mouse_x, mouse_y);
            if (getr(couleurpixel) == 254 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                while (condi == 0)
                {
                    case_actu.x1 = 0;
                    case_actu = detecterCase(plateau,page,batiment[0].icone,map,player);
                    if (case_actu.x1 != 0)
                        condi = 1;
                }
                creation_batiment(player,case_actu,batiment);
                
            }
            if (getr(couleurpixel) == 253 && getg(couleurpixel) == 0 && getb(couleurpixel) == 0)
            {
                while (condi == 0)
                {
                    case_actu.x1 = 0;
                    case_actu = detecterCase(plateau,page,batiment->water.iconeeau,map,player);
                    if (case_actu.x1 != 0 && case_actu.x1 < 1100){
                        condi = 1;
                    }
                }
                creation_chateau(player,case_actu,batiment,reseau);
            }

        }
        evolution_batiment(player,batiment,condition);
        if (timer - marqueur1 >= 1000)
        {
            marqueur1 = timer;
            secondes += 1;
        }
        if (timer - marqueur2 >= 60000)
        {
            //timer = 0;
            marqueur2 = timer;
            secondes = 0;
            minutes += 1;
        }
        for(int z=0;z<player->nbpropriete;z++){
            if(player->propriete[z].prix == 1000){
                draw_sprite(page,player->propriete[z].icone,player->propriete[z].x1,player->propriete[z].y1);
            }
            else if(player->propriete[z].water.prix == 100000){
                printf("WATERRRR\n\n");
                draw_sprite(page,player->propriete[z].water.iconeeau,player->propriete[z].water.x1,player->propriete[z].water.y1);
            }
        }
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear(page);
    }
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
            lancementPartieCapitaliste();
        } else if (modeDeJeu == 1) {
            lancementPartieCommuniste();
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

void lancementPartieCommuniste() {
    printf("\nPartie communiste");
}

int main() {
    t_bat *batiment;  // Mettre tout ça dans AffichageMap() ? (= lancer la partie)
    batiment = (t_bat *)malloc(5 * sizeof(t_bat));
    t_graphe *reseau;
    reseau = (t_graphe *)malloc(1 * sizeof(t_graphe));
    t_joueur *player;
    player = (t_joueur *)malloc(1 * sizeof(t_joueur));
    player->propriete = (t_bat *)malloc(1 * sizeof(t_bat));

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
