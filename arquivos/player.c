#include "objects.h"

void InitPlayer(struct PLAYER *player)
{
    int i;
    player->width = 60;
    player->height = 100;
    player->pos_inicial_x = 75;
    player->pos_inicial_y = 540 - player->height;
    player->x = player->pos_inicial_x;
    player->y = player->pos_inicial_y;
    player->dy = 0;
    player->move_speed = 5;
    player->jump_speed = 10;    //mudar a altura do pulo

    player->colidiu = false;
    player->is_on_solid_ground = true;
    player->may_jump = false;
    for(i=0; i<NUM_BIRDS; i++)
        player->seqJogador[i] = 24;
    player->lifes = 3;  // numero de vidas

    player->frame_count = 0;
    player->frame_delay = 10; //definir a velocidade das frames
    player->frame_act = STAND;//STAND = 0, WALK = 1, JUMP = 2
    player->frame_dir = RIGHT;//RIGHT = 0,  LEFT = 1
    player->frame_cur = 0;

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
                player->frame_act = JUMP;
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
        player->frame_act = JUMP;
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

    for(i=0; i<NUM_BOXES; i++)
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
            player->lifes--;
            break;
        }
    }

    if(*j == NUM_BIRDS)
        (*state) = YOUWIN;

    if(player->lifes <= 0)
        (*state) = GAMEOVER;
}
