#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

struct sensors
{
    int x1;
    int y1;
    int x2;
    int y2;
}our[5];

void sensors_position(SDL_Surface * screen ,int our_spaceshipx ,int our_spaceshipy)
{
    our[0].x1 = our_spaceshipx + 40;
    our[0].y1 = our_spaceshipy + 5;
    our[0].x2 = our_spaceshipx + 60;
    our[0].y2 = our_spaceshipy + 20;
    our[1].x1 = our_spaceshipx + 30;
    our[1].y1 = our_spaceshipy + 20;
    our[1].x2 = our_spaceshipx + 70;
    our[1].y2 = our_spaceshipy + 50;
    our[2].x1 = our_spaceshipx + 20;
    our[2].y1 = our_spaceshipy + 50;
    our[2].x2 = our_spaceshipx + 80;
    our[2].y2 = our_spaceshipy + 70;
    our[3].x1 = our_spaceshipx + 0;
    our[3].y1 = our_spaceshipy + 70;
    our[3].x2 = our_spaceshipx + 100;
    our[3].y2 = our_spaceshipy + 90;
    our[4].x1 = our_spaceshipx + 40;
    our[4].y1 = our_spaceshipy + 90;
    our[4].x2 = our_spaceshipx + 60;
    our[4].y2 = our_spaceshipy + 100;
}
