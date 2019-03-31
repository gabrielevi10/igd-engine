#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        ((Sound*)associated.GetComponent("Sound").get())->Play();
    } 
}

void Face::Update(const float& dt) {}

void Face::Render() {}

bool Face::Is(const std::string& type) {
    return (type == "Face"); 
}