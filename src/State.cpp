#include "State.hpp"

State::State() : quitRequested(false) {
    bg = new Sprite();
}

void State::LoadAssets() {}

void Update(fload dt) {
    quitRequested = SDL_QuitRequested();
}

void Render() {
    bg->Render();
}

bool QuitRequested() {
    return quitRequested;
}