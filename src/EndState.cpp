#include "EndState.h"
#include "Sprite.h"
#include "GameData.h"
#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"
#include "Text.h"

#include <iostream>

#define WIN_IMG "assets/img/win.jpg"
#define LOSE_IMG "assets/img/lose.jpg"
#define WIN_MSC "assets/audio/endStateWin.ogg"
#define LOSE_MSC "assets/audio/endStateLose.ogg"
#define FONT "assets/font/Call me maybe.ttf"

EndState::EndState() : flag(true) {
    LoadAssets();
}

EndState::~EndState() {}

void EndState::LoadAssets() {
    GameObject* go = new GameObject();
    GameObject* go1 = new GameObject();

    if (GameData::playerVictory) {
        go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go, WIN_IMG)));
        backgroundMusic.Open(WIN_MSC);
    }
    else {
        go->AddComponent(std::shared_ptr<Sprite>(new Sprite(*go, LOSE_IMG)));
        backgroundMusic.Open(LOSE_MSC);
    }
    backgroundMusic.Play(2);
    AddObject(go);

    Text* text = new Text(*go1, FONT, 50, Text::SOLID, "Press space to play again", {0, 0, 0, 0});
    go1->box.Centralize({512, 500});
    go1->AddComponent(std::shared_ptr<Text>(text));
    AddObject(go1);
}

void EndState::Update(double dt) {
    InputManager& input = InputManager::GetInstance();
    if (input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }
    else if (input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
    
    timer.Update(dt);
    if (timer.Get() > 1) {
        flag = 1 - flag;
        timer.Restart();
    }
}

void EndState::Render() {
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

void EndState::Start() {}

void EndState::Pause() {}

void EndState::Resume() {}