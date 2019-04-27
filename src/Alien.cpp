#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL
#include "SDL_include.h"

Alien::Alien(GameObject& associated, int nMinions) : 
    Component(associated), 
    speed({0, 0}), 
    hp(50), 
    taskQueue(), 
    minionArray() {
    
    std::shared_ptr<Sprite> sprite(new Sprite(associated, "assets/img/alien.png"));
    associated.AddComponent(sprite);
    associated.box.x = sprite->GetWidth();
    associated.box.y = sprite->GetHeight();
}

Alien::~Alien() {
    minionArray.clear();
}

void Alien::Start() {}

void Alien::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 center;            
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
            speed.x = dt*50;
            speed.y = dt*50;
            if (abs(center.x - action.pos.x) < speed.x || abs(center.y - action.pos.y) < speed.y) {
                associated.box.x += speed.x;
                associated.box.y += speed.y; 
            }
            else {
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