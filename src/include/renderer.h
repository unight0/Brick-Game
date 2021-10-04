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

    /** Draw line from point1 to point2 
      * @param uvec2 point1 -- first point
      * @param uvec2 point2 -- second point */
    void drawLine(uvec2 point1, uvec2 point2, color clr);

    /** Draw circle at pos with given radius
      * @param uvec2 pos -- pos to draw circle at
      * @param size_t r -- radius of circle
      * @param color clr -- color of circle
      * @param bool fill -- fill the circle or not */
    void drawCircle(uvec2 pos, size_t r, color clr, bool fill);

    /** Draw rectangle at pos with given size
      * @param uvec2 pos -- pos to draw
      * @param uvec2 size -- rectangle size
      * @param color clr -- rectangle color
      * @param bool fill -- fill rectangle or not */
    void drawRect(uvec2 pos, uvec2 size, color clr, bool fill);

    /** Draw Triangle using 3 points
      * @param uvec2 point1 -- first point
      * @param uvec2 point2 -- second point
      * @param uvec2 point3 -- third point
      * @param color clr -- triangle color
      * @param bool fill -- fill triangle or not*/
    void drawTriangle(uvec2 point1, uvec2 point2, uvec2 point3, color clr, bool fill);

    /** Draw Texture. See SDL_RenderCopy() at SLD2's wiki
      * @param SDL_Texture *texture -- texture to draw
      * @param SDL_Rect *srcRect -- source rectangle of image
      * @param SDL_Rect *destRect -- destination rectangle */
    void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect);
    
    /** Returns SDL_Renderer* */
    SDL_Renderer *getSDLRenderer();
};

#endif
