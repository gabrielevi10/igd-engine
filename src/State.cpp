#include "State.hpp"

State::State() : quitRequested(false) {
    bg = new Sprite("assets/img/ocean.jpg");
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
    bg->Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}