#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "Game.h"
#include "StageState.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Camera.h"
#include "Helpers.h"
#include "Collider.h"

#include <iostream>

#define GUN_IMG "assets/img/cubngun.png"
#define BULLET_IMG "assets/img/penguinbullet.png"
#define PI 3.14159265359
#define SHOOT_COOLDOWN 1

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : 
    Component(associated),
    penguinBody(penguinBody),
    angle(0) {

    std::shared_ptr<Sprite> cannonSprite(new Sprite(associated, GUN_IMG));
    associated.AddComponent(cannonSprite);

    std::shared_ptr<Collider> collider(new Collider(associated));
    associated.AddComponent(collider);
}

void PenguinCannon::Update(double dt) {
    timer.Update(dt);
    std::shared_ptr<GameObject> pbody = penguinBody.lock();
    InputManager& input = InputManager::GetInstance();
    Vec2 center, pbodyCenter;
    double mx, my;

    if (pbody != nullptr) {
        pbodyCenter = pbody->box.Center();

        associated.box.Centralize(pbodyCenter);

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

void PenguinCannon::Shoot() {
    if (timer.Get() < SHOOT_COOLDOWN) {
        return;
    }
    timer.Restart();
    State& state = Game::GetInstance().GetCurrentState();
    GameObject* go = new GameObject();
   
    std::shared_ptr<Bullet> bullet(new Bullet(*go, angle, 300, 10, 5000, BULLET_IMG, false, 4));
    go->angleDeg = associated.angleDeg;
    go->AddComponent(bullet);
    
    Vec2 aux(associated.box.w/2, 0);
    aux.Rotate(angle);
    aux = associated.box.Center() + aux;
    go->box.Centralize(aux);
    
    state.AddObject(go);
}

void PenguinCannon::Start() {}

void PenguinCannon::NotifyCollision(GameObject& other) {}