#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#define SDL_ICLUDE
#include "SDL_include.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : 
    Component(associated),
    speed({0, 0}),
    linearSpeed(0),
    angle(0) {
    
    std::shared_ptr<Sprite> bodySprite(new Sprite(associated, "assets/img/penguin.png"));
    associated.AddComponent(bodySprite);
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    // GameObject* go = new GameObject();
    // PenguinCannon* pcannon = new PenguinCannon(*go, std::weak_ptr<PenguinBody>(player));
    // penguinCannon = std::weak_ptr<PenguinCannon>(new PenguinCannon(*go, pcannon)); 
}

void PenguinBody::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    speed = {0, 0};
    angle = associated.angleDeg;
    if (input.KeyPress(W_KEY)) {
        if (speed.x < 300 && speed.y < 300) {
            speed.x += dt*100;
            speed.y += dt*100;
        }
        associated.box.x += speed.x;
        associated.box.y += speed.y;    
    }
    else if (input.KeyPress(S_KEY)) {
        if (speed.x > -300 && speed.y > -300) {
            speed.x -= dt*100;
            speed.y -= dt*100;
        }
        associated.box.x += speed.x;
        associated.box.y += speed.y;
    }
    else if (input.KeyPress(A_KEY)) {
        associated.angleDeg = angle - dt; 
    }
    else if (input.KeyPress(D_KEY)) {
        associated.angleDeg = angle + dt;
    }
    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(const std::string& type) const {
    return (type == "PenguinBody");
}
