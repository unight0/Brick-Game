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
	1.0, 0.05, 10000, 1000, 10);
    
    renderer.openWindow("Brick Game", (10 * brick_size + 8 * brick_size),
	 21 * brick_size, 0, 0);
    
    bglg.start();
    
    bool game_over = false;
    
    while(!game_over) { 
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
            if(bglg.is_game_over()) {
                game_over = true;
            }
            else {
			    bglg.tick();	
            }
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
    /* Game over */
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, "Game over!", {255, 255, 255, 255});
    if(text_surface == NULL) {
        printf("Error creating surface from text: %s\n", TTF_GetError());
        printf("Anyway, it is Game Over! Try again :)\n");
        exit(-1);
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer.getSDLRenderer(), text_surface);
    if(text_texture == NULL) {
        printf("Error creating texture from surface: %s\n", SDL_GetError());
        printf("Anyway, it is Game Over! Try again :)\n");
        exit(-1);
    }
    renderer.clear(clr_black);
    renderer.update();
    SDL_Rect dest_rect = {0, 0, 0, 0};
    dest_rect.w = text_surface->w;
    dest_rect.h = text_surface->h;
    renderer.drawTexture(text_texture, NULL, &dest_rect);
    renderer.update();

    /* Wait until key recieved */
    SDL_Event event;
    bool wait_key = true;
    while(wait_key) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_KEYDOWN)
                wait_key = false;
        }
    }
    
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);

	renderer.closeWindow();
	TTF_CloseFont(font);
	exit(0);
}
