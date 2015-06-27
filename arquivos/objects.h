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

//enum posNotes{};

struct PLAYER
{
    int ID;
    int width;
    int height;
    int lives;
    bool colidiu;
    float pos_inicial_x;
    float pos_inicial_y;
    float x;
    float y;
    float dy;
    float bound_x;
    float bound_y;
    float move_speed;
    float jump_speed;
    bool is_on_solid_ground;
    bool may_jump;
    int seqJogador[NUM_BIRDS];
};

struct BOXES
{
    int ID;
    int note;
    int width;
    int height;
    float x;
    float y;
    float bound_x;
    float bound_y;

};

struct BIRDS
{
    int ID;
    int note;
    float x;
    float y;
    float raio;
    float explosion;
};
