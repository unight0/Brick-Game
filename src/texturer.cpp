#include "include/texturer.h"


Texturer::
Texturer(Renderer *renderer, int flags) {
    this->renderer = renderer;
    if(IMG_Init(flags) < 0) {
    	throw IMGError_FailedInitingIMG();
    }
}

Texturer::
~Texturer() {
    for(auto t : allTextures) {
    	destroyTexture(t);
    }
    allTextures.clear();
    allTextures.~vector();
    IMG_Quit();
}

Texture * Texturer::
loadTexture(const char *file) {
    #ifdef DEBUG_SHOW_LOADING_TEXTURE
    std::cout<<"Loading "<<file<<"...";
    #endif
    
    Texture *actualTexture = new Texture;
    SDL_Texture *texture = NULL;
    SDL_Surface *textureSurface = IMG_Load(file);

    if(textureSurface == NULL) {
    	std::cout<<"Could not load "<<file<<"\n|\t"<<SDL_GetError()<<"\n";
        actualTexture->~Texture();
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), textureSurface);

    if(texture == NULL) {
    	std::cout<<"Could not load "<<file<<"\n|\t"<<SDL_GetError()<<"\n";
        actualTexture->~Texture();
        return NULL;
    }

    actualTexture->image = texture;

    allTextures.push_back(actualTexture);
    #ifdef DEBUG_SHOW_LOADING_TEXTURE
    std::cout<<"Loading Succesful"<<std::endl;
    #endif

    if(textureSurface != NULL)
        SDL_FreeSurface(textureSurface);

    return actualTexture;
}

void Texturer::
destroyTexture(Texture *texture) {
    for(auto ptr = allTextures.begin(); ptr < allTextures.end(); ptr++) {
        if(*ptr == texture) allTextures.erase(ptr);
    }
    delete texture;
    texture = NULL;
}
