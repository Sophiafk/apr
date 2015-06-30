#include "objects.h"


void CheckCollision(struct PLAYER *player, struct BOXES boxes[], int *j, int *timerColisao)
{
    int i;
    if(player->colidiu == true)
    {
        (*timerColisao)++;
        if((*timerColisao) > 30)
        {
            player->colidiu = false;
            (*timerColisao) = 0;
        }
    }

    for(i=0; i<NUM_NOTES; i++)
    {
        if( player->y <= (boxes[i].y + boxes[i].height) && (((player->x >= boxes[i].x) && (player->x <= (boxes[i].x+boxes[i].width))) || ((player->x+player->width) >= boxes[i].x) && ((player->x+player->width) <= (boxes[i].x+boxes[i].width))))//collision acima do player
        {
            player->y = boxes[i].y + boxes[i].height;
            if (*timerColisao==0)
            {
                player->seqJogador[*j] = i;
                (*j)++;
                player->colidiu = true;
            }
        }
    }

    /*/ COLIDIR COM AS LATERAIS DAS CAIXAS
    if(player->y <= (boxes[DO].y + boxes[DO].height) && (player->x+player->width) >= boxes[DO].x  && (player->x+player->width) < (boxes[DO].x+boxes[DO].width))
    {
       player->x = boxes[DO].x - player->width;
    }
    /*/
}

void CheckSequencias(struct PLAYER *player, int seqCerta[], int *j, int *state)
{
    int i;
    for(i=0; i<NUM_BIRDS; i++)
    {
        if(seqCerta[i] == player->seqJogador[i])
        {
            //o que faz quando acerta uma nota
        }
        else if(player->seqJogador[i] < 24)
        {
            (*j) = 0;
            player->seqJogador[i] = 24;
            player->lives--;
            break;
        }
    }

    if(*j == NUM_BIRDS)
        (*state) = YOUWIN;

    if(player->lives <= 0)
        (*state) = GAMEOVER;
}

void InitBoxes(struct BOXES boxes[])
{
    int i, j = 2;
    for(i = 0; i < NUM_BOXES; i++)
    {
        boxes[i].width = SCREEN_W/17;
        boxes[i].height = SCREEN_H/12;
        boxes[i].x = SCREEN_W*j/17; // posição em x da caixa
        boxes[i].y = SCREEN_H/2;
        boxes[i].note = i;
        j += 2;
    }
}

void DrawBoxes(struct BOXES boxes[])
{
    int i;
    for(i = 0; i < NUM_BOXES; i++)
    {
        al_draw_filled_rectangle(boxes[i].x,boxes[i].y, boxes[i].x + boxes[i].width, boxes[i].y + boxes[i].height, al_map_rgb(120,120,120));
    }
}
