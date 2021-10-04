#include "include/def.h"
#include "include/renderer.h"
#include "include/keyboard.h"
#include "include/bglg.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>



int main() {
    Renderer renderer;
    KeyboardHandler kbdhandl;
	
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("font.ttf", 32);
	
	const uint64_t brick_size = 32;

    BrickGameLG bglg(&renderer, font,
	&kbdhandl, brick_size, {8 * brick_size, 0}, {10, 21},
	1.0, 0.05, 10000, 1000);
    
    renderer.openWindow("Brick Game", (10 * brick_size + 8 * brick_size),
	 21 * brick_size, 0, 0);
    
    bglg.start();
    
    
    while(true) { 
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                renderer.closeWindow();
				TTF_CloseFont(font);
                exit(0);
            }
            else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                kbdhandl.pollKeys(event);
				if((kbdhandl.isPressed(SDLK_LSHIFT) 
					|| kbdhandl.isPressed(SDLK_RSHIFT))
					&& kbdhandl.isPressed(SDLK_c)) {
					renderer.closeWindow();
					TTF_CloseFont(font);
					exit(0);
				}
            }
        }
        

		if(bglg.should_tick()) {
			bglg.tick();	
        }
        else {
            bglg.handle_input();
        }

		bglg.update();
        
		renderer.update();
		renderer.clear(clr_black);
        

		//frames per second 
		SDL_Delay(1000/60);
    }
}
