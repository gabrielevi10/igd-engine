#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "Helpers.h"
#include "InputManager.h"
#define SDL_ICLUDE
#include "SDL_include.h"

#include <iostream>

#define PENGUIN_IMG "assets/img/penguin.png"
#define PI 3.14159265359
#define MAX_SPEED 20
#define MINIMUM_SPEED -20

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
    angle = associated.angleDeg;
    bool keyPressed = false;

    if (input.IsKeyDown(W_KEY)) {
        if (linearSpeed < MAX_SPEED) {
            linearSpeed += dt*10;
        }
        keyPressed = true;
    }
    if (input.IsKeyDown(S_KEY)) {
        if (linearSpeed > MINIMUM_SPEED) {
            linearSpeed -= dt*10;
        }
        keyPressed = true;
    }
    if (input.IsKeyDown(A_KEY)) {
        angle = angle - dt*100;
        associated.angleDeg = angle; 
    }
    if (input.IsKeyDown(D_KEY)) {
        angle = angle + dt*100;
        associated.angleDeg = angle;
    }
    if (!keyPressed) {
        if (linearSpeed > 0)
            linearSpeed -= dt*5;
        else if (linearSpeed < 0) {
            linearSpeed += dt*5;
        }
    }
    if (hp <= 0) {
        associated.RequestDelete();
    }
    
    speed = {linearSpeed, 0};
    speed.Rotate(Helpers::ConvertToRadians(angle));
    associated.box.x += speed.x;
    associated.box.y += speed.y; 
}

void PenguinBody::Render() {}

bool PenguinBody::Is(const std::string& type) const {
    return (type == "PenguinBody");
}
