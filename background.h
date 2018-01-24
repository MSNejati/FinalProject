#include <cstdlib>
#include <ctime>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

struct things {
    int x;
    int y;
    int r;//radiance
    bool ingame;
    int xv;//x's velocity
    int yv;//y's velocity
    int red, green, blue;
    int apocity;
} star[80];

void first_space_draw(int total_stars, int screenheight, int screenwidth) {
    for (int i = 0; i < total_stars; i++) {
        star[i].x = (rand() % screenwidth - 10) + 5;
        star[i].y = (rand() % screenheight - 10);
        star[i].yv = 2;
        star[i].r = 1;
        star[i].blue = 255;
        star[i].red = 200;
        star[i].green = 200;
        star[i].apocity = 255;
        star[i].ingame = true;
    }
}

void make_new_star_line(int total_stars, int screenwidth) {
    int this_line_stars_count;
    this_line_stars_count = (rand() % 4);
    for (int j = 0; j < this_line_stars_count; j++) {
        for (int i = 0; i < total_stars; i++) {
            if (star[i].ingame == false) {
                star[i].x = (rand() % screenwidth - 10) + 5;
                star[i].y = 0;
                star[i].yv = 2;
                star[i].r = 1;
                star[i].blue = 255;
                star[i].red = 200;
                star[i].green = 200;
                star[i].apocity = 255;
                star[i].ingame = true;
            }
        }
    }
}

void stars_y_change(int total_stars, int screenwidth, int screenheight) {
    for (int i = 0; i < 80; i++) {
        if (star[i].ingame == true) {
            star[i].y += star[i].yv;
        }
        if (star[i].y >= screenheight) {
            star[i].ingame = false;
        }
    }
}


void draw_stars(SDL_Surface *screen, int total_stars) {
    for (int i = 0; i < total_stars; i++) {
        filledCircleRGBA(screen, star[i].x, star[i].y, star[i].r, star[i].red, star[i].green, star[i].blue,
                         star[i].apocity);
    }
}