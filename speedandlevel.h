#include <iostream>
#include "background.h"
#include "sensorsandcollision.h"
#include "sstream"
#include <SDL/SDL_ttf.h>

using namespace std;

void speed_change(int comm ,int * max_enemy_enter_delay)
{
    if(comm == 1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            if(star[i].yv <= 15)
            {
                star[i].yv += 0.5;
            }
        }
        for(int i = 0 ; i < 15 ; i++)
        {
            if(classic_enemies[i].yv <= 16)
            {
                classic_enemies[i].yv += 0.5;
            }
        }
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].y_velocity <= 19)
            {
                enemy_arrow[i].y_velocity += 0.5;
            }
        }
       * max_enemy_enter_delay -= 2;
    }
    if(comm == -1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            if(star[i].yv > 2)
            {
                star[i].yv -= 0.5;
            }
        }
        for(int i = 0 ; i < 15 ; i++)
        {
            if(classic_enemies[i].yv > 3)
            {
                classic_enemies[i].yv -= 0.5;
            }
        }
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].y_velocity > 6)
            {
                enemy_arrow[i].y_velocity -= 0.5;
            }
        }
        *max_enemy_enter_delay += 2;
    }
}

void show_level_num(int level ,int show_level_frame ,SDL_Surface * screen ,float counter)
{
    stringstream level_title_text;
    SDL_Surface * level_title;
    TTF_Font * level_title_font = TTF_OpenFont("level_title.ttf",100);
    int level_apocity;
    int dist_from_center = 250;
    level_apocity = show_level_frame * 10;
    level_title_text << "LEVEL " << level;

    if(level_apocity <= 255)
    {
        SDL_Color level_title_font_color={255,255,255};
        level_title = TTF_RenderText_Solid(level_title_font ,level_title_text.str().c_str() ,level_title_font_color);
        apply_surface(300 + (dist_from_center - 10*show_level_frame )/ counter,150 ,level_title ,screen);
    }
    else
    {
        SDL_Color level_title_font_color={255,255,255};
        level_title = TTF_RenderText_Solid(level_title_font ,level_title_text.str().c_str() ,level_title_font_color);
        apply_surface(300 ,150 ,level_title ,screen);
    }
}



void level_difficulity(int level ,int * max_enemies_count ,int * max_enemies_enter_delay ,string * enemy_type)
{
    if(level <= 1)
    {
        *(max_enemies_count) = level;
        *(max_enemies_enter_delay) -= level*20;
    }
    else
    {
        *(enemy_type) = "enemyspaceship2.png";

    }
}






