#include "objects.h"

//CARREGAR SPRITES
void LoadSpritesPlayer(struct PLAYER *player)
{
    //STAND, RIGHT
    player->sprite[0][0][0] = al_load_bitmap("sprites/[0][0][0].png");
    player->sprite[0][0][1] = al_load_bitmap("sprites/[0][0][1].png");
    player->sprite[0][0][2] = al_load_bitmap("sprites/[0][0][2].png");
    player->sprite[0][0][3] = al_load_bitmap("sprites/[0][0][3].png");
    player->sprite[0][0][4] = al_load_bitmap("sprites/[0][0][4].png");
    player->sprite[0][0][5] = al_load_bitmap("sprites/[0][0][5].png");
    player->sprite[0][0][6] = al_load_bitmap("sprites/[0][0][6].png");
    player->sprite[0][0][7] = al_load_bitmap("sprites/[0][0][7].png");
    //STAND, LEFT
    player->sprite[0][1][0] = al_load_bitmap("sprites/[0][1][0].png");
    player->sprite[0][1][1] = al_load_bitmap("sprites/[0][1][1].png");
    player->sprite[0][1][2] = al_load_bitmap("sprites/[0][1][2].png");
    player->sprite[0][1][3] = al_load_bitmap("sprites/[0][1][3].png");
    player->sprite[0][1][4] = al_load_bitmap("sprites/[0][1][4].png");
    player->sprite[0][1][5] = al_load_bitmap("sprites/[0][1][5].png");
    player->sprite[0][1][6] = al_load_bitmap("sprites/[0][1][6].png");
    player->sprite[0][1][7] = al_load_bitmap("sprites/[0][1][7].png");
    //WALK, RIGHT
    player->sprite[1][0][0] = al_load_bitmap("sprites/[1][0][0].png");
    player->sprite[1][0][1] = al_load_bitmap("sprites/[1][0][1].png");
    player->sprite[1][0][2] = al_load_bitmap("sprites/[1][0][2].png");
    player->sprite[1][0][3] = al_load_bitmap("sprites/[1][0][3].png");
    player->sprite[1][0][4] = al_load_bitmap("sprites/[1][0][4].png");
    player->sprite[1][0][5] = al_load_bitmap("sprites/[1][0][5].png");
    player->sprite[1][0][6] = al_load_bitmap("sprites/[1][0][6].png");
    player->sprite[1][0][7] = al_load_bitmap("sprites/[1][0][7].png");
    //WALK, LEFT
    player->sprite[1][1][0] = al_load_bitmap("sprites/[1][1][0].png");
    player->sprite[1][1][1] = al_load_bitmap("sprites/[1][1][1].png");
    player->sprite[1][1][2] = al_load_bitmap("sprites/[1][1][2].png");
    player->sprite[1][1][3] = al_load_bitmap("sprites/[1][1][3].png");
    player->sprite[1][1][4] = al_load_bitmap("sprites/[1][1][4].png");
    player->sprite[1][1][5] = al_load_bitmap("sprites/[1][1][5].png");
    player->sprite[1][1][6] = al_load_bitmap("sprites/[1][1][6].png");
    player->sprite[1][1][7] = al_load_bitmap("sprites/[1][1][7].png");
    //JUMP, RIGHT
    player->sprite[2][0][0] = al_load_bitmap("sprites/[2][0][0].png");
    player->sprite[2][0][1] = al_load_bitmap("sprites/[2][0][1].png");
    player->sprite[2][0][2] = al_load_bitmap("sprites/[2][0][2].png");
    player->sprite[2][0][3] = al_load_bitmap("sprites/[2][0][3].png");
    player->sprite[2][0][4] = al_load_bitmap("sprites/[2][0][4].png");
    player->sprite[2][0][5] = al_load_bitmap("sprites/[2][0][5].png");
    player->sprite[2][0][6] = al_load_bitmap("sprites/[2][0][6].png");
    player->sprite[2][0][7] = al_load_bitmap("sprites/[2][0][7].png");
    //JUMP, LEFT
    player->sprite[2][1][0] = al_load_bitmap("sprites/[2][1][0].png");
    player->sprite[2][1][1] = al_load_bitmap("sprites/[2][1][1].png");
    player->sprite[2][1][2] = al_load_bitmap("sprites/[2][1][2].png");
    player->sprite[2][1][3] = al_load_bitmap("sprites/[2][1][3].png");
    player->sprite[2][1][4] = al_load_bitmap("sprites/[2][1][4].png");
    player->sprite[2][1][5] = al_load_bitmap("sprites/[2][1][5].png");
    player->sprite[2][1][6] = al_load_bitmap("sprites/[2][1][6].png");
    player->sprite[2][1][7] = al_load_bitmap("sprites/[2][1][7].png");
}

void LoadSpritesBoxes(struct BOXES boxes[])
{
    boxes[DO].sprite = al_load_bitmap("sprites/DO.png");
    boxes[RE].sprite = al_load_bitmap("sprites/RE.png");
    boxes[MI].sprite = al_load_bitmap("sprites/MI.png");
    boxes[FA].sprite = al_load_bitmap("sprites/FA.png");
    boxes[SOL].sprite = al_load_bitmap("sprites/SOL.png");
    boxes[LA].sprite = al_load_bitmap("sprites/LA.png");
    boxes[SI].sprite = al_load_bitmap("sprites/SI.png");
}

//DESENHAR
void DrawPentagram()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        al_draw_line(0,((SCREEN_H/6)+(SCREEN_H/30)*i),SCREEN_W,((SCREEN_H/6)+(SCREEN_H/30)*i),al_map_rgb(0,0,0),2);
    }
}

void DrawBirds(struct BIRDS birds[])
 {
    int i;
    for(i = 0; i < NUM_BIRDS; i++)
    {
        if(birds[i].live)
        {
            al_draw_bitmap(birds[i].sprite, birds[i].x, birds[i].y-10, 0);
        }
        else
            al_draw_filled_circle(birds[i].x, birds[i].y, birds[i].raio, al_map_rgb(255,255,255));

    }
}

void DrawBoxes(struct BOXES boxes[])
{
    int i;
    for(i = 0; i < NUM_BOXES; i++)
    {
        al_draw_bitmap(boxes[i].sprite, boxes[i].x, boxes[i].y, 0);
    }
}

void DrawPlayer(struct PLAYER *player)
{
    al_draw_bitmap(player->sprite[player->frame_act][player->frame_dir][player->frame_cur], player->x, player->y, 0);
}

