#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : 
    Component(associated),
    penguinBody(penguinBody) {}

void PenguinCannon::Update(double dt) {}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(const std::string& type) const {}

void PenguinCannon::Shoot() {}