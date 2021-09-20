#include "include/keyboard.h"


void KeyboardHandler::
pollKeys(SDL_Event event) {
    int key = event.key.keysym.sym;
    if(event.type == SDL_KEYDOWN) {
        if(std::find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end()) {
            pressedKeys.push_back(key);
        }
    }
    else if(event.type == SDL_KEYUP) {
        if(std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end()) {
            pressedKeys.erase(std::find(pressedKeys.begin(), pressedKeys.end(), key));
        }
    }
}

bool KeyboardHandler::
isPressed(int key) {
    return (std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end());
}

bool KeyboardHandler::
isReleased(int key) {
    return !isPressed(key);
}
