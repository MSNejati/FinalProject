#include <iostream>
#include <SDL/SDL.h>


void our_spaceship_v_initialize(float * our_spaceship_right_v , float * our_spaceship_left_v)
{
    Uint8 * keystates1 = SDL_GetKeyState(NULL);
    SDL_Event our_spaceship_move;
    if(SDL_PollEvent(&our_spaceship_move))
    {
	*our_spaceship_right_v = 0;
	*our_spaceship_left_v = 0;
        if(keystates1[SDLK_RIGHT])
        {
                *our_spaceship_right_v += 6;
        }
        if(keystates1[SDLK_LEFT])  
        {
                *our_spaceship_left_v += 6;
        }
    }
}
   
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
