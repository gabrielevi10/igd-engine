#include <stdexcept>
#include <iostream>

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr) {}

Sprite::Sprite(std::string file) : texture(nullptr) {
    Open(file);  
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    int code;

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        throw std::runtime_error("Sprite IMG_LoadTexture failed: " + std::string(SDL_GetError()));
    }

    code = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (code != 0) {
        throw std::runtime_error("Sprite SDL_QueryTexture failed: " + std::string(SDL_GetError()));
    }
    
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    int returned_code;

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    returned_code = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
    if (returned_code != 0) {
        throw std::runtime_error("Sprite Render() failed: " + std::string(SDL_GetError()));
    }
}

int Sprite::GetWidth() const {
    return width;
}

int Sprite::GetHeight() const {
    return height;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}
