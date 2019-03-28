#ifndef VEC2_HPP
#define VEC2_HPP

class Vec2 {
    public:
        Vec2();
        Vec2(float, float);

        Vec2 operator+(const Vec2&) const;
        Vec2 operator-(const Vec2&) const;
        Vec2& operator=(const Vec2&);
        Vec2 operator*(const float) const;

        double Magnitude(const Vec2&) const;
        double Magnitude() const;
        Vec2 Normalize();
        double Distance(const Vec2&) const;

        float x, y;
};

#endif