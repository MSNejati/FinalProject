#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>

// load and optimize image
SDL_Surface* load_image( std::string filename ) { 

    SDL_Surface* loadedImage = NULL; 
    SDL_Surface* optimizedImage = NULL; 
    loadedImage = IMG_Load( filename.c_str() ); 
    optimizedImage = SDL_DisplayFormat( loadedImage ); 
    SDL_FreeSurface( loadedImage ); 
    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 255 );
    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    return optimizedImage; 

}
//apply surface to the screen
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) { 
    
    SDL_Rect offset; 
    offset.x = x; 
    offset.y = y; 
    SDL_BlitSurface( source, NULL, destination, &offset );

}

