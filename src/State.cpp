#include "State.h"
#include <memory>

State::State() : quitRequested(false) {
    // bg = new Sprite("assets/img/ocean.jpg", nullptr);
    music = new Music("assets/audio/stageState.ogg"); 
    music->Play();
}

State::~State() {
    delete bg;
    delete music;
}

void State::LoadAssets() {}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg->Render();
}

bool State::QuitRequested() const {
    return quitRequested;
}