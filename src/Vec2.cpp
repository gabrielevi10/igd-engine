#include "Vec2.h"
#include <cmath>
#include <iostream>
#include <vector>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x1, float y1) : x(x1), y(y1) {}

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2& Vec2::operator=(const Vec2& other) {
    x = other.x;
    y = other.y;
    return *this;
}

Vec2 Vec2::operator*(const float& scalar) const {
    return Vec2(x*scalar, y*scalar);
}

double Vec2::Magnitude(const Vec2& vec) const {
    return(sqrt((vec.x*vec.x) + (vec.y*vec.y)));
}

double Vec2::Magnitude() const {
    return(sqrt((x*x) + (y*y)));
}

Vec2 Vec2::Normalize() {
    return Vec2(x/Magnitude(), y/Magnitude());
}

double Vec2::Distance(const Vec2& other) const {
    return (*this - other).Magnitude(); 
}

double Vec2::Inclination() const {
    return atan2(x, y);
}

void Vec2::Rotate(const float& angle) {
    float px = x * cos(angle) - y * sin(angle);
    float py = x * sin(angle) + y * cos(angle);
    x = px;
    y = py;
}

