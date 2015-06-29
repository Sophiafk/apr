#include "objects.h"

void CheckCollision(struct PLAYER *player, struct BOXES boxes[])
{
    int j=0;

    while(j < NUM_BIRDS)
    {
        if(!player->colidiu && player->y <= (boxes[DO].y + boxes[DO].height) && (((player->x >= boxes[DO].x) && (player->x <= (boxes[DO].x+boxes[DO].width))) || ((player->x+player->width) >= boxes[DO].x) && ((player->x+player->width) <= (boxes[DO].x+boxes[DO].width))))//collision acima do player
        {
            player->y = boxes[DO].y + boxes[DO].height;
            player->seqJogador[j] = DO;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[RE].y + boxes[RE].height) &&(((player->x >= boxes[RE].x) && (player->x <= (boxes[RE].x+boxes[RE].width))) || ((player->x+player->width) >= boxes[RE].x) && ((player->x+player->width) <= (boxes[RE].x+boxes[RE].width))))//collision acima do player
        {
            player->y = boxes[RE].y + boxes[RE].height;
            player->seqJogador[j] = RE;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[MI].y + boxes[MI].height) &&(((player->x >= boxes[MI].x) && (player->x <= (boxes[MI].x+boxes[MI].width))) || ((player->x+player->width) >= boxes[MI].x) && ((player->x+player->width) <= (boxes[MI].x+boxes[MI].width))))//collision acima do player
        {
            player->y = boxes[MI].y + boxes[MI].height;
            player->seqJogador[j] = MI;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[FA].y + boxes[FA].height) &&(((player->x >= boxes[FA].x) && (player->x <= (boxes[FA].x+boxes[FA].width))) || ((player->x+player->width) >= boxes[FA].x) && ((player->x+player->width) <= (boxes[FA].x+boxes[FA].width))))//collision acima do player
        {
            player->y = boxes[FA].y + boxes[FA].height;
            player->seqJogador[j] = FA;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[SOL].y + boxes[SOL].height) &&(((player->x >= boxes[SOL].x) && (player->x <= (boxes[SOL].x+boxes[SOL].width))) || ((player->x+player->width) >= boxes[SOL].x) && ((player->x+player->width) <= (boxes[SOL].x+boxes[SOL].width))))//collision acima  player
        {
            player->y = boxes[SOL].y + boxes[SOL].height;
            player->seqJogador[j] = SOL;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[LA].y + boxes[LA].height) &&(((player->x >= boxes[LA].x) && (player->x <= (boxes[LA].x+boxes[LA].width))) || ((player->x+player->width) >= boxes[LA].x) && ((player->x+player->width) <= (boxes[LA].x+boxes[LA].width))))//collision acima  player
        {
            player->y = boxes[LA].y + boxes[LA].height;
            player->seqJogador[j] = LA;
            j++;
            player->colidiu = true;
        }
        else if(!player->colidiu && player->y <= (boxes[SI].y + boxes[SI].height) &&(((player->x >= boxes[SI].x) && (player->x <= (boxes[SI].x+boxes[SI].width))) || ((player->x+player->width) >= boxes[SI].x) && ((player->x+player->width) <= (boxes[SI].x+boxes[SI].width))))//collision acima  player
        {
            player->y = boxes[SI].y + boxes[SI].height;
            player->seqJogador[j] = SI;
            j++;
            player->colidiu = true;
        }

        else
        {
            player->colidiu = false;
            break;
        }

    }
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
