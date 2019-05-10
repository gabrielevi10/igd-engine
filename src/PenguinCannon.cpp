#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Camera.h"
#include "Helpers.h"

#define GUN_IMG "assets/img/cubngun.png"
#define BULLET_IMG "assets/img/penguinbullet.png"
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
    Vec2 center, pbodyCenter;
    double mx, my;

    if (pbody != nullptr) {
        pbodyCenter = pbody->box.Center();
        associated.box.x = pbodyCenter.x - pbody->box.w/2;
        associated.box.y = pbodyCenter.y - pbody->box.h/2;

        center = associated.box.Center();

        mx = input.GetMouseX() - Camera::pos.x;
        my = input.GetMouseY() - Camera::pos.y;
        
        angle = Helpers::AngleBetweenTwoPoints(Vec2(center.x, center.y), Vec2(mx, my));
        
        associated.angleDeg = Helpers::ConvertToDegree(angle);
        
        if (input.MousePress(LEFT_MOUSE_BUTTON)) 
            Shoot();

    }
    else {
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(const std::string& type) const {
    return (type == "PenguinCannon");
}

#include <iostream>

void PenguinCannon::Shoot() {
    State* state = &Game::GetInstance().GetState();
    GameObject* go = new GameObject();
    Vec2 center = associated.box.Center();

    std::shared_ptr<Bullet> bullet(new Bullet(*go, angle, 100, 10, 5000, BULLET_IMG));

    go->box.x = center.x - go->box.w/2;
    go->box.y = center.y - go->box.h/2;

    go->AddComponent(bullet);
    go->angleDeg = Helpers::ConvertToDegree(angle);
    state->AddObject(go);
}

void PenguinCannon::Start() {}