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

int menu(BITMAP *page, BITMAP *detection,BITMAP* accueil)
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
}

int nouvellepartie(BITMAP *page, BITMAP *detection,BITMAP* accueil)
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
    batiment[0].icone=load_bitmap("images_structure/habitation/terrain_vague.bmp",NULL);

    batiment[1].x1 = 0;
    batiment[1].x2 = batiment[1].x1 + 60;
    batiment[1].y2 = batiment[1].y1 + 60;
    fscanf(f, "%d", &batiment[1].habitant);
    strcpy(batiment[1].nom, "cabane");
     batiment[1].icone=load_bitmap("images_structure/habitation/cabane.bmp",NULL);

    batiment[2].x1 = 0;
    batiment[2].x2 = batiment[2].x1 + 60;
    batiment[0].y2 = batiment[2].y1 + 60;
    fscanf(f, "%d", &batiment[2].habitant);
    strcpy(batiment[2].nom, "maison");
     batiment[2].icone=load_bitmap("images_structure/habitation/maison.bmp",NULL);

    batiment[3].x1 = 0;
    batiment[3].x2 = batiment[3].x1 + 60;
    batiment[3].y2 = batiment[3].y1 + 60;
    fscanf(f, "%d", &batiment[3].habitant);
    strcpy(batiment[3].nom, "immeuble");
     batiment[3].icone=load_bitmap("images_structure/habitation/immeuble.bmp",NULL);

    batiment[4].x1 = 0;
    batiment[4].x2 = batiment[4].x1 + 60;
    batiment[4].y2 = batiment[4].y1 + 60;
    fscanf(f, "%d", &batiment[4].habitant);
    strcpy(batiment[4].nom, "gratte_ciel");
    batiment[4].icone=load_bitmap("images_structure/habitation/gratte_ciel.bmp",NULL);

    reseau->centrale->x2 = reseau->centrale->x1 + 80;
    reseau->centrale->y2 = reseau->centrale->y1 + 120;
    reseau->centrale->capacite = 5000;
    reseau->centrale->prix = 100000;
    batiment->elec.iconeelec= load_bitmap("images_structure/centrale_electrique.bmp",NULL);
    
    reseau->chateau->x1=0;
    reseau->chateau->x2 = reseau->chateau->x1 + 80;
    reseau->chateau->y2 = reseau->chateau->y1 + 120;
    reseau->chateau->capacite = 5000;
    reseau->chateau->prix = 100000;
    batiment->water.iconeeau=load_bitmap("images_structure/chateau_eau.bmp",NULL);


    reseau->chaussee->prix=10;
    

}

