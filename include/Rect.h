#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2.h"

class Rect {
    public:
        Rect();
        Rect(const float&, const float&, const float&, const float&);
        
        Rect operator+(const Vec2&) const;
        Rect operator+(const Rect&) const;
        Rect operator-(const Rect&) const;
        Rect operator*(const float&) const;
        Rect& operator=(const Rect&);

        Vec2 Center() const;
        bool Contains(const Vec2&) const;

        float x, y, w, h;

};

#endif