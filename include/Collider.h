#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider : public Component {
    public:
        Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void SetScale(const Vec2& scale);
        void SetOffset(const Vec2& offset);
        void Start();
        void NotifyCollision(GameObject& other);

        Rect box;
    
    private:
        Vec2 scale, offset;
};

#endif