t_case detecterCase(t_case **plateau,BITMAP* page,BITMAP* batiment,BITMAP* map,t_joueur* player)
{
    clear_bitmap(page);
    t_case casecliquee;
    int xsouris = 0;
    int ysouris = 0;
    int casechoisie_x = 0;
    int casechoisie_y = 0;
    blit(map,page,0,0,0,0,SCREEN_W,SCREEN_H);
    draw_sprite(page,batiment,mouse_x,mouse_y);
    for(int z=0;z<player->nbpropriete;z++)
            draw_sprite(page,player->propriete[z].icone,player->propriete[z].x1,player->propriete[z].y1);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
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

void mode_capitaliste(BITMAP *page, BITMAP *detection, t_bat *batiment, t_joueur *player,BITMAP* map,t_graphe* reseau)
{

    
    player->nbhabitant=0;
    
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
        rectfill(detection, 24, 202, 101, 279, makecol(254, 0, 0)); //batiment
        rectfill(detection, 24, 296, 101, 373, makecol(253, 0, 0));//chateau
        rectfill(detection, 24, 390, 101, 467, makecol(252, 0, 0));//caserne
        rectfill(detection, 24, 484, 101, 561, makecol(251, 0, 0));//centrale

        int couleurpixel;
        blit(map,page,0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_centre_ex(page, font, 930, 726, makecol(0, 0, 0), -1, "%d :", minutes);
        textprintf_centre_ex(page, font, 960, 726, makecol(0, 0 ,0), -1, "%d", timer / 1000);
        textprintf_centre_ex(page, font, 750, 726, makecol(0, 0, 0), -1, "%d ECEflouz", player->argent);
        textprintf_centre_ex(page, font, 250, 726, makecol(0, 0, 0), -1, "%d", player->nbhabitant);
        textprintf_centre_ex(page, font, 100, 500, makecol(255, 255, 255), -1, "souris : %d %d", mouse_x, mouse_y);
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
                printf("%d",condi);
                while (condi == 0)
                {
                    case_actu.x1 = 0;
                    case_actu = detecterCase(plateau,page,batiment->water.iconeeau,map,player);
                    if (case_actu.x1 != 0)
                        condi = 1;
                }
                creation_chateau(player,case_actu,batiment,reseau);
            }

        }
        evolution_batiment(player,batiment,condition);
        if (timer >= 60000)
        {

            timer = 0;
            marqueur = timer;
            minutes += 1;
        }
        for(int z=0;z<player->nbpropriete;z++)
            draw_sprite(page,player->propriete[z].icone,player->propriete[z].x1,player->propriete[z].y1);
        textprintf_centre_ex(page, font, 500, 300, makecol(255, 255, 255), -1, "%d - %d", case_actu.x1, case_actu.y1);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        clear(page);
    }
}
int evolution_batiment(t_joueur* player,t_bat* batiment, int* condition){
    for (int z = 0; z < player->nbpropriete; z++)
        {
            //printf("%d : %d \n", z, player->propriete[z].niveau);
            //printf("%d : %d \n", z, batiment[player->propriete[z].niveau + 1].habitant-batiment[player->propriete[z].niveau].habitant);
            //printf("%d : %d \n", z, batiment[player->propriete[z].niveau].habitant);
            if (timer - player->propriete[z].marqueur >= 15000  && player->propriete[z].niveau < 4 && condition[z]==0)
            {
                player->propriete[z].habitant = batiment[player->propriete[z].niveau + 1].habitant;
                player->propriete[z].icone=batiment[player->propriete[z].niveau + 1].icone;
                player->nbhabitant += batiment[player->propriete[z].niveau + 1].habitant - batiment[player->propriete[z].niveau].habitant;
                player->propriete[z].niveau += 1;
                player->propriete[z].marqueur = timer;
                condition[z]=1;
            }
        }
}
int creation_chateau(t_joueur* player,t_case case_actu, t_bat* batiment,t_graphe* reseau){
            player->argent-=100000;
            t_eau new;
            new.x1 = case_actu.x1;
            new.x2 = case_actu.x2;
            new.y1 = case_actu.y1; // intialisation nouvelle case
            new.y2 = case_actu.y2;
            new.iconeeau=batiment->water.iconeeau;
            if(reseau->chateau->x1==0){

                reseau->chateau=&new;
                reseau->chateau->next=NULL;
                player->nbpropriete+=1;
            }
            else{
                while(reseau->chateau->next!=NULL){
                    reseau->chateau=reseau->chateau->next;

                }
                reseau->chateau->next=(t_eau*)malloc(1*sizeof(t_eau));
                reseau->chateau->next=&new;
                }
}
int creation_batiment(t_joueur* player,t_case case_actu, t_bat* batiment){
                
                player->argent -= 1000;

                t_bat new;
                new.x1 = case_actu.x1;
                new.x2 = case_actu.x2;
                new.y1 = case_actu.y1; // intialisation nouvelle case
                new.y2 = case_actu.y2;
                strcpy(new.nom, batiment[0].nom);
                new.prix = batiment[0].prix,
                new.niveau = 0;
                new.icone=batiment[0].icone;
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

int main()
{
    BITMAP *page;
    BITMAP *detection;
    BITMAP *accueil;
    BITMAP* map;
    int modedejeu = 0;

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
    map=load_bitmap("ingame.bmp",NULL);
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

            mode_capitaliste(page, detection, batiment, player,map,reseau);
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
    return 0;
}
END_OF_MAIN();
