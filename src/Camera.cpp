#include "Camera.h"
#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    
    if (focus != nullptr) {
        pos = {512, 300}; 
    }
    else {
        if (input.IsKeyDown(UP_ARROW_KEY)) {
            speed = {0, -dt*250};
            pos = pos + speed;
        }
        else if (input.IsKeyDown(DOWN_ARROW_KEY)) {
            speed = {0, dt*250};
            pos = pos + speed;
        }
        else if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed = {dt*250, 0};
            pos = pos + speed;
        }
        else if (input.IsKeyDown(LEFT_ARROW_KEY)) {
            speed = {-dt*250, 0};
            pos = pos + speed;
        }
    }
}