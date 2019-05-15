#include <iostream>
#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Helpers.h"
#include "Collider.h"
#include "Sound.h"
#include <chrono>

#define BULLET_IMG "assets/img/minionbullet2.png"
#define MINION_IMG "assets/img/minion.png"
#define DEATH_IMG "assets/img/miniondeath.png"
#define DEATH_SOUND "assets/audio/boom.wav"
#define ANIM_DUR 2.0
#define PI 3.14159265359
#define MINION_DST 200


Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, double arcOffsetDeg) :
    Component(associated),
    alienCenter(alienCenter),
    arc(arcOffsetDeg),
    hp(30) {
    
    srand(clock());
    int random = rand() % 5;
    random += 10;
    double drandom = (double)random/10.0;
    
    std::shared_ptr<Sprite> sprite(new Sprite(associated, MINION_IMG));
    sprite->SetScale(drandom, drandom);
    associated.AddComponent(sprite);

    std::shared_ptr<Collider> collider(new Collider(associated, {drandom, drandom}));
    associated.AddComponent(collider);
}

void Minion::Update(double dt) {
    Vec2 center, pos;
    Vec2 dst = {MINION_DST, 0};
    arc = arc + dt * PI/4.0;
    associated.angleDeg = Helpers::ConvertToDegree(arc);

    dst.Rotate(arc);
    std::shared_ptr<GameObject> alien = alienCenter.lock();
    if (alien != nullptr) {
        center = alien->box.Center();
        pos = dst + center;
        associated.box.Centralize(pos);
    }
    if (hp <= 0 || alien == nullptr) {
        associated.RequestDelete();
        State& state = Game::GetInstance().GetState();
        GameObject* go = new GameObject();

        std::shared_ptr<Sprite> deathSprite(new Sprite(*go, DEATH_IMG, 4, 
                                            ANIM_DUR/4, ANIM_DUR));

        std::shared_ptr<Sound> deathSound(new Sound(*go, DEATH_SOUND));

        go->AddComponent(deathSprite);
        go->AddComponent(deathSound);
        go->box.Centralize(associated.box.Center());
        
        deathSound->Play();

        state.AddObject(go);
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

    double angle = Helpers::AngleBetweenTwoPoints(Vec2(center.x, center.y), Vec2(target.x, target.y));
    
    std::shared_ptr<Bullet> bullet(new Bullet(*go, angle, 300, 10, 5000, BULLET_IMG, true, 3));

    go->box.x = center.x - go->box.w/2;
    go->box.y = center.y - go->box.h/2;

    go->AddComponent(bullet);
    go->angleDeg = Helpers::ConvertToDegree(angle);
    state->AddObject(go);
}

void Minion::NotifyCollision(GameObject& other) {
    std::shared_ptr<Component> aux;
    if ((aux = other.GetComponent("Bullet")) != nullptr) {
        std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(aux);
        if (!bullet->TargetsPlayer()) {
            hp -= std::dynamic_pointer_cast<Bullet>(aux)->GetDamage();
        }
    }
}