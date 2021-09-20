#include "include/def.h"
#include "include/renderer.h"
#include "include/texturer.h"
#include "include/keyboard.h"
#include "include/bglg.h"
#include <iostream>



int main() {
    Renderer renderer;
    Texturer texturer(&renderer, IMG_INIT_PNG);
    KeyboardHandler kbdhandl;
    BrickGameLG bglg(&renderer, &kbdhandl, 32, {0, 0}, {10, 21}, std::chrono::duration<double>(1.0));
    
    renderer.openWindow("Brick Game", 320, 672, 0, 0);

    
    bglg.start();

    
    
    while(true) { 
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                renderer.closeWindow();
                exit(0);
            }
            else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                kbdhandl.pollKeys(event);
				if(kbdhandl.isPressed(SDLK_LSHIFT) && kbdhandl.isPressed(SDLK_c)) {
		    		renderer.closeWindow();
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
