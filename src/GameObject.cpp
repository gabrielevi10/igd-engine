#include <iostream>
#include "GameObject.h"

GameObject::GameObject() : isDead(false), started(false) {}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    for (uint32_t i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(const float& dt) {
    for (uint32_t i = 0; i < components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (uint32_t i = 0; i < components.size(); i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt) {
    for (uint32_t i = 0; i < components.size(); i++) {
        if (components[i] == cpt) {
            components.erase(components.begin() + i);
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(const std::string& type) {
    for (uint32_t i = 0; i < components.size(); i++) {
        if (components[i]->Is(type)) {
            return components[i];
        }
    }
    return nullptr;
}
