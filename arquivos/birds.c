#include "objects.h"

/** posições das notas estao certas agora**/

void InitBirds(struct BIRDS birds[], int sequencia[])  //Inicialização do inimigo
{
    int i, rand_y;

    srand((unsigned)time(NULL));

    for(i = 0; i < NUM_BIRDS; i++)
    {
        rand_y = rand() % NUM_NOTES;
        birds[i].x = SCREEN_W/5+((SCREEN_W/6)*i);
        birds[i].live = true;
        birds[i].raio = 10;  //define o tamanho dos passaros

        switch(rand_y)
        {
        case 6: //do
            birds[i].note = DO;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 5: //re
            birds[i].note = RE;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 4: //mi
            birds[i].note = MI;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 3: //fa
            birds[i].note = FA;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 2: //sol
            birds[i].note = SOL;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 1: //la
            birds[i].note = LA;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        case 0: //si
            birds[i].note = SI;
            birds[i].y = (SCREEN_H/4.28)+(SCREEN_H/60)*rand_y;
            break;
        }
    }

    //Armazena a sequencia certa dos pássaros
    for(i=0; i<NUM_BIRDS; i++)
    {
        sequencia[i] = birds[i].note;
    }
}

void DrawBirds(struct BIRDS birds[])  // desenho do inimigo
 {
    int i;

    for(i = 0; i < NUM_BIRDS; i++)
    {
        if(birds[i].live)
        {
            al_draw_filled_circle(birds[i].x, birds[i].y, birds[i].raio, al_map_rgb(0,0,0));
        }
        else
            al_draw_filled_circle(birds[i].x, birds[i].y, birds[i].raio, al_map_rgb(255,255,255));

    }
}
