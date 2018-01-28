#include <cstdlib>
#include <ctime>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

int new_arrows = 0; // arrows that player gets in game
int velocity = -4;
int arrow_delay = 0;

struct shot {
	int x;
	int y;
	int y_velocity; // i don't use it now but maybe we use it later
	bool ingame;
}arrow[100000];


int make_arrow_ingame (SDL_Surface *screen, int spaceshipx, int spaceshipy, int arrow_number, int *our_spaceship_bullet) {

	Uint8 *keystates = SDL_GetKeyState( NULL );
	if (keystates[SDLK_SPACE]) 
	{
		if(arrow_delay % 10 == 0)
       		{
			arrow[arrow_number].ingame = true;
       			arrow[arrow_number].x = spaceshipx + 50;
      			arrow[arrow_number].y = spaceshipy;
      			//filledCircleRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, 3, 255, 255, 0, 255);
       			boxRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, arrow[arrow_number].x + 2, arrow[arrow_number].y + 10, 255, 255, 0, 255);
			arrow_number++;
			arrow_delay = 1;
			*our_spaceship_bullet--;
		
		}
		else
		{
            		arrow_delay++;
		}		
	}

	return arrow_number;
}


void move_arrow (SDL_Surface *screen, int arrow_number) {

	for (int i = 0; i < arrow_number; i++) {
		if (arrow[i].y >= 0, arrow[i].ingame == true) {
			arrow[i].y = arrow[i].y + velocity;
			//filledCircleRGBA(screen, arrow[i].x, arrow[i].y, 3, 255, 255, 0, 255);
            		boxRGBA(screen, arrow[i].x, arrow[i].y, arrow[i].x + 2, arrow[i].y + 10, 255, 255, 0, 255);
		}
	}

}


        	

