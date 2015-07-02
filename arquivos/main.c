/*=====================================================
                    NOME DO JOGO

                  desenvolvido por
            Sophia Klein e Sidarta Correa

Versão: 1.0
Data da última alteração: 03/07/2015
=======================================================*/
#include "objects.h"

//PROTÓTIPOS
void InitPlayer(struct PLAYER *player);
void LoadSpritesPlayer(struct PLAYER *player);
void DrawPlayer(struct PLAYER *player);
void MovePlayerRight(struct PLAYER *player);
void MovePlayerLeft(struct PLAYER *player);
void PlayerJump(struct PLAYER *player, int key);
void DrawBoxes(struct BOXES boxes[]);
void InitBoxes(struct BOXES boxes[]);
void LoadSpritesBoxes(struct BOXES boxes[]);
void InitBirds(struct BIRDS birds[], int sequencia[]);
void DrawBirds(struct BIRDS birds[]);
void DrawPentagram();
void CheckCollision(struct PLAYER *player, struct BOXES boxes[], int *j, int *timerColisao);
void CheckSequencias(struct PLAYER *player, int seqCerta[], int *j, int *state);

//VARIÁVEIS GLOBAIS
int timerColisao = 0;

int main(int argc, char **argv)
{
    //VARIÁVEIS
    int seqCerta[NUM_BIRDS];
    int numColisoes = 0;
    int state = MENU;
    int i,j,k;
    enum key_tag {KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ENTER, KEY_ESC, teclasTotal};
    bool redraw = true;
    bool quit = false;
    bool key[teclasTotal];
    for(i = 0; i < teclasTotal; i++)
        key[i] = 0;

    //VARIÁVEIS DE OBJETOS
    struct PLAYER jogador;
    struct BOXES caixas[NUM_BOXES];
    struct BIRDS passaros[NUM_BIRDS];

    //VARIÁVEIS DA ALLEGRO
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font_24, *font_48, *font_12;
    ALLEGRO_BITMAP *background, *foreground, *cleff;
    ALLEGRO_SAMPLE *bgsound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgsoundInstance= NULL;

/*//////////////////////////////INICIALIZA ALLEGRO//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

    //INICIALIZAÇÕES
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }
     if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }
    if(!al_reserve_samples(1))
    {
        fprintf(stderr, "failed to reserve sample!\n");
        return -1;
    }
    bgsound = al_load_sample("sounds/nyan.wav");
    if(!bgsound)
    {
        fprintf(stderr, "failed to load sound!\n");
        al_destroy_display(display);
        al_destroy_sample(bgsound);
        return -1;
    }
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    bgsoundInstance = al_create_sample_instance(bgsound);
    al_set_sample_instance_playmode(bgsoundInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgsoundInstance, al_get_default_mixer());

    //CARREGAR FONTES
    font_24 = al_load_font("casale.ttf", 24, 0);
    font_48 = al_load_font("casale.ttf", 48, 0);
    font_12 = al_load_font("casale.ttf", 12, 0);

    //CARREGAR SPRITES
    LoadSpritesBoxes(caixas);
    LoadSpritesPlayer(&jogador);
    for(i=0; i<NUM_BIRDS; i++)
        passaros[i].sprite = al_load_bitmap("sprites/bird0.png");
    background = al_load_bitmap("sprites/background.png");
    foreground = al_load_bitmap("sprites/foreground.png");
    cleff = al_load_bitmap("sprites/cleff.png");

    //LISTA DOS POSSIVEIS EVENTOS
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    //PREPARA A TELA
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

/*//////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
    while(!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //CASO TECLA PRESSIONADA
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = 1;
                break;
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = 1;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = 1;
                break;
            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]= 1;
                break;
            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER]= 1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                key[KEY_ESC]= 1;
                break;
            default:
                break;
            }//end of switch
        }//end of if event

        //CASO TECLA LIBEERADA
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = 0;
                break;
            case ALLEGRO_KEY_LEFT:
                key[KEY_LEFT] = 0;
                break;
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = 0;
                break;
            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]= 0;
                break;
            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER]= 0;
                break;
            case ALLEGRO_KEY_ESCAPE:
                key[KEY_ESC]= 0;
                break;
            default:
                break;
            }//end of switch
        }//end of else if event

        //FECHAR O PROGRAMA
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || key[KEY_ESC])
        {
            quit = 1;
        }

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
        //EVENT TIMER (LOGICA DO JOGO)
