/*=====================================================
                SHUT THE BIRDS UP!

                  desenvolvido por
            Sophia Klein e Sidarta Correa

Versão: 1.0
Data da última alteração: 03/07/2015
//bug dos passaros
=======================================================*/
#include "objects.h"

//PROTÓTIPOS
void InitPlayer(struct PLAYER *player);
void LoadSpritesPlayer(struct PLAYER *player);
void DrawPlayer(struct PLAYER *player);
void MovePlayerRight(struct PLAYER *player);
void MovePlayerLeft(struct PLAYER *player);
void PlayerJump(struct PLAYER *player, int key);
void DrawBoxes(struct BOXES boxes[],struct PLAYER *player);
void InitBoxes(struct BOXES boxes[]);
void BoxesUp(struct BOXES boxes[], struct PLAYER *player);
void LoadSpritesBoxes(struct BOXES boxes[]);
void InitBirds(struct BIRDS birds[], int sequencia[]);
void DrawBirds(struct BIRDS birds[]);
void DrawPentagram();
void CheckCollision(struct PLAYER *player, struct BOXES boxes[], int *j, int *timerColisao);
void CheckSequencias(struct PLAYER *player, int seqCerta[], int *j, int *state, struct BIRDS birds[],int *score, int *scoreBirds);

//VARIÁVEIS GLOBAIS
int timerColisao = 0;

