#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

InputManager::InputManager() : 
    mouseState({false, false, false, false, false}),
    mouseUpdate({0, 0, 0, 0, 0, 0}),
    quitRequested(false),
    updateCounter(0),
    mouseX(0),
    mouseY(0) {}

InputManager::~InputManager() {}

void InputManager::Update() {
    quitRequested = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Event event;
    
    updateCounter++;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && !event.key.repeat) {
            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        } 
        else if (event.type == SDL_KEYUP) {
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        } 
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
        } 
        else if (event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
        } 
        else if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (updateCounter == keyUpdate[key] && keyState[key]);    
}

bool InputManager::KeyRelease(int key) {
    return (updateCounter == keyUpdate[key] && !keyState[key]);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return (updateCounter == mouseUpdate[button] && mouseState[button]);    
}

bool InputManager::MouseRelease(int button) {
    return (updateCounter == mouseUpdate[button] && !mouseState[button]);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

bool InputManager::QuitRequested() const {
    return quitRequested;
}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}