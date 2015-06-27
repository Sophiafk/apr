#include "objects.h"

void InitPlayer(struct PLAYER *player)
{
    player->width = 22;
    player->height = 34;
    player->lives = 3;  // numero de vidas
    player->colidiu = false;
    player->pos_inicial_x = 75;
    player->pos_inicial_y = 500 - player->height;
    player->x = player->pos_inicial_x;
    player->y = player->pos_inicial_y;
    player->dy = 0;
    player->move_speed = 5;
    player->jump_speed = 12;    //mudar a altura do pulo
    player->is_on_solid_ground = true;
    player->may_jump = false;
}

void MovePlayerRight(struct PLAYER *player)
{
    player->x += player->move_speed;
    if(player->x + player->width > SCREEN_W)
    {
        player->x = SCREEN_W - player->width;
    }
}

void MovePlayerLeft(struct PLAYER *player)
{
    player->x -= player->move_speed;
    if(player->x < 0 )
    {
        player->x = 0;
    }
}

void PlayerJump(struct PLAYER *player, int key)
{
    player->is_on_solid_ground = (player->y == player->pos_inicial_y);
    if(player->is_on_solid_ground) //testa se pode pular
    {
        if(key && player->y >= player->pos_inicial_y)
        {
            if(player->may_jump)
            {
                player->dy -= player->jump_speed;
                player->may_jump = false;
            }
            else
            {
                player->may_jump = true;
            }
        }
    }
    if(!player->is_on_solid_ground)
    {
        player->dy += gravity; //começa a descer com a gravidade
    }
    if(player->dy > player->jump_speed)
    {
        player->dy = player->jump_speed; //limita uma velocidade maxima pro pulo, o que afeta na altura do pulo
    }

    player->y += player->dy; //aplica as alterações
    if(player->y > player->pos_inicial_y) //determina o limite com o chão depois de pular
    {
        player->dy = 0;
        player->y = player->pos_inicial_y;
    }
}

