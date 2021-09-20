#ifndef INCLUDE_TEXTURER_H
#define INCLUDE_TEXTURER_H

#include "def.h"
#include "renderer.h"
#include "texture.h"
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/** This class loads initializates IMG, loads textures, destroys textures */
class Texturer {
	Renderer *renderer;
	std::vector<Texture*> allTextures;
public:
	class IMGError_FailedInitingIMG{};
	Texturer(Renderer *renderer, int flags);
	~Texturer();
	Texture *loadTexture(const char *file);
	void destroyTexture(Texture *texture);
};

#endif
