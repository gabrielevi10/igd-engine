#include <iostream>
#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Helpers.h"
#include "Collider.h"

#define BULLET_IMG "assets/img/minionbullet2.png"
#define MINION_IMG "assets/img/minion.png"
#define PI 3.14159265359

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, double arcOffsetDeg) :
    Component(associated),
    alienCenter(alienCenter),
    arc(arcOffsetDeg) {
    
    int random = rand() % 5;
    random += 11;
    double drandom = (double)random/10.0;

    std::shared_ptr<Sprite> sprite(new Sprite(associated, MINION_IMG));
    sprite->SetScale(drandom, drandom);
    associated.AddComponent(sprite);          

    std::shared_ptr<Collider> collider(new Collider(associated));
    associated.AddComponent(collider);
}

void Minion::Update(double dt) {
    Vec2 center, pos;
    Vec2 dst = {200, 0};
    arc = arc + dt * PI/4.0;
    associated.angleDeg = Helpers::ConvertToDegree(arc);

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

    double dst = Helpers::EuclideanDistance(Vec2(center.x, center.y), Vec2(target.x, target.y));
    double angle = Helpers::AngleBetweenTwoPoints(Vec2(center.x, center.y), Vec2(target.x, target.y));
    
    std::shared_ptr<Bullet> bullet(new Bullet(*go, angle, 100, 10, dst*2, BULLET_IMG));

    go->box.x = center.x - go->box.w/2;
    go->box.y = center.y - go->box.h/2;

    go->AddComponent(bullet);
    go->angleDeg = Helpers::ConvertToDegree(angle);
    state->AddObject(go);
}

void Minion::NotifyCollision(GameObject& other) {}