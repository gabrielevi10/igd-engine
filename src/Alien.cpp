#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include "Game.h"
#include "Minion.h"
#include "Helpers.h"
#include "Bullet.h"
#include "Collider.h"

#include <iostream>

#define ALIEN_IMG "assets/img/alien.png"
#define PI 3.14159265359

Alien::Alien(GameObject& associated, int nMinions) : 
    Component(associated), 
    speed({0, 0}), 
    hp(50),
    nMinions(nMinions), 
    taskQueue() {
    
    std::shared_ptr<Sprite> sprite(new Sprite(associated, ALIEN_IMG));
    associated.AddComponent(sprite);
    associated.box.x = sprite->GetWidth()/2;
    associated.box.y = sprite->GetHeight()/2;

    std::shared_ptr<Collider> collider(new Collider(associated));
    associated.AddComponent(collider);
}

Alien::~Alien() {
    minionArray.clear();
}

void Alien::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 center;
    double angle, distance = 99999.9;
    int random, index;
    std::shared_ptr<Minion> minion;

    if (hp <= 0) {
        associated.RequestDelete();
        return;
    }
    associated.angleDeg += -1;
    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        // taskQueue.push(Action(Action::ActionType::SHOOT, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
    }
    else if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::ActionType::MOVE, input.GetMouseX() - Camera::pos.x, input.GetMouseY() - Camera::pos.y));
    }

    if (!taskQueue.empty()) {
        Action action = taskQueue.front();
        if (action.type == Action::ActionType::MOVE) {
            center = associated.box.Center();
            angle = Helpers::AngleBetweenTwoPoints(Vec2(center.x, center.y), Vec2(action.pos.x, action.pos.y));
            speed.x = dt*100 * cos(angle);
            speed.y = dt*100 * sin(angle);
            if (Helpers::EuclideanDistance(Vec2(action.pos.x, action.pos.y), Vec2(center.x, center.y)) > dt*100) {
                associated.box.x += speed.x;
                associated.box.y += speed.y;
            }
            else {
                associated.box.x = action.pos.x - associated.box.w/2;
                associated.box.y = action.pos.y - associated.box.h/2; 
                taskQueue.pop();
            }
        }
        else if (action.type == Action::ActionType::SHOOT) {

            for (int i = 0; i < nMinions; i++) {
                std::shared_ptr<GameObject> minionGo = minionArray[i].lock();
                double aux = Helpers::EuclideanDistance(Vec2(action.pos.x, action.pos.y), Vec2(minionGo->box.x, minionGo->box.y));   
                if (distance > aux) {
                    distance = aux;
                    index = i;
                }
            }

            std::shared_ptr<Component> aux = minionArray[index].lock()->GetComponent("Minion");
            minion = std::dynamic_pointer_cast<Minion>(aux);
            minion->Shoot(action.pos);
            
            taskQueue.pop();
        }

    }
}

void Alien::Render() {}

bool Alien::Is(const std::string& type) const {
    return (type == "Alien");
}

void Alien::Start() {
    State* state = &Game::GetInstance().GetState();
    
    for (int i = 0; i < nMinions; i++) {
        GameObject* go = new GameObject;
        std::shared_ptr<Minion> minion(new Minion(*go, state->GetObjectPtr(&associated), double(i*2*PI)/nMinions));
        go->AddComponent(minion);
        minionArray.push_back(state->AddObject(go));
    }

}

void Alien::NotifyCollision(GameObject& other) {
    std::shared_ptr<Component> aux;
    if ((aux = other.GetComponent("Bullet")) != nullptr) {
        hp -= std::dynamic_pointer_cast<Bullet>(aux)->GetDamage();
        std::cout << "Colidi com uma bullet" << std::endl;
    }
}

Alien::Action::Action(ActionType type, double x, double y) : 
    type(type),
    pos(x, y) {}