#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

#include <iostream>

Bullet::Bullet(GameObject& associated, double angle, double speed, int damage, 
                double maxDistance, const std::string& file, bool targetsPlayer, int frames) :
    Component(associated),
    speed({speed*cos(angle), speed*sin(angle)}),
    distanceLeft(maxDistance),
    damage(damage),
    targetsPlayer(targetsPlayer) {
    
    std::shared_ptr<Sprite> s(new Sprite(associated, file, frames));
    // s->SetScale(3, 3);
    associated.AddComponent(s);

    std::shared_ptr<Collider> collider(new Collider(associated));
    associated.AddComponent(collider);
}

void Bullet::Update(double dt) {
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= sqrt(pow(speed.x, 2) + pow(speed.y, 2))*dt;

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

bool Bullet::TargetsPlayer() const {
    return targetsPlayer;
}

void Bullet::NotifyCollision(GameObject& other) {
    if (other.GetComponent("Alien") != nullptr && !targetsPlayer) {
        associated.RequestDelete();
    }
    else if (other.GetComponent("Minion") != nullptr && !targetsPlayer) {
        associated.RequestDelete();
    }
    else if (other.GetComponent("Penguin") != nullptr && targetsPlayer) {
        associated.RequestDelete();
    }
}