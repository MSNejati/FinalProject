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
    int red,green,blue;
    int apocity;
}star[150];

int make_new_star_line(int total_stars , int screenwidth)
{
    int this_line_stars_count;
    this_line_stars_count = (rand() % 4);
    for(int i = total_stars ; i < total_stars + this_line_stars_count ; i++)
    {
        star[i].x = (rand() % screenwidth - 10) + 5;
        star[i].y = 0;
        star[i].yv = 2;
        star[i].r = 2;
        star[i].blue = 255;
        star[i].red = 200;
        star[i].green = 200;
        star[i].apocity = 255;
    }
    return (total_stars + this_line_stars_count);
}




void stars_y_change(int total_stars)
{
    for(int i = 0 ; i < total_stars ; i++)
    {
        star[i].y += star[i].yv;
    }
}


void draw_stars(SDL_Surface * screen , int total_stars)
{
    for(int i = 0 ; i < total_stars ; i++)
    {
        filledCircleRGBA(screen , star[i].x , star[i].y , star[i].r , star[i].red , star[i].green , star[i].blue , star[i].apocity);
    }
}

int main(int argc ,char * args[])
{
    int screenwidth = 1000;
    int screenhieght = 1000;
    long long int frame = 0;
    long long int last_stars_frame = 0;
    int stars_frame_difference = 5;
    int total_stars = 0;// total number of stars that made till now
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);
    while(true)
    {
        boxRGBA(screen , 0 , 0 , screenwidth , screenhieght , 0 , 0 , 50 , 250);
        if(frame - last_stars_frame == stars_frame_difference)
        {
            total_stars = make_new_star_line(total_stars , screenwidth);
            last_stars_frame = frame;
            stars_frame_difference = (rand() % 10) + 5;
        }
        stars_y_change(total_stars);

        draw_stars(screen , total_stars);

        SDL_Flip(screen);

        frame++;

        SDL_Delay(10);

    }

    SDL_Quit();

    return 0;
}