int main(int argc, char **argv)
{
    //VARIÁVEIS
    int seqCerta[NUM_BIRDS];
    int numColisoes = 0;
    int state = MENU;
    int i,j,k;
    int score = 0;
    int scoreBirds = 0;
    enum key_tag {KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ENTER, KEY_ESC, KEY_M, teclasTotal};
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
    ALLEGRO_BITMAP *background, *foreground, *cleff, *banda;
    ALLEGRO_SAMPLE *bgsound, *bggameover = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgsoundInstance = NULL, *bggameoverInstance = NULL;
    ALLEGRO_SAMPLE *musicbox1 = NULL,*musicbox2 = NULL,*musicbox3 = NULL,*musicbox4 = NULL,*musicbox5 = NULL,
                   *musicbox6 = NULL,*musicbox7 = NULL,*musicbox8 = NULL,*musicbox9 = NULL,*musicbox10 = NULL,
                   *musicbox11 = NULL,*musicbox12 = NULL,*musicbox13 = NULL, *fail = NULL;
    ALLEGRO_SAMPLE_INSTANCE *musicboxInstance1 = NULL,*musicboxInstance2 = NULL,*musicboxInstance3 = NULL,
                            *musicboxInstance4 = NULL,*musicboxInstance5 = NULL,*musicboxInstance6 = NULL,
                            *musicboxInstance7 = NULL,*musicboxInstance8 = NULL,*musicboxInstance9 = NULL,
                            *musicboxInstance10 = NULL,*musicboxInstance11 = NULL,*musicboxInstance12 = NULL,
                            *musicboxInstance13 = NULL, *failInstance = NULL;
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
    if(!al_reserve_samples(16))
    {
        fprintf(stderr, "failed to reserve sample!\n");
        return -1;
    }
    bgsound = al_load_sample("sounds/intro.wav");
    if(!bgsound)
    {
        fprintf(stderr, "failed to load sound!\n");
        al_destroy_display(display);
        al_destroy_sample(bgsound);
        return -1;
    }
    bggameover = al_load_sample("sounds/birds.wav");
    if(!bggameover)
    {
        fprintf(stderr, "failed to load sound!\n");
        al_destroy_display(display);
        al_destroy_sample(bggameover);
        return -1;
    }
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //CONFIGURAR SAMPLES DE AUDIO
    musicbox1 = al_load_sample("sounds/do.wav");
    musicbox2 = al_load_sample("sounds/re.wav");
    musicbox3 = al_load_sample("sounds/mi.wav");
    musicbox4 = al_load_sample("sounds/fa.wav");
    musicbox5 = al_load_sample("sounds/sol.wav");
    musicbox6 = al_load_sample("sounds/la.wav");
    musicbox7 = al_load_sample("sounds/si.wav");
    musicbox8 = al_load_sample("sounds/do8.wav");
    musicbox9 = al_load_sample("sounds/re8.wav");
    musicbox10 = al_load_sample("sounds/mi8.wav");
    musicbox11= al_load_sample("sounds/fa8.wav");
    musicbox12 = al_load_sample("sounds/sol8.wav");
    musicbox13 = al_load_sample("sounds/la8.wav");
    fail = al_load_sample("sounds/beep.wav");

    bgsoundInstance = al_create_sample_instance(bgsound);
    bggameoverInstance = al_create_sample_instance(bggameover);
    musicboxInstance1 = al_create_sample_instance(musicbox1);
    musicboxInstance2 = al_create_sample_instance(musicbox2);
    musicboxInstance3 = al_create_sample_instance(musicbox3);
    musicboxInstance4 = al_create_sample_instance(musicbox4);
    musicboxInstance5 = al_create_sample_instance(musicbox5);
    musicboxInstance6 = al_create_sample_instance(musicbox6);
    musicboxInstance7 = al_create_sample_instance(musicbox7);
    musicboxInstance8 = al_create_sample_instance(musicbox8);
    musicboxInstance9 = al_create_sample_instance(musicbox9);
    musicboxInstance10 = al_create_sample_instance(musicbox10);
    musicboxInstance11 = al_create_sample_instance(musicbox11);
    musicboxInstance12 = al_create_sample_instance(musicbox12);
    musicboxInstance13 = al_create_sample_instance(musicbox13);
    failInstance = al_create_sample_instance(fail);

    al_set_sample_instance_playmode(bgsoundInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(bggameoverInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(musicboxInstance1, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance2, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance3, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance4, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance5, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance6, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance7, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance8, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance9, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance10, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance11, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance12, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(musicboxInstance13, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(failInstance, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(bgsoundInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(bggameoverInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance1, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance2, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance3, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance4, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance5, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance6, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance7, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance8, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance9, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance10, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance11, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance12, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(musicboxInstance13, al_get_default_mixer());

    //CARREGAR FONTES
    font_24 = al_load_font("casale.ttf", 24, 0);
    font_48 = al_load_font("casale.ttf", 48, 0);
    font_12 = al_load_font("casale.ttf", 12, 0);

    //CARREGAR SPRITES
    LoadSpritesBoxes(caixas);
    LoadSpritesPlayer(&jogador);
    for(i=0; i<NUM_BIRDS; i++)
    {
        passaros[i].sprite0 = al_load_bitmap("sprites/bird0.png");
        passaros[i].sprite1 = al_load_bitmap("sprites/bird1.png");
    }
    background = al_load_bitmap("sprites/background.png");
    foreground = al_load_bitmap("sprites/foreground.png");
    cleff = al_load_bitmap("sprites/cleff.png");
    banda = al_load_bitmap("sprites/banda.png");

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
            case ALLEGRO_KEY_M:
                key[KEY_M] = !key[KEY_M];
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
        else if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            switch(state)
            {
            case MENU:
                al_stop_sample_instance(bggameoverInstance);
                al_play_sample_instance(bgsoundInstance);
                if(key[KEY_SPACE])
                {
                    state = CONFIG;
                    key[KEY_SPACE] = 0;
                }
                if(key[KEY_ENTER])
                {
                    state = INSTR;
                    key[KEY_ENTER] = 0;
                }
                break;

            case CONFIG:
                //(RE)INICIALIZAÇÕES
                InitPlayer(&jogador);
                InitBoxes(caixas);
                InitBirds(passaros, seqCerta);
                numColisoes = 0;
                state = PLAYING;
                break;

            case INSTR:
                InitBirds(passaros, seqCerta);
                al_play_sample_instance(bggameoverInstance);
                if(key[KEY_ENTER])
                {
                    al_stop_sample_instance(bggameoverInstance);
                    state = MENU;
                    key[KEY_ENTER] = 0;
                }
                break;

            case PLAYING:

                al_stop_sample_instance(bgsoundInstance);
                if(key[KEY_M])
                {
                    al_stop_sample_instance(bggameoverInstance);
                }
                else
                {
                    al_play_sample_instance(bggameoverInstance);
                }

                //MOVIMENTAÇÃO DO PLAYER
                if(key[KEY_SPACE])
                {
                    state = MENU;
                    key[KEY_SPACE] = 0;
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
                BoxesUp(caixas, &jogador);

                //CHECAGEM DE COLISÃO
                CheckCollision(&jogador, caixas, &numColisoes, &timerColisao);

                //VIDAS E PONTUAÇÃO
                CheckSequencias(&jogador, seqCerta, &numColisoes, &state, passaros, &score, &scoreBirds);

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
                    al_stop_sample_instance(bggameoverInstance);
                    state = CONFIG;
                    key[KEY_SPACE] = 0;
                }
                 if(key[KEY_ENTER])
                {
                    al_stop_sample_instance(bggameoverInstance);
                    state = MENU;
                    key[KEY_ENTER] = 0;
                }
                break;

            case YOUWIN:
                al_stop_sample_instance(bggameoverInstance);
                al_play_sample_instance(bgsoundInstance);
                if(key[KEY_SPACE])
                {
                    state = CONFIG;
                    key[KEY_SPACE] = 0;
                }
                break;
            }//end of switch
        }//end of TIMER

/*//////////////////////////////PARTE GRAFICA///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            //CORES
            ALLEGRO_COLOR color_bg = al_map_rgb(119, 220, 217);
            //ALLEGRO_COLOR color_green = al_map_rgb(0, 139, 69);
            ALLEGRO_COLOR color_white = al_map_rgb(255, 255, 255);
            ALLEGRO_COLOR color_grey = al_map_rgb(125, 105, 90);

            switch(state)
            {
            case MENU:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(foreground, 0, 0, 0);
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "SHUT THE BIRDS UP!");
                al_draw_text(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, "START GAME [PRESS SPACE]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 400, ALLEGRO_ALIGN_CENTER, "INSTRUCTIONS [PRESS ENTER]");
                al_draw_text(font_24, color_white, SCREEN_W/2, 450, ALLEGRO_ALIGN_CENTER, "QUIT [PRESS ESC]");
                al_draw_text(font_12, color_white, SCREEN_W/2, 180, ALLEGRO_ALIGN_CENTER, "DEVELOPED BY S2");
                al_flip_display();
                break;

            case INSTR:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(foreground, 0, 0, 0);
                DrawBirds(passaros);
                al_draw_bitmap(banda, SCREEN_W*2/5, SCREEN_H/2+45, 0);
                al_draw_filled_rounded_rectangle(70,548, 260, 585, 5, 5, color_grey);
                al_draw_text(font_24, color_white, SCREEN_W/6, 550, ALLEGRO_ALIGN_CENTER, "> BACK [ENTER]");
                //ESCREVER INSTRUÇÕES
                al_draw_textf(font_12, color_white, 80, 360, ALLEGRO_ALIGN_LEFT, "Scott's band is trying to play for some change.");
                al_draw_textf(font_12, color_white, 80, 380, ALLEGRO_ALIGN_LEFT, "But a very annoying group of birds keep singing");
                 al_draw_textf(font_12, color_white, 80, 400, ALLEGRO_ALIGN_LEFT, "right where they were playing.");
                al_draw_textf(font_12, color_white, 80, 420, ALLEGRO_ALIGN_LEFT, "Jump on the boxes in the same order as the bird's");
                al_draw_textf(font_12, color_white, 80, 440, ALLEGRO_ALIGN_LEFT, "positions and help Scott to shut 'em up!");
                al_draw_textf(font_12, color_white, 70, 480, ALLEGRO_ALIGN_LEFT, "Player is controlled with up, right and left arrows.");
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
                DrawBoxes(caixas, &jogador);
                for(i=0; i<3; i++)
                {
                    al_draw_bitmap(jogador.heart_empty, 800+(50*i), 20, 0);
                }
                if(jogador.lifes >=0)
                {
                    for(i=0; i<jogador.lifes; i++)
                    {
                        al_draw_bitmap(jogador.heart_full, 800+(50*i), 20, 0);
                    }

                }
                al_draw_textf(font_24, color_white, SCREEN_W/2, 20, ALLEGRO_ALIGN_CENTER, "YOU: %d   BIRDS: %d", score, scoreBirds);
                al_draw_textf(font_24, color_white, SCREEN_W/10, 20, ALLEGRO_ALIGN_CENTER, "MUTE[M]");
                al_draw_filled_rounded_rectangle(70,548, 260, 585, 5, 5, color_grey);
                al_draw_text(font_24, color_white, SCREEN_W/6, 550, ALLEGRO_ALIGN_CENTER, "> BACK [SPACE]");
                al_draw_filled_rounded_rectangle(SCREEN_W/3-10, 548, 930, 585, 5, 5, color_grey);
                al_draw_text(font_24, color_white, SCREEN_W/3, 550, ALLEGRO_ALIGN_LEFT, "   C=DO   D=RE   E=MI   F=FA   G=SOL   A=LA   B=SI  ");

                /*/DEBUG:
                al_draw_textf(font_24, color_white, 100, 150, ALLEGRO_ALIGN_CENTER, "timerColisao: %d", timerColisao);
                al_draw_textf(font_24, color_white, 100, 200, ALLEGRO_ALIGN_CENTER, "contg: %d", numColisoes);
                al_draw_textf(font_24, color_white, 100, 250, ALLEGRO_ALIGN_CENTER, "player colidiu: %d", jogador.colidiu);
                //al_draw_textf(font_24, color_white, 100, 350, ALLEGRO_ALIGN_CENTER, "timerNotas: %d", timerNotas);
                /*/
                al_flip_display();
                break;

            case GAMEOVER:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                DrawBirds(passaros);
                al_draw_bitmap(foreground, 0, 0, 0);
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "YOU LOSE!");
                al_draw_text(font_24, color_white, SCREEN_W/6, 500, ALLEGRO_ALIGN_CENTER, "> TRY AGAIN [SPACE]");
                al_draw_filled_rounded_rectangle(70,548, 260, 585, 5, 5, color_grey);
                al_draw_text(font_24, color_white, SCREEN_W/6, 550, ALLEGRO_ALIGN_CENTER, "> MENU [ENTER]");
                al_draw_textf(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, " BIRDS %d x %d YOU", scoreBirds, score);
                al_flip_display();
                break;

            case YOUWIN:
                al_clear_to_color(color_bg);
                al_draw_bitmap(background, 0, 0, 0);
                DrawPentagram();
                al_draw_bitmap(cleff,100,90,0);
                al_draw_bitmap(foreground, 0, 0, 0);
                al_draw_bitmap(banda, SCREEN_W*2/5, SCREEN_H/2+45, 0);
                al_draw_text(font_48, color_white, SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_draw_filled_rounded_rectangle(30,548, 300, 585, 5, 5, color_grey);
                al_draw_text(font_24, color_white, SCREEN_W/6, 550, ALLEGRO_ALIGN_CENTER, "> PLAY AGAIN [SPACE]");
                al_draw_textf(font_24, color_white, SCREEN_W/2, 350, ALLEGRO_ALIGN_CENTER, " BIRDS %d x %d YOU", scoreBirds, score);
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
        al_destroy_bitmap(passaros[i].sprite0);
        al_destroy_bitmap(passaros[i].sprite1);
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(foreground);
    al_destroy_bitmap(cleff);
    al_destroy_bitmap(jogador.heart_empty);
    al_destroy_bitmap(jogador.heart_full);
    al_destroy_font(font_24);
    al_destroy_font(font_48);
    al_destroy_font(font_12);
    al_destroy_timer(timer);
    al_destroy_sample(bgsound);
    al_destroy_sample_instance(bgsoundInstance);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(musicbox1);
    al_destroy_sample(musicbox2);
    al_destroy_sample(musicbox3);
    al_destroy_sample(musicbox4);
    al_destroy_sample(musicbox5);
    al_destroy_sample(musicbox6);
    al_destroy_sample(musicbox7);
    al_destroy_sample(musicbox8);
    al_destroy_sample(musicbox9);
    al_destroy_sample(musicbox10);
    al_destroy_sample(musicbox11);
    al_destroy_sample(musicbox12);
    al_destroy_sample(musicbox13);
    al_destroy_sample(fail);

    return 0;
}
