#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "InputManager.h"
#define SDL_ICLUDE
#include "SDL_include.h"

#include <iostream>

#define PENGUIN_IMG "assets/img/penguin.png"
#define PI 3.14159265359

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : 
    Component(associated),
    speed({0, 0}),
    linearSpeed(0),
    angle(0),
    hp(50) {
    
    std::shared_ptr<Sprite> bodySprite(new Sprite(associated, PENGUIN_IMG));
    associated.AddComponent(bodySprite);
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    Game& gameInstance = Game::GetInstance();
    State& stateInstance = gameInstance.GetState();
    GameObject* go = new GameObject();

    std::shared_ptr<PenguinCannon> pcannon(new PenguinCannon(*go, stateInstance.GetObjectPtr(&associated)));
    go->AddComponent(pcannon);
    stateInstance.AddObject(go);
    penguinCannon = stateInstance.GetObjectPtr(go);
}

void PenguinBody::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    speed = {0, 0};
    angle = associated.angleDeg;
    if (input.IsKeyDown(W_KEY)) {
        if (speed.x < 300 && speed.y < 300) {
            speed.x += dt*100 * cos(angle);
            speed.y += dt*100 * sin(angle);
        }
        associated.box.x += speed.x;
        associated.box.y += speed.y;    
    }
    else if (input.IsKeyDown(S_KEY)) {
        if (speed.x > -300 && speed.y > -300) {
            speed.x -= dt*100;
            speed.y -= dt*100;
        }
        associated.box.x += speed.x;
        associated.box.y += speed.y;
    }
    else if (input.IsKeyDown(A_KEY)) {
        angle = angle - dt/4;
        associated.angleDeg = angle*180/PI; 
    }
    else if (input.IsKeyDown(D_KEY)) {
        angle = angle + dt/4;
        associated.angleDeg = angle*180/PI;
    }
    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(const std::string& type) const {
    return (type == "PenguinBody");
}
