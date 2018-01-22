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

int main(int argc ,char * args[])
{
    int screenwidth;
    int screenhieght;
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);

    return 0;
}
