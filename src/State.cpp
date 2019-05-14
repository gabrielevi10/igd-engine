#include <memory>

#include <iostream>

#include "State.h"
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

#define OCEAN_IMG "assets/img/ocean.jpg"
#define TILESET "assets/img/tileset.png"
#define TILEMAP "assets/map/tileMap.txt"
#define BCK_MSIC "assets/audio/stageState.ogg"
#define PI 3.14159265359
#define debug(x) std::cout << x << std::endl;

State::State() : quitRequested(false), started(false) {
    Game& game = Game::GetInstance();
    LoadAssets();
   
    GameObject* go = new GameObject();
    go->AddComponent(std::shared_ptr<Alien>(new Alien(*go, 5)));
    go->box.x = 512 - go->box.x;
    go->box.y = 300 - go->box.y;
    AddObject(go);

    GameObject* go1 = new GameObject();
    go1->AddComponent(std::shared_ptr<PenguinBody>(new PenguinBody(*go1)));
    go1->box.x = 704;
    go1->box.y = 640;
    player = AddObject(go1);

    Camera::Follow(go1);
    // Camera::pos = {0, 0};
    Camera::speed = {0, 0};
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

    go->AddComponent(std::shared_ptr<Component>(new Sprite(*go, OCEAN_IMG)));
    go->AddComponent(std::shared_ptr<Component>(new CameraFollower(*go)));
    go->box.x = 0;
    go->box.y = 0;
    objectArray.emplace_back(go);
    
    music = std::unique_ptr<Music>(new Music(BCK_MSIC)); 
    music->Play();
    
    std::shared_ptr<TileSet> tileSet(new TileSet(64, 64, TILESET));
    std::shared_ptr<Component> tileMap(new TileMap(*go1, TILEMAP, tileSet));
    go1->AddComponent(tileMap);
    go1->box.x = 0;
    go1->box.y = 0;
    objectArray.emplace_back(go1);
}

void State::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    std::vector<std::shared_ptr<Collider>> colliders;
    Collision colision;
    std::shared_ptr<Collider> collider;
    std::vector<int> indexes;
    int k =0;
    
    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
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
            for (int j : indexes) {
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

void State::Render() {
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

Vec2 State::GetPlayerPosition() const {
    std::shared_ptr<GameObject> aux = player.lock();
    return Vec2(aux->box.x, aux->box.y);
}