#include "Face.h"
#include "Sound.h"

#include <iostream>

Face::Face(GameObject& associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    std::shared_ptr<Sound> sound;
    sound = std::dynamic_pointer_cast<Sound>(associated.GetComponent("Sound"));
    if (sound == nullptr)
        throw std::runtime_error("Sound is a nullptr");
    if (hitpoints <= 0) {
        associated.RequestDelete();
        sound->Play(1); 
    } 
}

void Face::Update(float dt) {
    
}

void Face::Render() {}

bool Face::Is(const std::string& type) {
    return (type == "Face"); 
}