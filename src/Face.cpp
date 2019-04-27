#include "Face.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"

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
    if (input.MousePress(1) && associated.box.Contains({(float)input.GetMouseX() - Camera::pos.x, (float)input.GetMouseY() - Camera::pos.y})) {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render() {}

bool Face::Is(const std::string& type) const {
    return (type == "Face"); 
}