#include "objects.h"

void InitBoxes(struct BOXES boxes[])
{
    int i, j = 2;
    for(i = 0; i < NUM_BOXES; i++)
    {
        boxes[i].width = SCREEN_W/17;
        boxes[i].height = SCREEN_H/12;
        boxes[i].x = SCREEN_W*j/17; // posição em x da caixa
        boxes[i].y = SCREEN_H/2;
        boxes[i].note = i;
        j += 2;
    }
}

