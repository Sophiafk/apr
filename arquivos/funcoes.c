#include "objects.h"


/*
        if((player->x+player->width) < boxes[i].x ||
           player->x > (boxes[i].x+boxes[i].width) ||
           (player->y+player->height) < boxes[i].y ||
           player->y > (boxes[i].y+boxes[i].height))
        {
            return i;
        }
        else
        {
            return 24;
        }
*/


/*
int i;
    if((player->x+player->width) >= boxes[i].x ) //collision a direita do player
    {
        player->x = boxes[i].x - player->width;
        return i;
    }
    else if(player->x <= (boxes[i].x+boxes[i].width)) //collision a esquerda do player
    {
        player->x = boxes[i].x + boxes[i].width;
        return i;
    }
    else if((player->y+player->height) >= boxes[i].y )//collison abaixo do player
    {
        player->y = boxes[i].y - player->height;

        return i;
    }
    else if(player->y <= (boxes[i].y+boxes[i].height))//collision acima do player
    {
        player->y = boxes[i].y + boxes[i].height;
        return i;
    }
    else
    {
        return 24;
    }

*/


/*
bool Collision(struct PLAYER *player, struct BOXES boxes[])
{
    int i;
    for(i = 0; i < NUM_BOXES; i++)
    {
        if(player->y <= (boxes[DO].y + boxes[DO].height))//collision acima do player
        {
            player->seq[i] = DO;
            player->y = boxes[DO].y + boxes[DO].height;
            return true;
        }
        else if(player->y <= (boxes[RE].y + boxes[RE].height))//collision acima do player
        {
            player->y = boxes[RE].y + boxes[RE].height;
            player->seq[i] = RE;
            return true;
        }
        else if(player->y <= (boxes[MI].y + boxes[MI].height))//collision acima do player
        {
            player->y = boxes[MI].y + boxes[MI].height;
            player->seq[i] = MI;
            return true;
        }
        else if(player->y <= (boxes[FA].y + boxes[FA].height))//collision acima do player
        {
            player->y = boxes[FA].y + boxes[FA].height;
            player->seq[i] = FA;
            return true;
        }
        else if(player->y <= (boxes[SOL].y + boxes[SOL].height))//collision acima do player
        {
            player->y = boxes[SOL].y + boxes[SOL].height;
            player->seq[i] = SOL;
            return true;
        }
        else if(player->y <= (boxes[LA].y + boxes[LA].height))//collision acima do player
        {
            player->y = boxes[LA].y + boxes[LA].height;
            player->seq[i] = LA;
            return true;
        }
        else if(player->y <= (boxes[SI].y + boxes[SI].height))//collision acima do player
        {
            player->y = boxes[SI].y + boxes[SI].height;
            player->seq[i] = SI;
            return true;
        }
        else
        {

            return false;
        }
    }
}
*/

/**
//Quase que bom

bool Collision(struct PLAYER *player, struct BOXES boxes[])
{
    bool j;
    int i;
    for(i = 0; i < NUM_BOXES; i++)
    {
        if(player->y <= (boxes[DO].y + boxes[DO].height) && ((player->x >= boxes[DO].x) && ((player->x+player->width) <= (boxes[DO].x+boxes[DO].width))))//collision acima do player
        {
            player->seq[i] = DO;
            player->y = boxes[DO].y + boxes[DO].height;
            j = true;
        }
        else if(player->y <= (boxes[RE].y + boxes[RE].height) && player->x >= boxes[RE].x && (player->x+player->width) <= (boxes[RE].x+boxes[RE].width))//collision acima do player
        {
            player->y = boxes[RE].y + boxes[RE].height;
            player->seq[i] = RE;
            j = true;
        }
        else if(player->y <= (boxes[MI].y + boxes[MI].height) && player->x >= boxes[MI].x && (player->x+player->width) <= (boxes[MI].x+boxes[MI].width))//collision acima do player
        {
            player->y = boxes[MI].y + boxes[MI].height;
            player->seq[i] = MI;
            j = true;
        }
        else if(player->y <= (boxes[FA].y + boxes[FA].height) && player->x >= boxes[FA].x && (player->x+player->width) <= (boxes[FA].x+boxes[FA].width))//collision acima do player
        {
            player->y = boxes[FA].y + boxes[FA].height;
            player->seq[i] = FA;
            j = true;
        }
        else if(player->y <= (boxes[SOL].y + boxes[SOL].height) && player->x >= boxes[SOL].x && (player->x+player->width) <= (boxes[SOL].x+boxes[SOL].width))//collision acima do player
        {
            player->y = boxes[SOL].y + boxes[SOL].height;
            player->seq[i] = SOL;
            j = true;
        }
        else if(player->y <= (boxes[LA].y + boxes[LA].height) && player->x >= boxes[LA].x && (player->x+player->width) <= (boxes[LA].x+boxes[LA].width))//collision acima do player
        {
            player->y = boxes[LA].y + boxes[LA].height;
            player->seq[i] = LA;
            j = true;
        }
        else if(player->y <= (boxes[SI].y + boxes[SI].height) && player->x >= boxes[SI].x && (player->x+player->width) <= (boxes[SI].x+boxes[SI].width))//collision acima do player
        {
            player->y = boxes[SI].y + boxes[SI].height;
            player->seq[i] = SI;
            j = true;
        }
        else
        {
            j = false;
        }
    }
    return j;
}



**/
