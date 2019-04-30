#include <iostream>
#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"

#define PI 3.14159265359

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, double arcOffsetDeg) :
    Component(associated),
    alienCenter(alienCenter),
    arc(arcOffsetDeg) {
    
    int random = rand() % 5;
    random += 11;
    double drandom = (double)random/10.0;

    std::shared_ptr<Sprite> sprite(new Sprite(associated, "assets/img/minion.png"));
    sprite->SetScale(drandom, drandom);
    associated.AddComponent(sprite);          
}

void Minion::Update(float dt) {
    Vec2 center, pos;
    Vec2 dst = {200, 0};
    arc = arc + dt * PI/4.0;
    associated.angleDeg = arc*180/PI;

    dst.Rotate(arc);
    std::shared_ptr<GameObject> alien = alienCenter.lock();
    if (alien != nullptr) {
        center = alien->box.Center();
        pos = dst + center;
        associated.box.x = pos.x - associated.box.w/2;
        associated.box.y = pos.y - associated.box.h/2;
    }
    else {
        associated.RequestDelete();
    }
}

void Minion::Render() {}

bool Minion::Is(const std::string& type) const {
    return (type == "Minion");
}

void Minion::Start() {}

#include <iostream>

void Minion::Shoot(Vec2 target) {
    State* state = &Game::GetInstance().GetState();
    GameObject* go = new GameObject();
    Vec2 center = associated.box.Center();
    auto dst = sqrt(pow(target.x - center.x, 2) + pow(target.y - center.y, 2));

    go->box.x = center.x - go->box.w/2;
    go->box.y = center.y - go->box.h/2;

    float angle = atan2(target.y - center.y, target.x - center.x);
    std::shared_ptr<Bullet> bullet(new Bullet(*go, angle, 500, 10, dst*2, "assets/img/minionbullet1.png"));
    go->AddComponent(bullet);
    go->angleDeg = angle*180/PI;
    state->AddObject(go);
}
