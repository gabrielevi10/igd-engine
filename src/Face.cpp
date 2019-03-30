#include "Face.h"

Face::Face(GameObject& associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        // sound.Play(); ?
    } 
}

void Face::Update(const float& dt) {}

void Face::Render() {}

bool Is(const std::string& type) {
    return (type == "Face"); 
}