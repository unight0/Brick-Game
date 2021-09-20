#ifndef INCLUDE_TEXTURE_H
#define INCLUDE_TEXTURE_H

#include "def.h"
#include <SDL2/SDL.h>

/* This class stores SDL_Texture and source rect of this texture */
struct Texture {
    SDL_Texture *image;
    SDL_Rect *sourceRect;
    Texture();
    ~Texture();
    void setSrcRect(coord_t x, coord_t y, size_t w, size_t h);
    bool operator==(Texture texture);
};

#endif
