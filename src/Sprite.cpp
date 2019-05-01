#include <stdexcept>
#include <iostream>

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : 
    Component(associated), 
    texture(nullptr),
    scale({1, 1}),
    angle(associated.angleDeg) {}

Sprite::Sprite(GameObject& associated, const std::string& file) : 
    Component(associated), 
    texture(nullptr),
    scale({1, 1}),
    angle(associated.angleDeg) {
    
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(const std::string& file) {
    int code;

    texture = Resources::GetImage(file);

    code = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (code != 0) {
        throw std::runtime_error("Sprite SDL_QueryTexture failed: " + std::string(SDL_GetError()));
    }
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    SetClip(0, 0, width, height); 
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render(double x, double y) {
    SDL_Rect dstrect;
    int returned_code;

    dstrect.x = x + Camera::pos.x;
    dstrect.y = y + Camera::pos.y;
    dstrect.w = clipRect.w * scale.x;
    dstrect.h = clipRect.h * scale.y;

    angle = associated.angleDeg;

    returned_code = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
    if (returned_code != 0) {
        throw std::runtime_error("Sprite Render() failed: " + std::string(SDL_GetError()));
    }
}

int Sprite::GetWidth() const {
    return width * (int)scale.x;
}

int Sprite::GetHeight() const {
    return height * (int)scale.y;
}

void Sprite::SetScale(double scaleX, double scaleY) {
    if (scaleX > 0) 
        scale.x = scaleX;
    if (scaleY > 0) 
        scale.y = scaleY;
}

Vec2 Sprite::GetScale() const {
    return scale;
}

void Sprite::SetAngle(double angle) {
    this->angle = angle;
}

double Sprite::GetAngle() const {
    return angle;
}

bool Sprite::IsOpen() const {
    return texture != nullptr;
}

void Sprite::Update(const double dt) {}

bool Sprite::Is(const std::string& type) const {
    return(type == "Sprite");
}

void Sprite::Start() {}