#include "objects.h"

//Funções
void InitBirds(struct BIRDS birds[], int sequencia[])  //Inicialização do inimigo
{
    int i, rand_y;

    srand((unsigned)time(NULL));

    for(i = 0; i < NUM_BIRDS; i++)
    {
        rand_y = rand() % NUM_NOTES;
        birds[i].ID = BIRDS;
        birds[i].x = SCREEN_W/5+(SCREEN_W/6)*i;
        birds[i].explosion = false;
        birds[i].raio = 10;  //define o tamanho dos passaros

        switch(rand_y)
        {
        case 0: //do
            birds[i].note = DO;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 1: //re
            birds[i].note = RE;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 2: //mi
            birds[i].note = MI;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 3: //fa
            birds[i].note = FA;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 4: //sol
            birds[i].note = SOL;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 5: //la
            birds[i].note = LA;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        case 6: //si
            birds[i].note = SI;
            birds[i].y = (SCREEN_H/6)+(SCREEN_H/60)*rand_y;// Botar valor do desenho
            break;
        }
    }

    for(i=0; i<NUM_BIRDS; i++)
    {
        sequencia[i] = birds[i].note;
    }
}


