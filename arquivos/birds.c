#include "objects.h"

void InitBirds(struct BIRDS birds[], int sequencia[])  //Inicialização do inimigo
{
    int i, rand_y;

    srand((unsigned)time(NULL));

    for(i = 0; i < NUM_BIRDS; i++)
    {
        rand_y = rand() % NUM_NOTES;
        birds[i].x = SCREEN_W/NUM_BIRDS+((SCREEN_W/6)*i);
        birds[i].live = true;
        birds[i].raio = 10;  //define o tamanho dos passaros

        switch(rand_y)
        {
        case 12: //do
            birds[i].note = DO;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 11: //re
            birds[i].note = RE;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 10: //mi
            birds[i].note = MI;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 9: //fa
            birds[i].note = FA;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 8: //sol
            birds[i].note = SOL;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 7: //la
            birds[i].note = LA;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 6: //si
            birds[i].note = SI;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 5: //do#
            birds[i].note = DO;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 4: //re#
            birds[i].note = RE;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 3: //mi#
            birds[i].note = MI;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 2: //fa#
            birds[i].note = FA;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 1: //sol#
            birds[i].note = SOL;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        case 0: //la#
            birds[i].note = LA;
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y; //80
            break;
        }
    }

    //Armazena a sequencia certa dos pássaros
    for(i=0; i<NUM_BIRDS; i++)
    {
        sequencia[i] = birds[i].note;
    }
}
