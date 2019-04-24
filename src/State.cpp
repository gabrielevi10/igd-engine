#include <memory>

#include <iostream>

#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

#define PI 3.14159265359

State::State() : quitRequested(false) {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();

    go->AddComponent(std::shared_ptr<Component>(new Sprite(*go, "assets/img/ocean.jpg")));
    go->AddComponent(std::shared_ptr<Component>(new CameraFollower(*go)));
    go->box.x = 0;
    go->box.y = 0;
    objectArray.emplace_back(go);
    
    music = new Music("assets/audio/stageState.ogg"); 
    music->Play();
    
    std::shared_ptr<TileSet> tileSet(new TileSet(64, 64, "assets/img/tileset.png"));
    std::shared_ptr<Component> tileMap(new TileMap(*go1, "assets/map/tileMap.txt", tileSet));
    go1->AddComponent(tileMap);
    go1->box.x = 0;
    go1->box.y = 0;
    objectArray.emplace_back(go1);

    Camera::pos = {0, 0};
    Camera::speed = {0, 0};
}

State::~State() {
    delete music;
    objectArray.clear();
}

void State::LoadAssets() {}

void State::Update(float dt) {
    InputManager& input = InputManager::GetInstance(); 
    
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
    if (input.KeyPress(SPACE_KEY)) {
        Vec2 aux = Vec2(200, 0);
        aux.Rotate(-PI + PI*(rand() % 1001)/500.0);
        Vec2 objPos = aux + Vec2(input.GetMouseX(), input.GetMouseY());
        AddObject((int)objPos.x, (int)objPos.y);
    }

    Camera::Update(dt);
    
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() const {
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* go = new GameObject();
    Sprite* s = new Sprite(*go, "assets/img/penguinface.png");

    go->AddComponent(std::shared_ptr<Component>(s));
    go->box.x = mouseX - s->GetWidth()/2;
    go->box.y = mouseY - s->GetHeight()/2;
    go->box.h = s->GetHeight();
    go->box.w = s->GetWidth();
    go->AddComponent(std::shared_ptr<Component>(new Sound(*go, "assets/audio/boom.wav")));
    go->AddComponent(std::shared_ptr<Component>(new Face(*go)));
    objectArray.emplace_back(go);
}