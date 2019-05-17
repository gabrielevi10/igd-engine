#include "TitleState.h"
#include "Sprite.h"
#include "GameObject.h"
#include "State.h"
#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#include <iostream>

#define TITLE_IMG "assets/img/title.jpg"

TitleState::TitleState() {
    GameObject* go = new GameObject();
    go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go, TITLE_IMG)));
    go->box.x = -Camera::pos.x;
    go->box.y = -Camera::pos.y;
    AddObject(go);
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(double dt) {
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }
    else if (input.KeyPress(SPACE_KEY)) {
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
    }
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::pos = {0, 0};
}