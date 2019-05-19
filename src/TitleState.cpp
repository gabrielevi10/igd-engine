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

TitleState::TitleState() : flag(true) {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();
   
    go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go, TITLE_IMG)));
    AddObject(go);
    
    Text* text = new Text(*go1, FONT, 50, Text::SOLID, "Press space to play", {0, 0, 0, 0});
    go1->box.Centralize({512, 500});
    go1->AddComponent(std::shared_ptr<Text>(text));
    AddObject(go1);
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    timer.Update(dt);
    if (timer.Get() > 1) {
        flag = 1 - flag;
        timer.Restart();
    } 

    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }
    else if (input.KeyPress(SPACE_KEY)) {
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
    }
}

void TitleState::Render() {
    std::shared_ptr<Text> text = nullptr;
    for (uint32_t i = 0; i < objectArray.size(); i++) {
        text = std::dynamic_pointer_cast<Text>(objectArray[i]->GetComponent("Text"));
        if (text == nullptr) {
            objectArray[i]->Render();
        }
        else {
            if (flag) {
                text->Render();
            }
        }
    }
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::pos = {0, 0};
}