#include "Collider.h"
#include "Helpers.h"
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
    box.x = associated.box.Center().x + associated.box.w/2;
    box.y = associated.box.Center().y + associated.box.h/2;
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;

    Vec2 aux(box.x + offset.x, box.y + offset.y);
    aux.Rotate(Helpers::ConvertToRadians(associated.angleDeg)); 
    box.x = aux.x;
    box.y = aux.y;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

    Vec2 aux = Vec2(box.x, box.y) - center;
    aux.Rotate(associated.angleDeg/(180/PI));
	Vec2 point = aux + center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
    
    aux = Vec2(box.x + box.w, box.y) - center;
    aux.Rotate(associated.angleDeg/(180/PI));
	point = aux + center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
    
    aux = Vec2(box.x + box.w, box.y + box.h) - center;
    aux.Rotate(associated.angleDeg/(180/PI));
	point = aux + center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
    aux = Vec2(box.x, box.y + box.h) - center;
    aux.Rotate(associated.angleDeg/(180/PI));
	point = aux + center - Camera::pos;
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