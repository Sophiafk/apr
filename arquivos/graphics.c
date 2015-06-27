#include "objects.h"

void DrawPentagram()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        al_draw_line(0,((SCREEN_H/6)+(SCREEN_H/30)*i),SCREEN_W,((SCREEN_H/6)+(SCREEN_H/30)*i),al_map_rgb(0,0,0),2);
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

 void DrawBirds(struct BIRDS birds[])  // desenho do inimigo
 {
    int i;

    for(i = 0; i < NUM_BIRDS; i++)
    {
        if(!birds[i].explosion)
        {
            al_draw_filled_circle(birds[i].x, birds[i].y, birds[i].raio, al_map_rgb(0,0,0));
        }
        else
            al_draw_filled_circle(birds[i].x, birds[i].y, birds[i].raio, al_map_rgb(255,255,255));

    }
}

void DrawPlayer(struct PLAYER *player)
{
    al_draw_filled_rectangle(player->x, player->y, player->x + player->width, player->y + player->height, al_map_rgb(0,139,69));
}
