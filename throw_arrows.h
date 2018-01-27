#include <cstdlib>
#include <ctime>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

int total_arrows = 500; // arrows that player has in the beginning
int new_arrows = 0; // arrows that player gets in game
int velocity = -2;

struct shot {
	int x;
	int y;
	int y_velocity; // i don't use it now but maybe we use it later
	bool ingame;
}arrow[100000];

void make_arrow_ingame (SDL_Surface *screen, int spaceshipx, int spaceshipy, int arrow_number ) {

        arrow[arrow_number].ingame = true;
        arrow[arrow_number].x = spaceshipx + 50;
        arrow[arrow_number].y = spaceshipy;
        //filledCircleRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, 5, 255, 200, 200, 255);
        lineRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, arrow[arrow_number].x, arrow[arrow_number].y + 4, 255, 255, 255, 255);
    //filledCircleRGBA(screen, arrow[arrow_number].x, arrow[arrow_number].y, 5, 255, 200, 200, 255);

}

void move_arrow (SDL_Surface *screen, int arrow_number) {

	for (int i = 0; i < arrow_number; i++) {
		if (arrow[i].y >= 0, arrow[i].ingame == true) {
			arrow[i].y = arrow[i].y + velocity;
			//filledCircleRGBA(screen, arrow[i].x, arrow[i].y, 5, 255, 200, 200, 255);
            lineRGBA(screen, arrow[i].x, arrow[i].y, arrow[i].x, arrow[i].y + 4, 255, 255, 255, 255);
		}
	}

}



