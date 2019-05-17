#include "State.h"
#include "TileMap.h"
#include "Camera.h"
#include <algorithm>

State::State() : 
    popRequested(false),
    quitRequested(false),
    started(false) {}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) const {
    std::weak_ptr<GameObject> wkptr = std::weak_ptr<GameObject>();
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        if (object == objectArray[i].get()) {
            wkptr = objectArray[i];
            break;
        }
    }
    return wkptr;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
    std::shared_ptr<GameObject> shrptr(object);

    std::weak_ptr<GameObject> weakptr = shrptr;
    
    objectArray.push_back(shrptr);
    
    if (started) {
        shrptr->Start();
    }
    
    return weakptr;
}

bool State::PopRequested() const {
    return popRequested;
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::StartArray() {
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

void State::UpdateArray(double dt) {
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}