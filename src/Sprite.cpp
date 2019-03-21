#include <stdexcept>

#include "Sprite.hpp"
#include "Game.hpp"

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
    Game game_instance = Game::GetInstance();
    int code;

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(game_instance.GetRenderer(), file.c_str());
    if (texture == nullptr) {
        throw std::runtime_error("Sprite IMG_LoadTexture failed: " + std::string(SDL_GetError()));
    }

    code = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (code != 0) {
        throw std::runtime_error("Sprite SDL_QueryTexture" + std::string(SDL_GetError()));
    }
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    Game game_instance = Game::GetInstance();
    SDL_Rect dstrect;

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(game_instance.GetRenderer(), texture, &clipRect, &dstrect);
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
