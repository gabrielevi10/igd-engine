#include "Collider.h"
#include "Helpers.h"

#include <iostream>
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG
#define PI 3.14159265359

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : 
    Component(associated),
    scale(scale),
    offset(offset) {}

void Collider::Update(double dt) {
    Vec2 center = associated.box.Center();
    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;
    box.Centralize(center);

    offset.Rotate(Helpers::ConvertToRadians(associated.angleDeg));
    box.x += offset.x;
    box.y += offset.y;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center = box.Center();
	SDL_Point points[5];
    double angleRad = Helpers::ConvertToRadians(associated.angleDeg);

    Vec2 aux = Vec2(box.x, box.y) - center;
    aux.Rotate(angleRad);
	Vec2 point = aux + center + Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
    
    aux = Vec2(box.x + box.w, box.y) - center;
    aux.Rotate(angleRad);
	point = aux + center + Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
    
    aux = Vec2(box.x + box.w, box.y + box.h) - center;
    aux.Rotate(angleRad);
	point = aux + center + Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
    aux = Vec2(box.x, box.y + box.h) - center;
    aux.Rotate(angleRad);
	point = aux + center + Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(const std::string& type) const {
    return (type == "Collider");
}

void Collider::SetScale(const Vec2& scale) {
    this->scale = scale;
}

void Collider::SetOffset(const Vec2& offset) {
    this->offset = offset;
}

void Collider::Start() {}

void Collider::NotifyCollision(GameObject& other) {}