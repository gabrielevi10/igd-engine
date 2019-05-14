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
#include "Sound.h"
#include "Bullet.h"
#include "Collider.h"
#include "PenguinBody.h"

#include <iostream>

#define ALIEN_IMG   "assets/img/alien.png"
#define DEATH_IMG   "assets/img/aliendeath.png"
#define DEATH_SOUND "assets/audio/boom.wav"
#define ANIM_DUR    2.0
#define RST_CWDN    2.0
#define PI 3.14159265359

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : 
    Component(associated),
    state(RESTING),
    speed({0, 0}), 
    hp(50),
    nMinions(nMinions) {
    
    alienCount++;
    std::shared_ptr<Sprite> sprite(new Sprite(associated, ALIEN_IMG));
    associated.AddComponent(sprite);
    associated.box.x = sprite->GetWidth()/2;
    associated.box.y = sprite->GetHeight()/2;

    std::shared_ptr<Collider> collider(new Collider(associated));
    associated.AddComponent(collider);
}

Alien::~Alien() {
    alienCount--;
    minionArray.clear();
}

void Alien::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 center;
    double angle, distance = 99999.9;
    int random, index;
    std::shared_ptr<Minion> minion;
    State& gameState = Game::GetInstance().GetState();
    associated.angleDeg += -1;

    if (PenguinBody::player == nullptr) {}
    else if (state == RESTING) {
        restTimer.Update(dt);
        if (restTimer.Get() > RST_CWDN) {
            state = MOVING;
            destination = gameState.GetPlayerPosition();
        }
    }
    else if (state == MOVING) {
        center = associated.box.Center();
        angle = Helpers::AngleBetweenTwoPoints(Vec2(center.x, center.y), 
                                                Vec2(destination.x, destination.y));
        speed.x = dt*100 * cos(angle);
        speed.y = dt*100 * sin(angle);
        if (Helpers::EuclideanDistance(Vec2(destination.x, destination.y),
                                         Vec2(center.x, center.y)) > dt*100) {
            associated.box.x += speed.x;
            associated.box.y += speed.y;
        }
        else {
            restTimer.Restart();
            associated.box.x = destination.x - associated.box.w/2;
            associated.box.y = destination.y - associated.box.h/2;

            destination = gameState.GetPlayerPosition();

            for (int i = 0; i < nMinions; i++) {
                std::shared_ptr<GameObject> minionGo = minionArray[i].lock();
                if (minionGo == nullptr) {
                    continue;
                }
                double aux = Helpers::EuclideanDistance(Vec2(destination.x, destination.y), 
                                                        Vec2(minionGo->box.x, minionGo->box.y));   
                if (distance > aux) {
                    distance = aux;
                    index = i;
                }
            }
            std::shared_ptr<Component> aux = minionArray[index].lock()->GetComponent("Minion");
            minion = std::dynamic_pointer_cast<Minion>(aux);
            minion->Shoot(destination);
        }
    }
    if (hp <= 0) {
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
        std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(aux);
        if (!bullet->TargetsPlayer()) {
            hp -= std::dynamic_pointer_cast<Bullet>(aux)->GetDamage();
        }
    }
}