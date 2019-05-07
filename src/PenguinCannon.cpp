#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Camera.h"

#define GUN_IMG "assets/img/cubngun.png"
#define PI 3.14159265359

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : 
    Component(associated),
    penguinBody(penguinBody),
    angle(0) {

    std::shared_ptr<Sprite> cannonSprite(new Sprite(associated, GUN_IMG));
    associated.AddComponent(cannonSprite);
}

void PenguinCannon::Update(double dt) {
    std::shared_ptr<GameObject> pbody = penguinBody.lock();
    InputManager& input = InputManager::GetInstance();
    double angle, mx, my;
    if (pbody != nullptr) {
        associated.box.x = pbody->box.Center().x - pbody->box.w/2;
        associated.box.y = pbody->box.Center().y - pbody->box.h/2;

        mx = input.GetMouseX() - Camera::pos.x;
        my = input.GetMouseY() - Camera::pos.y;
        angle = atan2(my - associated.box.Center().y, mx - associated.box.Center().x);
        associated.angleDeg = angle*180/PI;
    }
    else {
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(const std::string& type) const {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {}

void PenguinCannon::Start() {}