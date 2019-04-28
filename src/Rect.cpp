#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(const float& rx, const float& ry, const float& rw, const float& rh) :
    x(rx), y(ry), w(rw), h(rh) {}

Rect Rect::operator+(const Vec2& vec) const {
    return Rect(x + vec.x, y + vec.y, w, h);
}

Rect Rect::operator+(const Rect& other) const {
    return Rect(x + other.x, y + other.y, w + other.w, h + other.h);
}

Rect Rect::operator-(const Rect& other) const {
    return Rect(x - other.x, y - other.y, w - other.w, h - other.h);
}

Rect Rect::operator*(const float& scalar) const {
    return Rect(x * scalar, y * scalar, w * scalar, h * scalar);
}

Rect& Rect::operator=(const Rect& other) {
    x = other.x;
    y = other.y;
    w = other.w;
    h = other.h;
    return *this;
}

Vec2 Rect::Center() const {
    return Vec2(x + w/2, y + h/2);
}

bool Rect::Contains(const Vec2& point) const {
    return(point.x <= (x + w) && point.y <= (y + h) && (point.x >= x && point.y >= y));
}