/*PORQUE TEM ISSO??
    #ifndef OBJECTS_H_INCLUDED
    #define OBJECTS_H_INCLUDED
    #endif // OBJECTS_H_INCLUDED
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_W 1000
#define SCREEN_H 600
#define  FPS 60
#define  gravity 0.5
#define NUM_BOXES 7
#define NUM_BIRDS 5
#define NUM_NOTES 7
#define NENHUMA 24

enum IDS {PLAYER, BIRDS, BOXES};
enum notes {DO, RE, MI, FA, SOL, LA, SI};
enum state_tag {MENU, PLAYING, GAMEOVER, YOUWIN};

//enum posNotes{};

struct PLAYER
{
    int width;
    int height;
    float pos_inicial_x;
    float pos_inicial_y;
    float x;
    float y;
    float dy;
    float move_speed;
    float jump_speed;

    int seqJogador[NUM_BIRDS];
    int lives;

    float bx;
    float by;
    bool colidiu;
    bool is_on_solid_ground;
    bool may_jump;
};

struct BOXES
{
    int width;
    int height;
    float x;
    float y;
    float bx;
    float by;

    int note;
};

struct BIRDS
{
    float x;
    float y;
    float raio;

    int note;
    bool live;
};
