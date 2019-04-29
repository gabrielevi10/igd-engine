#include "Bullet.h"
#include "Sprite.h"

#include <iostream>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& file) :
    Component(associated),
    speed({speed*cos(angle), speed*sin(angle)}),
    distanceLeft(maxDistance),
    damage(damage) {
    
    std::shared_ptr<Sprite> s(new Sprite(associated, file));
    associated.box.h = s->GetHeight();
    associated.box.w = s->GetWidth();
    associated.AddComponent(s);
}

void Bullet::Update(float dt) {
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= sqrt(pow(speed.x, 2) - pow(speed.y, 2))*dt;

    if (distanceLeft <= 0) 
        associated.RequestDelete();
}

void Bullet::Render() {}

bool Bullet::Is(const std::string& type) const {
    return (type == "Bullet");
}

void Bullet::Start() {}

int Bullet::GetDamage() const {
    return damage;
}