/**verificar coisas comentadas!!!!! **/

        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            switch(state)
            {
            case MENU:
                //(RE)INICIALIZAÇÕES
                al_play_sample_instance(bgsoundInstance);
                InitPlayer(&jogador);
                InitBoxes(caixas);
                InitBirds(passaros, seqCerta);
                numColisoes = 0;

                if(key[KEY_SPACE])
                {
                    state = PLAYING;
                    key[KEY_SPACE] = 0;
                }
                /*/
                if(key[KEY_SPACE])
                {
                    state = INTRO;
                    key[KEY_SPACE] = 0;
                }
                /*/
                break;
            /*/
            case INTRO:
                if(key[KEY_SPACE])
                {
                    state = PLAYING;
                    key[KEY_SPACE] = 0;
                }
                //contagem de frames
                break;
            /*/

            case PLAYING:

                //MOVIMENTAÇÃO DO PLAYER
                if(key[KEY_RIGHT])
                {
                    MovePlayerRight(&jogador);
                    jogador.frame_dir = RIGHT;
                    jogador.frame_act = WALK;
                }
                if(key[KEY_LEFT])
                {
                    MovePlayerLeft(&jogador);
                    jogador.frame_dir = LEFT;
                    jogador.frame_act = WALK;
                }
                else if(!key[KEY_RIGHT] && !key[KEY_LEFT] && !key[KEY_UP])
                {
                    jogador.frame_act = STAND;
                }
                PlayerJump(&jogador, key[KEY_UP]);

                //CHECAGEM DE COLISÃO
                CheckCollision(&jogador, caixas, &numColisoes, &timerColisao);

                //VIDAS E PONTUAÇÃO
                CheckSequencias(&jogador, seqCerta, &numColisoes, &state);

                //ANIMAÇÃO
                jogador.frame_count++;
                if(jogador.frame_count >= jogador.frame_delay)
                {
                    jogador.frame_cur++;
                    if(jogador.frame_cur >= SPRITE_CUR)
                    {
                        jogador.frame_cur = 0;
                    }
                    jogador.frame_count = 0;
                }
                //no break

            case GAMEOVER:
                if(key[KEY_SPACE])
                {
                    state = MENU;
                    key[KEY_SPACE] = 0;
                }
                break;

            case YOUWIN:
                if(key[KEY_SPACE])
                {
                    state = MENU;
                    key[KEY_SPACE] = 0;
                }
            /*/
                NAO TER UM CASO YOUWIN
                AO INVES DISSO, CADA VEZ QUE
                ACERTAR UMA SEQUENCIA IMPRIME "ACERTOU"
                NA TELA E DA MAIS PONTOS PRO JOGADOR
                DEPOIS DISSO REINICIA OS PASSAROS
                E CONTINUA O JOGO
                SE QUISER SAIR, TEM QUE APERTAR ESPAÇO
            /*/
                break;

            }//end of switch
        }//end of TIMER

