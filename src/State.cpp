#include <memory>

#include "State.h"
#include "Face.h"
#include "Sound.h"

#define PI 3.14159265359

State::State() : quitRequested(false) {
    GameObject go;
    // bg = new Sprite(go, "assets/img/ocean.jpg");
    go.AddComponent(std::unique_ptr<Component>(new Sprite(go, "assets/img/ocean.jpg")));
    go.box.x = 0;
    go.box.y = 0;
    // go.AddComponent(&Sound(go, "../assets/audio/boom.wav"));
    // go.AddComponent(&Face(go));
    // music = new Music("assets/audio/stageState.ogg"); 
    // music->Play();
    objectArray.emplace_back(go);
}

State::~State() {
    delete bg;
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
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				if (objectArray[i]->box.Contains({(float)mouseX, (float)mouseY})) {
					// auto face = (Face*)objectArray[i]->GetComponent("Face").get();
					// if (nullptr != face) {
					// 	// Aplica dano
					// 	face->Damage(std::rand() % 10 + 10);
					// 	// Sai do loop (só queremos acertar um)
					// 	break;
					// }
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
				Vec2 objPos = aux + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject go;
    go.AddComponent(std::unique_ptr<Component>(new Sprite(go, "../assets/img/penguinface.png")));
    // TODO: Compensar o tamanho da sprite
    go.box.x = mouseX;
    go.box.y = mouseY;
    go.AddComponent(std::unique_ptr<Component> (new Sound(go, "../assets/audio/boom.wav")));
    go.AddComponent(std::unique_ptr<Component> (new Face(go)));
    objectArray.emplace_back(go);
}