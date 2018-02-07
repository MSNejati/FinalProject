#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "speedandlevel.h"

using namespace std;

struct power_up
{
    int x=0;
    int y=0;
    int xv;
    int yv = 2;
    int rad =50;
    bool ingame = false;
}extra_heart[1] ,extra_bullet[1] ,special_ammu[1];

void power_up_drop(int power_up_type)
{
    if(power_up_type == 0)
    {
        extra_heart[0].ingame = true;
        extra_heart[0].x = (rand() % 10) * 100;
        extra_heart[0].y = 0;
    }
    if(power_up_type == 1)
    {
        extra_bullet[0].ingame = true;
        extra_bullet[0].x = (rand() % 10) * 100;
        extra_bullet[0].y = 0;
    }
    if(power_up_type == 2)
    {
        special_ammu[0].ingame = true;
        special_ammu[0].x = (rand() % 10) * 100;
        special_ammu[0].y = 0;
    }
}

void power_up_move_and_show(SDL_Surface * screen)
{
    SDL_Surface * show_power_up;
    if(extra_heart[0].ingame)
    {
         extra_heart[0].y += extra_heart[0].yv;
        filledCircleRGBA(screen ,extra_heart[0].x ,extra_heart[0].y ,extra_heart[0].rad ,0 ,255 ,0 ,255);
        filledCircleRGBA(screen ,extra_heart[0].x ,extra_heart[0].y ,extra_heart[0].rad - 5,0 ,0 ,50 ,255);
    }
    if(extra_bullet[0].ingame)
    {
        extra_bullet[0].y += extra_bullet[0].yv;
        filledCircleRGBA(screen ,extra_bullet[0].x ,extra_bullet[0].y ,extra_bullet[0].rad ,255 ,0 ,0 ,255);
        filledCircleRGBA(screen ,extra_bullet[0].x ,extra_bullet[0].y ,extra_bullet[0].rad - 5,0 ,0 ,50 ,255);
    }
    if(special_ammu[0].ingame)
    {
        special_ammu[0].y += special_ammu[0].yv;
        filledCircleRGBA(screen ,special_ammu[0].x ,special_ammu[0].y ,special_ammu[0].rad ,0 ,0 ,255 ,255);
        filledCircleRGBA(screen ,special_ammu[0].x ,special_ammu[0].y ,special_ammu[0].rad - 5,0 ,0 ,50 ,255);

    }
}

int power_ups_effects()
{
    if(extra_heart[0].ingame)
    {
        for(int i = 0 ; i < 5 ; i++)
        {
            if(our[i].x1 < extra_heart[0].x && our[i].x2 > extra_heart[0].x && our[i].y1 - extra_heart[0].y < extra_heart[0].rad &&  extra_heart[0].y - our[i].y2 < extra_heart[0].rad)
            {
                return 0;
            }
            if( our[i].y1 < extra_heart[0].y && our[i].y2 > extra_heart[0].y && our[i].x1 - extra_heart[0].x < extra_heart[0].rad &&  extra_heart[0].x - our[i].x2 < extra_heart[0].rad)
            {
                return 0;
            }
        }
    }
    if(extra_bullet[0].ingame)
    {
        for(int i = 0 ; i < 5 ; i++)
        {
            if(our[i].x1 < extra_bullet[0].x && our[i].x2 > extra_bullet[0].x && our[i].y1 - extra_bullet[0].y < extra_bullet[0].rad &&  extra_bullet[0].y - our[i].y2 < extra_bullet[0].rad)
            {
                return 1;
            }
            if( our[i].y1 < extra_bullet[0].y && our[i].y2 > extra_bullet[0].y && our[i].x1 - extra_bullet[0].x < extra_bullet[0].rad &&  extra_bullet[0].x - our[i].x2 < extra_bullet[0].rad)
            {
                return 1;
            }
        }
    }
    if(special_ammu[0].ingame)
    {

    }
    return 4;
}







