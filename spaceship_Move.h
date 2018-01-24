#include <SDL/SDL.h>


void our_spaceship_v_initialize(float * our_spaceship_right_v , float * our_spaceship_left_v)
{
    Uint8 * keystates = SDL_GetKeyState(NULL);
    SDL_Event our_spaceship_move;
    if(SDL_PollEvent(&our_spaceship_move))
    {
        if(keystates[SDLK_RIGHT] && *(our_spaceship_right_v) <= 5)
        {
            *our_spaceship_right_v += 1;
        }
        if(keystates[SDLK_LEFT] && *(our_spaceship_left_v) <= 5)
        {
                *our_spaceship_left_v += 1;
        }
    }
    else
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
    }
}


void our_spaceship_move (int * our_spaceshipx ,float * our_spaceship_right_v, float * our_spaceship_left_v)
{

    *(our_spaceshipx) += *(our_spaceship_right_v);
    *(our_spaceshipx) -= *(our_spaceship_left_v);

}
