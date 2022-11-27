#include "biblio.h"

/*void charger_sauvegarde(t_joueur *player){
    FILE*sauvegarde = fopen("sauvegarde.txt","r");//Mode lecture
    fscanf(sauvegarde,"%d\n",&player->argent);
    fscanf(sauvegarde,"%d\n",&player->nbhabitant);
    fscanf(sauvegarde,"%d\n",&player->nbpropriete);
    fscanf(sauvegarde,"%d\n",&player-> nbroute);
    for(int z = 0; z < player->nbpropriete; z++){
    fscanf(sauvegarde,"%d\n",&player->propriete[z].x1);
    fscanf(sauvegarde,"%d\n",&player->propriete[z].y1);
    fscanf(sauvegarde,"%d\n",&player->propriete[z].b_num);
    }
    for (int k = 0; k < player->nbroute; k++){
        fscanf(sauvegarde,"%d\n",&player->bitume[k].x);
        fscanf(sauvegarde,"%d\n",&player->bitume[k].y);
        fscanf(sauvegarde,"%d\n",&player->bitume[k].r_num);
    }

    printf("%d\n",player->argent);
    fclose(sauvegarde);

}*/

/*void sauvegarde(t_joueur *player){
    FILE* sauvegarde = fopen("sauvegarde.txt","w+");
    fprintf(sauvegarde,"%d\n",player->argent);
    fprintf(sauvegarde,"%d\n",player->nbhabitant);
    fprintf(sauvegarde,"%d\n",player->nbpropriete);
    fprintf(sauvegarde,"%d\n",player-> nbroute);
    for(int z = 0; z < player->nbpropriete; z++){
    fprintf(sauvegarde,"%d\n",player->propriete[z].x1);
    fprintf(sauvegarde,"%d\n",player->propriete[z].y1);
    fprintf(sauvegarde,"%d\n",player->propriete[z].b_num);}
    for (int k = 0; k < player->nbroute; k++){
        fprintf(sauvegarde,"%d\n",player->bitume[k].x);
        fprintf(sauvegarde,"%d\n",player->bitume[k].y);
        fprintf(sauvegarde,"%d\n",player->bitume[k].r_num);
    }
    printf("%d\n",player->argent);
    fclose(sauvegarde);
    }*/
/*void charger_map(t_joueur){
    FILE*map = fopen("map.txt","w+");//Mode lecture
   for(int i =0;i<35;i++){
        for(int j = 0 ; j<45;j++){
            fprintf(map,"%d",tab[i][j]);
        }
   }
    fclose(map);

}
/*

void sauvegarde(t_joueur *player){
    FILE* sauvegarde = fopen("sauvegarde.txt","w+");
    fprintf(sauvegarde,"%d\n",player->argent);
    fprintf(sauvegarde,"%d\n",player->nbhabitant);
    fprintf(sauvegarde,"%d\n",player->nbpropriete);
    fprintf(sauvegarde,"%d\n",player-> nbroute);
    for(int z = 0; z < player->nbpropriete; z++){
    fprintf(sauvegarde,"%d\n",player->propriete[z].x1);
    fprintf(sauvegarde,"%d\n",player->propriete[z].y1);
    fprintf(sauvegarde,"%d\n",player->propriete[z].b_num);}
    for (int k = 0; k < player->nbroute; k++){
        fprintf(sauvegarde,"%d\n",player->bitume[k].x);
        fprintf(sauvegarde,"%d\n",player->bitume[k].y);
        fprintf(sauvegarde,"%d\n",player->bitume[k].r_num);
    }
    printf("%d\n",player->argent);
    fclose(sauvegarde);
    }
*/
