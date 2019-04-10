#include <memory>

#include <iostream>

#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "TileSet.h"

#define PI 3.14159265359

State::State() : quitRequested(false) {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();

    go->AddComponent(std::shared_ptr<Component>(new Sprite(*go, "assets/img/ocean.jpg")));
    go->box.x = 0;
    go->box.y = 0;
    music = new Music("assets/audio/stageState.ogg"); 
    music->Play();
    objectArray.emplace_back(go);
    
    std::shared_ptr<TileSet> tileSet(new TileSet(64, 64, "assets/img/tileset.png"));
    std::shared_ptr<Component> tileMap(new TileMap(*go1, "assets/map/tileMap.txt", tileSet));
    go1->AddComponent(tileMap);
    go1->box.x = 0;
    go1->box.y = 0;
    objectArray.emplace_back(go1);
}

State::~State() {
    delete music;
    objectArray.clear();
}

void State::LoadAssets() {}

void State::Update(float dt) {
    Input();
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quitRequested = true;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			for (int i = objectArray.size() - 1; i >= 0; --i) {
				std::shared_ptr<GameObject> go = objectArray[i];
				if (go->box.Contains({(float)mouseX, (float)mouseY})) {
					std::shared_ptr<Face> face = std::dynamic_pointer_cast<Face>(go->GetComponent("Face"));
					if (nullptr != face) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}
			else {
                Vec2 aux = Vec2(200, 0);
                aux.Rotate(-PI + PI*(rand() % 1001)/500.0);
				Vec2 objPos = aux + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
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