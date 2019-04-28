#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>

Alien::Alien(GameObject& associated, int nMinions) : 
    Component(associated), 
    speed({0, 0}), 
    hp(50), 
    taskQueue(), 
    minionArray(nMinions) {
    
    std::shared_ptr<Sprite> sprite(new Sprite(associated, "assets/img/alien.png"));
    associated.AddComponent(sprite);
    associated.box.x = sprite->GetWidth()/2;
    associated.box.y = sprite->GetHeight()/2;
}

Alien::~Alien() {
    minionArray.clear();
}

void Alien::Start() {}

void Alien::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 center;
    double angle;
    int dirx = 0, diry = 0;

    if (input.IsMouseDown(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::ActionType::SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
    }
    else if (input.IsMouseDown(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::ActionType::MOVE, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
    }

    if (!taskQueue.empty()) {
        Action action = taskQueue.front();

        if (action.type == Action::ActionType::MOVE) {
            center = associated.box.Center();
            angle = atan2((action.pos.y - center.y), (action.pos.x - center.x));
            speed.x = dt*100 * cos(angle);
            speed.y = dt*100 * sin(angle);
            if (sqrt(pow(action.pos.x - center.x, 2) + pow(action.pos.y - center.y, 2)) > dt*100) {
                associated.box.x += speed.x;
                associated.box.y += speed.y;
            }
            else {
                // associated.box.x = action.pos.x - associated.box.w/2;
                // associated.box.y = action.pos.y - associated.box.h/2; 
                taskQueue.pop();
            }
        }
        else if (action.type == Action::ActionType::SHOOT) {
            taskQueue.pop();
        }

    }
}

void Alien::Render() {}

bool Alien::Is(const std::string& type) const {
    return (type == "Alien");
}

Alien::Action::Action(ActionType type, float x, float y) : 
    type(type),
    pos(x, y) {}