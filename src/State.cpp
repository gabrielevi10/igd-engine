#include <memory>

#include <iostream>

#include "State.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"

#define PI 3.14159265359

State::State() : quitRequested(false), started(false) {
    LoadAssets();
   
    GameObject* go = new GameObject();
    go->AddComponent(std::shared_ptr<Alien>(new Alien(*go, 5)));
    go->box.x = 512 - go->box.x;
    go->box.y = 300 - go->box.y;
    AddObject(go);

    Camera::pos = {0, 0};
    Camera::speed = {0, 0};

    GameObject* go1 = new GameObject();
    go1->AddComponent(std::shared_ptr<PenguinBody>(new PenguinBody(*go1)));
    go1->box.x = 0;
    go1->box.y = 0;
    AddObject(go1);
}

State::~State() {
    objectArray.clear();
}

void State::Start() {
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true; 
}

void State::LoadAssets() {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();

    go->AddComponent(std::shared_ptr<Component>(new Sprite(*go, "assets/img/ocean.jpg")));
    go->AddComponent(std::shared_ptr<Component>(new CameraFollower(*go)));
    go->box.x = 0;
    go->box.y = 0;
    objectArray.emplace_back(go);
    
    music = std::unique_ptr<Music>(new Music("assets/audio/stageState.ogg")); 
    music->Play();
    
    std::shared_ptr<TileSet> tileSet(new TileSet(64, 64, "assets/img/tileset.png"));
    std::shared_ptr<Component> tileMap(new TileMap(*go1, "assets/map/tileMap.txt", tileSet));
    go1->AddComponent(tileMap);
    go1->box.x = 0;
    go1->box.y = 0;
    objectArray.emplace_back(go1);
}

void State::Update(double dt) {
    InputManager& input = InputManager::GetInstance(); 
    
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
    if (input.KeyPress(SPACE_KEY)) {
        Vec2 aux = Vec2(200, 0);
        aux.Rotate(-PI + PI*(rand() % 1001)/500.0);
        // Vec2 objPos = aux + Vec2(input.GetMouseX(), input.GetMouseY());
        // AddObject();
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
    std::shared_ptr<TileMap> tilemap = nullptr;
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        if (tilemap == nullptr) {
            tilemap = std::dynamic_pointer_cast<TileMap>(objectArray[i]->GetComponent("TileMap"));
        }
        objectArray[i]->Render();
    }
    if (tilemap != nullptr) {
        tilemap->RenderLayer(1);
    }
}

bool State::QuitRequested() const {
    return quitRequested;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) const {
    std::weak_ptr<GameObject> wkptr = std::weak_ptr<GameObject>();
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        if (go == objectArray[i].get()) {
            wkptr = objectArray[i];
            break;
        }
    }
    return wkptr;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> shrptr(go);
    std::weak_ptr<GameObject> weakptr = shrptr;
    
    objectArray.push_back(shrptr);
    
    if (started) {
        shrptr->Start();
    }

    return weakptr;
}