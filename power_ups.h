#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "speedandlevel.h"
#include "sstream"

using namespace std;

struct power_up
{
    int x=0;
    int y=0;
    int xv;
    float yv = 2;
    int rad =50;
    bool ingame = false;
    bool activated = false;
}extra_heart[1] ,extra_bullet[1] ,special_ammu[1];

void power_up_drop(int power_up_type)
{
    if(power_up_type == 0)
    {
        extra_heart[0].ingame = true;
        extra_heart[0].x = ((rand() % 9) + 1) * 100;
        extra_heart[0].y = 0;
    }
    if(power_up_type == 1)
    {
        extra_bullet[0].ingame = true;
        extra_bullet[0].x = ((rand() % 9) + 1) * 100;
        extra_bullet[0].y = 0;
    }
    if(power_up_type == 2)
    {
        special_ammu[0].ingame = true;
        special_ammu[0].x = ((rand() % 9) + 1) * 100;
        special_ammu[0].y = 0;
    }
}

void power_up_move_and_show(SDL_Surface * screen)
{
    SDL_Surface * show_power_up;
    SDL_Surface *powerup_heart = load_image("powerup_heart.png");
    SDL_Surface *powerup_laser = load_image("powerup_laser.png");
    SDL_Surface *powerup_bullet = load_image("powerup_bullet.png");
    if(extra_heart[0].ingame)
    {
        extra_heart[0].y += extra_heart[0].yv;
        filledCircleRGBA(screen ,extra_heart[0].x ,extra_heart[0].y ,extra_heart[0].rad ,0 ,255 ,0 ,255);
        filledCircleRGBA(screen ,extra_heart[0].x ,extra_heart[0].y ,extra_heart[0].rad - 5,0 ,0 ,50 ,255);
	apply_surface(extra_heart[0].x - 36 ,extra_heart[0].y - 32, powerup_heart, screen);
    }
    if(extra_bullet[0].ingame)
    {
        extra_bullet[0].y += extra_bullet[0].yv;
        filledCircleRGBA(screen ,extra_bullet[0].x ,extra_bullet[0].y ,extra_bullet[0].rad ,255 ,0 ,0 ,255);
        filledCircleRGBA(screen ,extra_bullet[0].x ,extra_bullet[0].y ,extra_bullet[0].rad - 5,0 ,0 ,50 ,255);
	apply_surface(extra_bullet[0].x - 35 ,extra_bullet[0].y - 35, powerup_bullet, screen);
    }
    if(special_ammu[0].ingame)
    {
        special_ammu[0].y += special_ammu[0].yv;
        filledCircleRGBA(screen ,special_ammu[0].x ,special_ammu[0].y ,special_ammu[0].rad ,0 ,0 ,255 ,255);
        filledCircleRGBA(screen ,special_ammu[0].x ,special_ammu[0].y ,special_ammu[0].rad - 5,0 ,0 ,50 ,255);
	apply_surface(special_ammu[0].x - 31 ,special_ammu[0].y - 33, powerup_laser, screen);

    }
}

int catch_power_ups()
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
        for(int i = 0 ; i < 5 ; i++)
        {
            if(our[i].x1 < special_ammu[0].x && our[i].x2 > special_ammu[0].x && our[i].y1 - special_ammu[0].y < special_ammu[0].rad &&  special_ammu[0].y - our[i].y2 < special_ammu[0].rad)
            {
                special_ammu[0].activated = true;
                special_ammu[0].ingame = false;
            }
            if( our[i].y1 < special_ammu[0].y && our[i].y2 > special_ammu[0].y && our[i].x1 - special_ammu[0].x < special_ammu[0].rad &&  special_ammu[0].x - our[i].x2 < special_ammu[0].rad)
            {
                special_ammu[0].activated = true;
                special_ammu[0].ingame = false;
            }
        }
    }
    return 4;
}


void special_ammu_effect(SDL_Surface * screen ,int our_spaceship_x ,int our_spaceship_y ,bool boss_fight)
{
    for(int i = 0 ; i < 15 ; i++)
    {
        if(classic_enemies[i].ingame)
        {
            lineRGBA(screen ,our_spaceship_x + 50,our_spaceship_y ,classic_enemies[i].x + 50 ,classic_enemies[i].y + 50 ,255 ,255 ,255 ,255);
            classic_enemies[i].hitpoint--;
            if(classic_enemies[i].hitpoint == 0)
            {
                for(int p = 0 ; p < 5 ; p++)
                {
                    enemies[i][p].ingame = false;
                }
                classic_enemies[i].ingame = false;
                classic_enemies[i].explosion_counter++;
            }
        }
    }
    if(boss_fight)
    {
        lineRGBA(screen ,our_spaceship_x + 50,our_spaceship_y ,boss[0].x + 100 ,boss[0].y + 100 ,255 ,255 ,255 ,255);
        boss[0].hitpoint -= 20;
    }
}



void special_ammu_notice(SDL_Surface * screen)
{
    stringstream S_A_notice;
    SDL_Surface * special_ammu_notice;
    TTF_Font * SAN_font = TTF_OpenFont("level_title.ttf",20);
    S_A_notice << "LASER ACTIVATED";
    SDL_Color SAN_font_color = {255,255,255};
    special_ammu_notice = TTF_RenderText_Solid(SAN_font ,S_A_notice.str().c_str() ,SAN_font_color);
    apply_surface(20 ,80 ,special_ammu_notice ,screen);
}






