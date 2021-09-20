#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

#include "def.h"
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

/** KeyboardHandler reads pressed and released keys from SDL_Event, 
 * then stores information about which keys are pressed and which
 * are not */
class KeyboardHandler {
private:
    std::vector<int> pressedKeys;
public:
    /**Read keys from event*/
    void pollKeys(SDL_Event event);
    /**Checks if key pressed*/
    bool isPressed(int key);
    /**Checks if key released*/
    bool isReleased(int key);
};

#endif
