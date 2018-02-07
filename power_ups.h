#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct power_up
{
    int x;
    int y;
    int xv;
    int yv = 2;
    bool ingame;
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
         show_power_up = load_image("heart.png");
         apply_surface(extra_heart[0].x ,extra_heart[0].y ,show_power_up ,screen);
    }
    if(extra_bullet[0].ingame)
    {
        extra_bullet[0].y += extra_bullet[0].yv;
        show_power_up = load_image("heart.png");
        apply_surface(extra_heart[0].x ,extra_heart[0].y ,show_power_up ,screen);
    }
    if(special_ammu[0].ingame)
    {
        special_ammu[0].y += special_ammu[0].yv;
        show_power_up = load_image("heart.png");
        apply_surface(extra_heart[0].x ,extra_heart[0].y ,show_power_up ,screen);
    }
}

void special_ammu_drop()
