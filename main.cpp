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
}star[80],star2[80];


void first_space_draw(int total_stars2 , int screenheight , int screenwidth)
{
    for(int i = 0 ; i < total_stars2 ; i++)
    {
        star2[i].x = (rand() % screenwidth - 10) + 5;
        star2[i].y = (rand() % screenheight -10);
        star2[i].yv = 2;
        star2[i].r = 1;
        star2[i].blue = 255;
        star2[i].red = 200;
        star2[i].green = 200;
        star2[i].apocity = 255;
        star2[i].ingame = true ;
    }
}

void make_new_star_line(int total_stars2 , int screenwidth)
{
    int this_line_stars_count;
    this_line_stars_count = (rand() % 4);
    for(int j = 0 ; j < this_line_stars_count ; j++)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            if(star2[i].ingame == false)
            {
                star2[i].x = (rand() % screenwidth - 10) + 5;
                star2[i].y = 0;
                star2[i].yv = 2;
                star2[i].r = 1;
                star2[i].blue = 255;
                star2[i].red = 200;
                star2[i].green = 200;
                star2[i].apocity = 255;
                star2[i].ingame = true;
            }
        }
    }
}




void stars_y_change(int total_stars2 , int screenwidth)
{
    for(int i = 0 ; i < 80 ; i++)
    {
        if(star2[i].ingame == true)
        {
            star2[i].y += star[i].yv;
        }
        if(star2[i].y >= screenwidth)
        {
            star2[i].ingame = false;
        }
    }
}


void draw_stars(SDL_Surface * screen , int total_stars2)
{
    for(int i = 0 ; i < total_stars2 ; i++)
    {
        filledCircleRGBA(screen , star2[i].x , star2[i].y , star2[i].r , star2[i].red , star2[i].green , star2[i].blue , star2[i].apocity);
    }
}

int main(int argc ,char * args[])
{
    int screenwidth = 1000;
    int screenhieght = 1000;
    int frame = 0;
    int last_stars_frame = 0;
    int stars_frame_difference = 5;
    int total_stars = 0;// total number of stars that made till now
    int total_stars2 = 80;
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);
    first_space_draw(total_stars2 , screenhieght , screenwidth);
    while(true)
    {
        boxRGBA(screen , 0 , 0 , screenwidth , screenhieght , 0 , 0 , 50 , 250);
        if(frame - last_stars_frame == stars_frame_difference)
        {
            make_new_star_line(total_stars2 , screenwidth);
            last_stars_frame = frame;
            stars_frame_difference = (rand() % 15) + 5;
        }
        stars_y_change(total_stars2 , screenwidth);

        draw_stars(screen , total_stars2);

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
