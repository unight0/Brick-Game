#include "include/texture.h"


Texture::
Texture() {
    image = NULL;
    sourceRect = new SDL_Rect;
}
void Texture::
setSrcRect(coord_t x, coord_t y, size_t w, size_t h) {
    sourceRect->x = x;
    sourceRect->y = y;
    sourceRect->w = w;
    sourceRect->h = h;
}

Texture::
~Texture() {
    if(sourceRect != NULL)
        delete sourceRect; 

    if(image != NULL)
        SDL_DestroyTexture(image);

    sourceRect = NULL;
    image = NULL;
}

bool Texture::
operator==(Texture texture) {
    return ((sourceRect == texture.sourceRect) && (image == texture.image));
}
