#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>

using namespace std;

struct things
{
    int x;
    int y;
    int r;//radiance
    bool ingame;
    int xv;//x's velocity
    int yv;//y's velocity
}stars[100];

int main(int argc ,char * args[])
{
    int screenwidth;
    int screenhieght;
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);
    while(true)
    {
        boxRGBA(screen , 0 , 0 , screenwidth , screenhieght , 0 , 0 , 100 , 250);

    }

    return 0;
}
