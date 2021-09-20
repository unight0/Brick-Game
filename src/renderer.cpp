#include "include/renderer.h"
#include <cassert>

SDL_Renderer *Renderer::
getSDLRenderer() {
    return renderer; 
}

bool Renderer::was_created = false;

Renderer::
Renderer(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) !=  0) {
        throw SDLError_FailedInitingSDL();
    }
    if(was_created) throw MoreThenOneRenderer();
    was_created = true;
}

Renderer::
~Renderer(void) {
    closeWindow();
    SDL_Quit();
    was_created = false;
}

void Renderer::
openWindow(const char *name, size_t xsize, size_t ysize, uint32_t wflags, int rflags) {
    renderer = NULL;
    window = NULL;

    windowXSize = xsize;
    windowYSize = ysize;
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            xsize, ysize, wflags);
    
    if(!window) {
        std::cout<<"ERROR: "<<SDL_GetError()<<"\n";
        throw SDLError_CannotCreateWindow();
    }

    renderer = SDL_CreateRenderer(window, -1, rflags);

    if(!renderer) {
        std::cout<<"ERROR: "<<SDL_GetError()<<"\n";
        throw SDLError_CannotCreateRenderer();
    }

    //windowSurface = SDL_GetWindowSurface(window);

    /*if(!windowSurface) {
        std::cout<<"ERROR: "<<SDL_GetError()<<"\n";
        throw SDLError_CannotGetWindowSurface();
    }*/
}

void Renderer::
closeWindow() {
    //assert(renderer != nullptr);
    //assert(windowSurface != nullptr);
    //assert(window != nullptr);
    //if(windowSurface != NULL)
    //    SDL_FreeSurface(windowSurface);
    if(window != NULL)
        SDL_DestroyWindow(window);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    //windowSurface = NULL;
    window = NULL;
    renderer = NULL;
}

void Renderer::
update() {
    SDL_RenderPresent(renderer);
}

void Renderer::
clear(color clr) {
    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
    SDL_RenderClear(renderer);
}

void Renderer::
drawLine(uvec2 point1, uvec2 point2, color clr) {
    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
    SDL_RenderDrawLine(renderer, point1[_x], point1[_y], point2[_x], point2[_y]);
}

/* I don't really know how is this algorithm named */
void Renderer::
drawCircle(uvec2 pos, size_t r, color clr, bool fill) {
    const double stepC = 0.5 / r;
    const double stepR = 0.8;
    const uint64_t x = pos[_x];
    const uint64_t y = pos[_y];


    for(double a = 0; a < M_PI / 2; a += stepC) {
        coord_t xx = sin(a) * r;
        coord_t yy = cos(a) * r;


        drawRect(uvec2({x + xx, y + yy}), uvec2({1, 1}), clr, 1);
        drawRect(uvec2({x - xx, y - yy}), uvec2({1, 1}), clr, 1);
        drawRect(uvec2({x + xx, y - yy}), uvec2({1, 1}), clr, 1);
        drawRect(uvec2({x - xx, y + yy}), uvec2({1, 1}), clr, 1);

        if(fill) {
            for(double rr = 0; rr < r; rr += stepR) {
                xx = sin(a) * rr;
                yy = cos(a) * rr;
                drawRect(uvec2({x + xx, y + yy}), uvec2({1, 1}), clr, 1);
                drawRect(uvec2({x - xx, y - yy}), uvec2({1, 1}), clr, 1);
                drawRect(uvec2({x + xx, y - yy}), uvec2({1, 1}), clr, 1);
                drawRect(uvec2({x - xx, y + yy}), uvec2({1, 1}), clr, 1);
            }    
        }
    }

}

void Renderer::
drawRect(uvec2 pos, uvec2 size, color clr, bool fill) {
    SDL_Rect rect;
    rect.x = pos[_x];
    rect.y = pos[_y];
    rect.h = size[_y];
    rect.w = size[_x]; 

    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
    if(fill) SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

/* I can't really explain this well...
 * But it makes vector follow the line, like this:

            #
           # #
vector -> #   #
         #     #
        #       #
       ###########

            #
           # #
          #   #
vector ->#     #
        #       #
       ###########
       
 * and not like this:

    
            #
           # #
vector -> #   #
         #     #
        #       #
       ###########

            #
           # #
          #   #
vector ---->   #
        #       #
       ###########
*/

static void triangle_makeCloser(fvec2 *what, fvec2 to, float val) {
    float A_x = 1;
    float A_y = 1;
    float A = 0;
    
    //Unreadable code

    if((*what)[_y] > to[_y] && (*what)[_y] - val >= to[_y]) {
        A_y = (*what)[_y] - to[_y];

        (*what)[_y] -= val;
    }
    else if((*what)[_y] < to[_y] && (*what)[_y] + val <= to[_y]) {
        A_y = to[_y] - (*what)[_y];

        (*what)[_y] += val;
    }
    if((*what)[_x] > to[_x]) {
        A_x = (*what)[_x] - to[_x];
        A = A_x/A_y;

        if(((*what)[_x]) - val*A >= to[_x])
            (*what)[_x] -= val * A;
    }
    else if((*what)[_x] < to[_x]) {
        A_x = to[_x] - (*what)[_x];
        A = A_x/A_y;

        if(((*what)[_x]) + val*A <= to[_x])
            (*what)[_x] += val * A;
    }
}

void Renderer::
drawTriangle(uvec2 pos1, uvec2 pos2, uvec2 pos3, color clr, bool fill) {
    drawLine(pos1, pos2, clr);
    drawLine(pos2, pos3, clr);
    drawLine(pos3, pos1, clr);


    if(fill) {
        fvec2 point1 = (fvec2)pos1;
        fvec2 point2 = (fvec2)pos2;
	const fvec2 point3 = (fvec3)pos3;
        
        //FIXME: rectangle is not being filled
        for(; (point1 != point3) || (point2 != point3);) {
            drawLine(point1, point2, clr);
            triangle_makeCloser(&point1, point3, 1);
            triangle_makeCloser(&point2, point3, 1);
        }
    }
}

void Renderer::
drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect) {
    if(texture != NULL) {
        SDL_RenderCopy(renderer, texture, srcRect, destRect);
    }else {
        std::cout<<"Invalid texture"<<std::endl;
    }
}