/*//////////////////////////////PARTE GRAFICA///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            //CORES
            ALLEGRO_COLOR color_bg = al_map_rgb(119, 220, 217);
            ALLEGRO_COLOR color_green = al_map_rgb(0, 139, 69);
            ALLEGRO_COLOR color_white = al_map_rgb(255, 255, 255);
            ALLEGRO_COLOR color_black = al_map_rgb(0, 0, 0);

            switch(state)
            {
            case MENU:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(foreground, 0, 0, 0);
                /*/DESENHAR OS JOGADORES DA BANDA TOCANDO FELIZINHOS/*/
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "NOME");
                al_draw_text(font_24, color_white, SCREEN_W/4, 500, ALLEGRO_ALIGN_CENTER, "START GAME [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W*3/4, 500, ALLEGRO_ALIGN_CENTER, "QUIT [PRESS ESC]");
                al_draw_text(font_12, color_white, SCREEN_W/2, 180, ALLEGRO_ALIGN_CENTER, "DEVELOPED BY S2");
                al_flip_display();
                break;

                /*/
            case INTRO:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                DrawBirds(passaros);
                al_draw_bitmap(foreground, 0, 0, 0);

                //FUNÇAO PRA DESENHAR E ANIMAR CADA UM DOS PERSONAGENS
                CONTAGEM DE TEMPO PRA CONTINUAREM TOCANDO
                QUANDO ACABA CONTAGEM,
                IMPRIME PASSARINHOS CHEGANDO E POUSANDO
                CONTA OUTRO TIMER
                QUANDO ACABA O OUTRO TIMER
                IMPRIME O PESSOAL DA BANDA FICANDO REVOLTADO
                CONTA TIMER DE NOVO
                IMPRIME O OBJETIVO DO JOGO NA TELA
                //
                al_flip_display();
                break;
                /*/

            case PLAYING:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(cleff,100,90,0);
                DrawBirds(passaros);
                al_draw_bitmap(foreground, 0, 0, 0);
                DrawPlayer(&jogador);
                DrawBoxes(caixas);
                /*/
                !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                DESENHAR AS VIDAS E OS SCORES
                !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                /*/
                //DEBUG//al_draw_textf(font_24, color_white, 100, 150, ALLEGRO_ALIGN_CENTER, "timerColisao: %d", timerColisao);al_draw_textf(font_24, color_white, 100, 200, ALLEGRO_ALIGN_CENTER, "contg: %d", numColisoes);al_draw_textf(font_24, color_white, 100, 250, ALLEGRO_ALIGN_CENTER, "player colidiu: %d", jogador.colidiu); //
                al_flip_display();
                break;

            case GAMEOVER:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(foreground, 0, 0, 0);
                /*/DESENHAR OS JOGADORES DA BANDA TRISTES/*/
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_text(font_24, color_white, SCREEN_W/4, 500, ALLEGRO_ALIGN_CENTER, "TRY AGAIN [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W*3/4, 500, ALLEGRO_ALIGN_CENTER, "QUIT [PRESS ESC]");
                al_flip_display();
                break;

            case YOUWIN:
                /*/
                !!!!!!!!!!!!
                DELETAR!!!!!
                !!!!!!!!!!!!
                /*/
                al_clear_to_color(color_green);
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_draw_text(font_24, color_white, SCREEN_W/2, 300, ALLEGRO_ALIGN_CENTER, "> TRY AGAIN [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, "> QUIT [PRESS ESC]");
                al_flip_display();
                break;
            }//switch(state)
        }//if da parte grafica
    }//while

/*//////////////////////////////DESTROI AS COISAS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

    for(i = 0; i < SPRITE_ACT; i++)
    {
        for(j = 0; j < SPRITE_DIR; j++)
        {
            for(k = 0; k < SPRITE_CUR; k++)
            {
                al_destroy_bitmap(jogador.sprite[i][j][k]);
            }
        }
    }
    for(i=0; i <NUM_BOXES; i++)
    {
        al_destroy_bitmap(caixas[i].sprite);
    }
    for(i=0; i<NUM_BIRDS; i++)
    {
        al_destroy_bitmap(passaros[i].sprite);
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(foreground);
    al_destroy_font(font_24);
    al_destroy_font(font_48);
    al_destroy_font(font_12);
    al_destroy_timer(timer);
    al_destroy_sample(bgsound);
    al_destroy_sample_instance(bgsoundInstance);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
