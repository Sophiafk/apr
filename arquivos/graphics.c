#include "objects.h"

void DrawPentagram()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        al_draw_line(0,((SCREEN_H/6)+(SCREEN_H/30)*i),SCREEN_W,((SCREEN_H/6)+(SCREEN_H/30)*i),al_map_rgb(0,0,0),2);
    }
}
