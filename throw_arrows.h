#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

using namespace std;

int new_arrows = 0; // arrows that player gets in game
int velocity = -6;
int arrow_delay = 0;

struct shot {
	int x;
	int y;
	int y_velocity;
	bool ingame;
}arrow[1000];

int make_arrow_ingame (SDL_Surface *screen, int spaceshipx, int spaceshipy, int arrow_number )
{

	for(int i = 0 ; i < 1000 ; i++)
	{
       		if(arrow[i].ingame == false)
        	{
            		arrow[i].ingame = true;
            		arrow[i].x = spaceshipx + 50;
            		arrow[i].y = spaceshipy;
            		return arrow_number;
            		break;
        	}
	}

}

void move_arrow (SDL_Surface *screen) {

	for (int i = 0; i < 1000; i++) {
		if (arrow[i].y >= 0 && arrow[i].ingame == true) {
			arrow[i].y = arrow[i].y + velocity;
            		boxRGBA(screen, arrow[i].x, arrow[i].y, arrow[i].x + 3, arrow[i].y + 10, 255, 130, 0, 255);
		}
		if (arrow[i].y < -2 && arrow[i].ingame == true)
		{
            		arrow[i].ingame = false;
		}
	}

}




