#include "GameObject.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    std::vector<Component*>::reverse_iterator rit = components.rbegin();
    for (; rit != components.rend(); ++rit)
        delete *rit;
    components.clear();
}

void GameObject::Update(const float& dt) {
    for (Component* cp : components) {
        cp->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* cp : components) {
        cp->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    int index = 0;
    for (Component* cp : components) {
        if (cp == cpt) {
            delete cp;
            components.erase(components.begin(), components.begin() + index);
        }
        index++;
    }
}

Component* GameObject::GetComponent(const std::string& type) {
    for (Component* cp : components) {
        if (cp->Is(type)) {
            return cp;
        }
    }
    return nullptr;
}
