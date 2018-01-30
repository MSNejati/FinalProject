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
	int y_velocity; // i don't use it now but maybe we use it later
	bool ingame;
}arrow[100];

int make_arrow_ingame (SDL_Surface *screen, int spaceshipx, int spaceshipy, int arrow_number) {
	for(int i = 0 ; i < 100 ; i++)
	{
        if(arrow[i].ingame == false)
        {
            arrow[i].ingame = true;
            arrow[i].x = spaceshipx + 50;
            arrow[i].y = spaceshipy;
            filledCircleRGBA(screen, arrow[i].x, arrow[i].y, 3, 255, 255, 0, 255);
            //boxRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, arrow[arrow_number].x + 2, arrow[arrow_number].y + 10, 255, 255, 0, 255);
            return arrow_number;
            break;
        }
	}

}

void move_arrow (SDL_Surface *screen) {

	for (int i = 0; i < 100; i++) {
		if (arrow[i].y >= 0 && arrow[i].ingame == true) {
			arrow[i].y = arrow[i].y + velocity;
			filledCircleRGBA(screen, arrow[i].x, arrow[i].y, 3, 255, 255, 0, 255);
            		//boxRGBA(screen, arrow[i].x, arrow[i].y, arrow[i].x + 2, arrow[i].y + 10, 255, 255, 0, 255);
		}
		if (arrow[i].y < -2 && arrow[i].ingame == true)
		{
            arrow[i].ingame = false;
		}
	}

}




