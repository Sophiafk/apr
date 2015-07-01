#include "objects.h"

//PROTÓTIPOS
void InitPlayer(struct PLAYER *player);
void DrawPlayer(struct PLAYER *player);
void MovePlayerRight(struct PLAYER *player);
void MovePlayerLeft(struct PLAYER *player);
void PlayerJump(struct PLAYER *player, int key);
void LoadSpritesPlayer(struct PLAYER *player);

void DrawBoxes(struct BOXES boxes[]);
void InitBoxes(struct BOXES boxes[]);
void LoadSpritesBoxes(struct BOXES boxes[]);

void InitBirds(struct BIRDS birds[], int sequencia[]);
void DrawBirds(struct BIRDS birds[]);

void DrawPentagram();

void CheckCollision(struct PLAYER *player, struct BOXES boxes[], int *j, int *timerColisao);
void CheckSequencias(struct PLAYER *player, int seqCerta[], int *j, int *state);

//VARIAVEIS GLOBAIS
int timerColisao = 0;


int main(int argc, char **argv)
{
    //VARIAVEIS
    enum key_tag {KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_LSHIFT, KEY_SPACE, KEY_ENTER, KEY_Y, KEY_N, KEY_ESC, teclasTotal};

    srand(time(NULL));
    int i,j,k;
    bool redraw = true;
    bool quit = false;
    bool key[teclasTotal];
    for(i = 0; i < teclasTotal; i++)
        key[i] = 0;
    int seqCerta[NUM_BIRDS];
    int numColisoes = 0;
    int state = MENU;


    //VARIÁVEIS DE OBJETOS
    struct PLAYER jogador;
    struct BOXES caixas[NUM_BOXES];
    struct BIRDS passaros[NUM_BIRDS];

    //VARIÁVEIS DA ALLEGRO
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font_24, *font_48, *font_124;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *foreground;
    ALLEGRO_BITMAP *cleff;
    ALLEGRO_SAMPLE *bgsound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgsoundInstance= NULL;


///////////////////////////////INICIALIZA ALLEGRO///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


    bgsoundInstance = al_create_sample_instance(bgsound);
    al_set_sample_instance_playmode(bgsoundInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgsoundInstance, al_get_default_mixer());

    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //CARREGAR
    font_24 = al_load_font("casale.ttf", 24, 0);
    font_48 = al_load_font("casale.ttf", 48, 0);
    font_124 = al_load_font("casale.ttf", 124, 0);

    //SPRITE
    background = al_load_bitmap("sprites/background.png");
    foreground = al_load_bitmap("sprites/foreground.png");
    cleff = al_load_bitmap("sprites/cleff.png");
    for(i=0; i<NUM_BIRDS; i++)
    {
        passaros[i].sprite = al_load_bitmap("sprites/bird0.png");
    }
    LoadSpritesBoxes(caixas);
    LoadSpritesPlayer(&jogador);

    //LISTA DOS POSSIVEIS EVENTOS
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    //PREPARA A TELA
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

///////////////////////////////LOOP////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while(!quit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //ARMAZENAR O ESTADO DOS BOTÕES DO TECLADO
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
            case ALLEGRO_KEY_LSHIFT:
                key[KEY_LSHIFT] = 1;
                break;
            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]= 1;
                break;
            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER]= 1;
                break;
            case ALLEGRO_KEY_Y:
                key[KEY_Y]= 1;
                break;
            case ALLEGRO_KEY_N:
                key[KEY_N]= 1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                key[KEY_ESC]= 1;
                break;
            default:
                break;
            }//switch
        }//if event

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
            case ALLEGRO_KEY_LSHIFT:
                key[KEY_LSHIFT] = 0;
                break;
            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE]= 0;
                break;
            case ALLEGRO_KEY_ENTER:
                key[KEY_ENTER]= 0;
                break;
            case ALLEGRO_KEY_Y:
                key[KEY_Y]= 0;
                break;
            case ALLEGRO_KEY_N:
                key[KEY_N]= 0;
                break;
            case ALLEGRO_KEY_ESCAPE:
                key[KEY_ESC]= 0;
                break;
            default:
                break;
            }//switch
        }//else if event

        //EVENT TIMER (LOGICA DO JOGO)
        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            switch(state)
            {
            case MENU:

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
                break;

            case PLAYING:
                if(key[KEY_ENTER])
                {
                    state = GAMEOVER;
                    key[KEY_ENTER] = 0;
                }
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
                CheckCollision(&jogador, caixas, &numColisoes, &timerColisao);
                CheckSequencias(&jogador, seqCerta, &numColisoes, &state);

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
                break;

            }//fecha o switch
        }// fecha o TIMER

        //FECHAR O PROGRAMA SE APERTAR X OU "ESC"
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || key[KEY_ESC])
        {
            quit = 1;
        }

///////////////////////////////PARTE GRAFICA////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                al_draw_text(font_48, color_white, SCREEN_W/2, 150, ALLEGRO_ALIGN_CENTER, "NOME");
                al_draw_text(font_24, color_white, SCREEN_W/2, 300, ALLEGRO_ALIGN_CENTER, "> START GAME [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, "> QUIT [PRESS ESC]");
                al_flip_display();
                break;

            case PLAYING:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(cleff,100,90,0);
                DrawBirds(passaros);
                al_draw_bitmap(foreground, 0, 0, 0);
                DrawPlayer(&jogador);
                DrawBoxes(caixas);
                //DEBUG//al_draw_textf(font_24, color_white, 100, 150, ALLEGRO_ALIGN_CENTER, "timerColisao: %d", timerColisao);al_draw_textf(font_24, color_white, 100, 200, ALLEGRO_ALIGN_CENTER, "contg: %d", numColisoes);al_draw_textf(font_24, color_white, 100, 250, ALLEGRO_ALIGN_CENTER, "player colidiu: %d", jogador.colidiu); //
                al_flip_display();
                break;

            case GAMEOVER:
                al_clear_to_color(color_black);
                al_draw_text(font_48, color_white, SCREEN_W/2, 150, ALLEGRO_ALIGN_CENTER, "GAME OVER");
                al_draw_text(font_24, color_white, SCREEN_W/2, 300, ALLEGRO_ALIGN_CENTER, "> TRY AGAIN [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, "> QUIT [PRESS ESC]");
                al_flip_display();
                break;

            case YOUWIN:
                al_clear_to_color(color_green);
                al_draw_text(font_48, color_white, SCREEN_W/2, 150, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_draw_text(font_24, color_white, SCREEN_W/2, 300, ALLEGRO_ALIGN_CENTER, "> TRY AGAIN [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, "> QUIT [PRESS ESC]");
                al_flip_display();
                break;
            }//switch(state)
        }//if da parte grafica
    }//while

///////////////////////////////DESTROI AS COISAS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    al_destroy_font(font_124);
    al_destroy_timer(timer);
    al_destroy_sample(bgsound);
    al_destroy_sample_instance(bgsoundInstance);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
