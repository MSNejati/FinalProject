#include <iostream>
#include <SDL/SDL.h>


void our_spaceship_v_initialize(float * our_spaceship_right_v , float * our_spaceship_left_v)
{
    Uint8 * keystates = SDL_GetKeyState(NULL);
    SDL_Event our_spaceship_move;
    if(SDL_PollEvent(&our_spaceship_move))
    {
	*our_spaceship_right_v = 0;
	*our_spaceship_left_v = 0;
        if(keystates[SDLK_RIGHT] /* *(our_spaceship_right_v) <= 5*/)
        {
            //if( *(our_spaceship_left_v) > 0 )
            //{
            //    *our_spaceship_left_v = 0;
            //}
            //else
            //{
                *our_spaceship_right_v += 2;
            //}
        }
        if(keystates[SDLK_LEFT]  /* *(our_spaceship_left_v) <= 5*/)
        {
            //if(*(our_spaceship_right_v) > 0)
            //{
            //    *our_spaceship_right_v = 0;
            //}
            //else
            //{
            	*our_spaceship_left_v += 2;
            //}
        }
    }
}
    /*else
    {
         if(*(our_spaceship_left_v) >= 1)
            {
                *our_spaceship_left_v -= 1;
            }
            else
            {
               *our_spaceship_left_v = 0;
            }
            if(*(our_spaceship_right_v) >= 1)
            {
                *our_spaceship_right_v -= 1;
            }
            else
            {
               *our_spaceship_right_v = 0;
            }
    }*/



void our_spaceship_move (int * our_spaceshipx ,float * our_spaceship_right_v, float * our_spaceship_left_v ,int screenwidth ,int screenheight)
{
    if(*our_spaceshipx < screenwidth - 100)
    {
        *(our_spaceshipx) += *(our_spaceship_right_v);
    }
    if(*our_spaceshipx > 0)
    {
        *(our_spaceshipx) -= *(our_spaceship_left_v);
    }
}
