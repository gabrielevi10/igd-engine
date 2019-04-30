#include "Face.h"
#include "Sound.h"
#include "Camera.h"
#include "InputManager.h"

#include <iostream>

Face::Face(GameObject& associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    std::shared_ptr<Sound> sound;
    sound = std::dynamic_pointer_cast<Sound>(associated.GetComponent("Sound"));
    if (hitpoints <= 0) {
        associated.RequestDelete();
        sound->Play(1); 
    } 
}

void Face::Update(float dt) {
    InputManager& input = InputManager::GetInstance();
    Vec2 click = {(float)input.GetMouseX() - Camera::pos.x, (float)input.GetMouseY() - Camera::pos.y};
    if (input.MousePress(1) && associated.box.Contains(click)) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render() {}

bool Face::Is(const std::string& type) const {
    return (type == "Face"); 
}