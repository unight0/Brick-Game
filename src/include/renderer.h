#ifndef INCLUDE_RENDERER_H
#define INCLUDE_RENDERER_H

#include "def.h"
#include "vec.h"
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/** This is quite a big class. It creates initializes SDL, creates window, 
 * draws different shapes, draws texture, updates renderer, etc */
class Renderer {
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    //SDL_Surface *windowSurface;
    uint64_t windowXSize;
    uint64_t windowYSize;

    static bool was_created;
public:
    class SDLError_CannotCreateWindow{};
    class SDLError_CannotCreateRenderer{};
    class SDLError_FailedInitingSDL{};
    class MoreThenOneRenderer{};

    /**Attention! Only one Renderer should be created!*/
    Renderer(void);
    ~Renderer(void);
    void openWindow(const char *name,
        size_t xsize,
        size_t ysize,
        uint32_t wflags,
        int rflags);
    void closeWindow(void);
    void update();
    void clear(color clr);
    /**Draw line from point1 to point2*/
    void drawLine(uvec2 point1, uvec2 point2, color clr);
    /**Draw circle at @param pos with radius = @param r*/
    void drawCircle(uvec2 pos, size_t r, color clr, bool fill);
    /**Draw rectangle at @param pos with @param size size*/
    void drawRect(uvec2 pos, uvec2 size, color clr, bool fill);
    /**Draw Triangle with 3 points = {@param point1, @param point2, @param point3}*/
    void drawTriangle(uvec2 point1, uvec2 point2, uvec2 point3, color clr, bool fill);
    /**Draw Texture. See SDL_RenderCopy() at SLD2's wiki*/
    void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect);
    SDL_Renderer *getSDLRenderer();
};

#endif
