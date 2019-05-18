#include "TitleState.h"
#include "Sprite.h"
#include "GameObject.h"
#include "State.h"
#include "StageState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Text.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#include <iostream>

#define TITLE_IMG "assets/img/title.jpg"
#define FONT "assets/font/Call me maybe.ttf"

TitleState::TitleState() {
    GameObject* go = new GameObject();
    go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go, TITLE_IMG)));
    Text* text = new Text(*go, FONT, 50, Text::SOLID, "Press space to play", {0, 0, 0, 0});
    go->AddComponent(std::shared_ptr<Text>(text));
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