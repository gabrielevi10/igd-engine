#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2.h"

class Rect {
    public:
        Rect();
        Rect(double, double, double, double);
        
        Rect operator+(const Vec2&) const;
        Rect operator+(const Rect&) const;
        Rect operator-(const Rect&) const;
        Rect operator*(double) const;
        Rect& operator=(const Rect&);

        Vec2 Center() const;
        bool Contains(const Vec2&) const;


        double x, y, w, h;
};

#endif