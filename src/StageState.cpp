#include <memory>

#include <iostream>

#include "StageState.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Game.h"
#include "Alien.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Helpers.h"
#include "GameData.h"
#include "EndState.h"

#define OCEAN_IMG "assets/img/ocean.jpg"
#define TILESET "assets/img/tileset.png"
#define TILEMAP "assets/map/tileMap.txt"
#define BCK_MSIC "assets/audio/stageState.ogg"
#define PI 3.14159265359
#define NUM_ALIENS 3
#define debug(x) std::cout << x << std::endl;

StageState::StageState() : State() {
    LoadAssets();
   
    for (int i = 0; i < NUM_ALIENS; i++) {
        GameObject* go = new GameObject();
        go->AddComponent(std::shared_ptr<Alien>(new Alien(*go, 5)));
        srand(clock());
        int randX = rand() % 1408;
        int randY = rand() % 1280;
        go->box.x = randX - go->box.x;
        go->box.y = randY - go->box.y;
        AddObject(go);
    }
    
    GameObject* go1 = new GameObject();
    go1->AddComponent(std::shared_ptr<PenguinBody>(new PenguinBody(*go1)));
    go1->box.x = 704;
    go1->box.y = 640;
    AddObject(go1);

    Camera::Follow(go1);
    Camera::speed = {0, 0};
}

StageState::~StageState() {
    objectArray.clear();
}

void StageState::Start() {
    StartArray();
}

void StageState::Pause() {}

void StageState::Resume() {}

void StageState::LoadAssets() {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();

    go->AddComponent(std::shared_ptr<Component>(new Sprite(*go, OCEAN_IMG)));
    go->AddComponent(std::shared_ptr<Component>(new CameraFollower(*go)));
    go->box.x = 0;
    go->box.y = 0;
    AddObject(go);
    
    backgroundMusic.Open(BCK_MSIC);
    backgroundMusic.Play();
    
    std::shared_ptr<TileSet> tileSet(new TileSet(64, 64, TILESET));
    std::shared_ptr<Component> tileMap(new TileMap(*go1, TILEMAP, tileSet));
    go1->AddComponent(tileMap);
    go1->box.x = 0;
    go1->box.y = 0;
    AddObject(go1);
}

void StageState::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    std::vector<std::shared_ptr<Collider>> colliders;
    Collision colision;
    std::shared_ptr<Collider> collider;
    std::vector<int> indexes;
    int k =0;
    
    if (input.KeyPress(ESCAPE_KEY)) {
        popRequested = true;
    }
    if (input.QuitRequested()) {
        quitRequested = true;
    }
    if (PenguinBody::player == nullptr) {
        GameData::playerVictory = false;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
        return;
    }
    else if (Alien::alienCount == 0) {
        GameData::playerVictory = true;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
        return;
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
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        collider = std::dynamic_pointer_cast<Collider>(objectArray[i]->GetComponent("Collider"));
        if (collider != nullptr) {
            colliders.push_back(collider);
            indexes.push_back(i);
            k = 0;
            for (uint32_t j : indexes) {
                double a1 = Helpers::ConvertToRadians(objectArray[j]->angleDeg);
                double a2 = Helpers::ConvertToRadians(objectArray[i]->angleDeg);

                if (i != j && colision.IsColliding(colliders[k++]->box, collider->box, a1, a2)) {
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                }
            }
        }
    }

    colliders.clear();
    indexes.clear();
}

void StageState::Render() {
    std::shared_ptr<TileMap> tilemap = nullptr;
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        if (tilemap == nullptr) {
            tilemap = std::dynamic_pointer_cast<TileMap>(objectArray[i]->GetComponent("TileMap"));
        }
        objectArray[i]->Render();
    }
    if (tilemap != nullptr) {
        tilemap->RenderLayer(1, Camera::pos.x, Camera::pos.y);
    }
}