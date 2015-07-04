#include "objects.h"

//FUNÇÕES PLAYER
void InitPlayer(struct PLAYER *player)
{
    int i;
    //posição
    player->width = 60;
    player->height = 100;
    player->pos_inicial_x = 75;
    player->pos_inicial_y = 540 - player->height;
    player->x = player->pos_inicial_x;
    player->y = player->pos_inicial_y;
    player->dy = 0;
    player->move_speed = 5;
    player->jump_speed = 10;    //mudar a altura do pulo
    //colisão
    player->colidiu = false;
    player->is_on_solid_ground = true;
    player->may_jump = false;
    //vidas
    for(i=0; i<NUM_BIRDS; i++)
        player->seqJogador[i] = NENHUMA;
    player->lifes = 3;  // numero de vidas
    //animação
    player->frame_count = 0;
    player->frame_delay = 10; //definir a velocidade das frames
    player->frame_act = STAND;//STAND = 0, WALK = 1, JUMP = 2
    player->frame_dir = RIGHT;//RIGHT = 0,  LEFT = 1
    player->frame_cur = 0;
}

void MovePlayerRight(struct PLAYER *player)
{
    //move pra direita
    player->x += player->move_speed;
    //limite da tela
    if(player->x + player->width > SCREEN_W)
    {
        player->x = SCREEN_W - player->width;
    }
}

void MovePlayerLeft(struct PLAYER *player)
{
    //move pra esquerda
    player->x -= player->move_speed;
    //limite da tela
    if(player->x < 0 )
    {
        player->x = 0;
    }
}

void PlayerJump(struct PLAYER *player, int key)
{
    player->is_on_solid_ground = (player->y == player->pos_inicial_y);
    //se estiver no chão permite pular
    if(player->is_on_solid_ground && key)
    {
        if(player->may_jump)
        {
            player->frame_act = JUMP;
            player->dy -= player->jump_speed;
            player->may_jump = false;
        }
        else
            player->may_jump = true;
    }
    //caso contrário, desce com a gravidade
    else if(!player->is_on_solid_ground)
    {
        player->frame_act = JUMP;
        player->dy += gravity;
    }

    //limita velocidade maxima pro pulo
    if(player->dy > player->jump_speed)
    {
        player->dy = player->jump_speed;
    }

    //aplica as alterações na posição
    player->y += player->dy;

    //limite com o chão
    if(player->y > player->pos_inicial_y)
    {
        player->dy = 0;
        player->y = player->pos_inicial_y;
    }
}

//FUNÇÕES BOXES
void InitBoxes(struct BOXES boxes[])
{
    int i, j = 2;
    for(i = 0; i < NUM_BOXES; i++)
    {
        boxes[i].width = SCREEN_W/17;
        boxes[i].height = SCREEN_H/12;
        boxes[i].x = SCREEN_W*j/17; // posição em x da caixa é incrementada
        boxes[i].y = SCREEN_H/2;
        boxes[i].dy = SCREEN_H/2;
        boxes[i].subir = false;
        j += 2;
    }
}

void BoxesUp(struct BOXES boxes[], struct PLAYER *player)
{
    int i=0;
    for(i = 0; i < NUM_BOXES; i++)
    {
        if(player->colidiu == true && player->notaAtual == i)
        {
            boxes[i].dy--;
            boxes[i].subir = true;
        }
        if(player->colidiu == false)
        {
            boxes[i].subir = false;
            boxes[i].dy = SCREEN_H/2;
        }
    }
}

//FUNÇÕES BIRDS
void InitBirds(struct BIRDS birds[], int sequencia[]){

    int i, rand_y;
    srand((unsigned)time(NULL));

    for(i = 0; i < NUM_BIRDS; i++)
    {
        rand_y = rand() % NUM_NOTES;    //valor aleatório entre 0 e NUM_NOTES
        birds[i].x = SCREEN_W/NUM_BIRDS+((SCREEN_W/(NUM_BIRDS+1))*i);
        birds[i].live = true;
        birds[i].raio = 10;     //tamanho dos passaros

        //associa valor aleatório com nota e atribui posição na tela
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
            birds[i].y = (SCREEN_H/7.5)+(SCREEN_H/60)*rand_y;
            break;
        }
    }

    //Armazena a sequencia certa de notas geradas
    for(i=0; i<NUM_BIRDS; i++)
    {
        sequencia[i] = birds[i].note;
    }
}

//FUNÇÕES COLISÃO: PLAYER E BOXES
void CheckCollision(struct PLAYER *player, struct BOXES boxes[], int *j, int *timerColisao)
{
    int i;
    //espaço de tempo entre o registro de duas colisões
    if(player->colidiu == true)
    {
        (*timerColisao)++;
        if((*timerColisao) > 30)
        {
            player->colidiu = false;
            (*timerColisao) = 0;
        }
    }

    //registro de colisões
    for(i=0; i<NUM_BOXES; i++)
    {
        //testa se player colide com a parte de baixo de alguma caixa
        if(player->y <= (boxes[i].y + boxes[i].height) && (((player->x >= boxes[i].x) && (player->x <= (boxes[i].x+boxes[i].width))) || ((player->x+player->width) >= boxes[i].x) && ((player->x+player->width) <= (boxes[i].x+boxes[i].width))))//collision acima do player
        {
            //limite da caixa
            player->y = boxes[i].y + boxes[i].height;
            if (*timerColisao==0)
            {
                //armazena a sequencia tocada pelo jogador
                player->seqJogador[*j] = i;
                (*j)++;
                player->notaAtual = i;
                player->colidiu = true;
            }
        }
    }
}

void CheckSequencias(struct PLAYER *player, int seqCerta[], int *j, int *state, struct BIRDS birds[], int *score, int *scoreBirds)
{
    int i,m;

    //compara a sequência certa com a sequência do jogador
    for(i=0; i<NUM_BIRDS; i++)
    {
        if(seqCerta[i] == player->seqJogador[i])
        {
            //uma nota certa
            birds[i].live = false;

        }
        else if(player->seqJogador[i] < NENHUMA)
        {
            //uma nota errada
            (*j) = 0;
            player->seqJogador[i] = NENHUMA;
            player->lifes--;
            for(m=0; m<NUM_BIRDS; m++)
                birds[m].live = true;
            break;
        }
    }

    //toda sequência certa
    if(*j == NUM_BIRDS)
    {
        (*state) = YOUWIN;
        (*score)++;
    }

    //todas vidas perdidas
    if(player->lifes < 0)
    {
        (*state) = GAMEOVER;
        (*scoreBirds)++;
    }
}
