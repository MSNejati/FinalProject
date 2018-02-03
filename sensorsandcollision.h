#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "enemies.h"
#include "throw_arrows.h"

struct sensors
{
    int x1;
    int y1;
    int x2;
    int y2;
    bool ingame = false;
}our[5] ,enemies[15][5] ,boss_s[5];

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
    for (int i = 0 ; i < 15 ; i++)
    {
        if(classic_enemies[i].ingame )
        {
            enemies[i][0].x1 = classic_enemies[i].x + 0;
            enemies[i][0].y1 = classic_enemies[i].y + 20;
            enemies[i][0].x2 = classic_enemies[i].x + 100;
            enemies[i][0].y2 = classic_enemies[i].y + 40;
            enemies[i][0].ingame = true;

            enemies[i][1].x1 = classic_enemies[i].x + 15;
            enemies[i][1].y1 = classic_enemies[i].y + 40;
            enemies[i][1].x2 = classic_enemies[i].x + 80;
            enemies[i][1].y2 = classic_enemies[i].y + 50;
            enemies[i][1].ingame = true;

            enemies[i][2].x1 = classic_enemies[i].x + 25;
            enemies[i][2].y1 = classic_enemies[i].y + 50;
            enemies[i][2].x2 = classic_enemies[i].x + 70;
            enemies[i][2].y2 = classic_enemies[i].y + 60;
            enemies[i][2].ingame = true;

            enemies[i][3].x1 = classic_enemies[i].x + 35;
            enemies[i][3].y1 = classic_enemies[i].y + 60;
            enemies[i][3].x2 = classic_enemies[i].x + 60;
            enemies[i][3].y2 = classic_enemies[i].y + 70;
            enemies[i][3].ingame = true;

            enemies[i][4].x1 = classic_enemies[i].x + 40;
            enemies[i][4].y1 = classic_enemies[i].y + 70;
            enemies[i][4].x2 = classic_enemies[i].x + 55;
            enemies[i][4].y2 = classic_enemies[i].y + 80;
            enemies[i][4].ingame = true;

        }
        if(!classic_enemies[i].ingame)
        {
            for(int j = 0 ; j < 5 ; j++)
            {
                enemies[i][j].ingame = false;
            }
        }
    }
}


int collision(int * score ,bool boss_fight)
{
        for(int i = 0 ; i < 15 ; i++)
        {
            if(classic_enemies[i].ingame)
            {
                for(int j = 0 ; j < 5 ; j++)
                {
                    for(int k = 0 ; k < 100 ; k++)
                    {
                        if(arrow[k].ingame && arrow[k].y > enemies[i][j].y1 && arrow[k].y < enemies[i][j].y2 && arrow[k].x > enemies[i][j].x1 && arrow[k].x < enemies[i][j].x2)
                        {
                            for(int p = 0 ; p < 5 ; p++)
                            {
                                enemies[i][p].ingame = false;
                            }
                            classic_enemies[i].ingame = false;
                            arrow[k].ingame = false;
                            *score += 1;
                            break;
                        }
                    }
                    for(int k = 0 ; k < 5 ; k++)
                    {
                        if(((enemies[i][j].x1 < our[k].x2 && enemies[i][j].x1 > our[k].x1) || (enemies[i][j].x2 < our[k].x2 && enemies[i][j].x2 > our[k].x1)) && ((enemies[i][j].y1 < our[k].y2 && enemies[i][j].y1 > our[k].y1) || (enemies[i][j].y2 < our[k].y2 && enemies[i][j].y2 > our[k].y1)))
                        {
                            classic_enemies[i].ingame = false;
                            return 1;
                        }
                    }
                }
            }
        }
        for(int j = 0 ; j < 5 ; j++)
        {
            for(int k = 0 ; k < 100 ; k++)
            {
                if(enemy_arrow[k].ingame && enemy_arrow[k].y > our[j].y1 && enemy_arrow[k].y < our[j].y2 && enemy_arrow[k].x > our[j].x1 && enemy_arrow[k].x < our[j].x2)
                {
                    enemy_arrow[k].ingame = false;
                    return 1;
                }
            }
        }

    if(boss_fight)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            for(int k = 0 ; k < 100 ; k++)
            {
                if(boss_arrow[k].ingame && boss_arrow[k].y > our[j].y1 && boss_arrow[k].y < our[j].y2 && boss_arrow[k].x > our[j].x1 && boss_arrow[k].x < our[j].x2)
                {
                    boss_arrow[k].ingame = false;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void boss_sensors_position(SDL_Surface * screen)
{
    boss_s[0].x1 = boss[0].x + 10;
    boss_s[0].y1 = boss[0].y + 200;
    boss_s[0].x2 = boss[0].x + 40;
    boss_s[0].y2 = boss[0].y + 80;
    boss_s[0].ingame = true;
    boss_s[1].x1 = boss[0].x + 40;
    boss_s[1].y1 = boss[0].y + 170;
    boss_s[1].x2 = boss[0].x + 60;
    boss_s[1].y2 = boss[0].y + 150;
    boss_s[1].ingame = true;
    boss_s[2].x1 = boss[0].x + 60;
    boss_s[2].y1 = boss[0].y + 200;
    boss_s[2].x2 = boss[0].x + 140;
    boss_s[2].y2 = boss[0].y + 0;
    boss_s[2].ingame = true;
    boss_s[3].x1 = boss[0].x + 140;
    boss_s[3].y1 = boss[0].y + 170;
    boss_s[3].x2 = boss[0].x + 160;
    boss_s[3].y2 = boss[0].y + 150;
    boss_s[3].ingame = true;
    boss_s[4].x1 = boss[0].x + 160;
    boss_s[4].y1 = boss[0].y + 200;
    boss_s[4].x2 = boss[0].x + 190;
    boss_s[4].y2 = boss[0].y + 80;
    boss_s[4].ingame = true;

}



void boss_collision_check()
{
    for(int i = 0 ; i < 5 ; i++)
    {
        for(int k = 0 ; k < 100 ; k++)
        {
            if(arrow[k].ingame && arrow[k].y < boss_s[i].y1 && arrow[k].y > boss_s[i].y2 && arrow[k].x > boss_s[i].x1 && arrow[k].x < boss_s[i].x2)
            {
                cout << 1 << "\n";
                boss[0].hitpoint--;
                arrow[k].ingame = false;
                break;
            }
        }
    }
}




