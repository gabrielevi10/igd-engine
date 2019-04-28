#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, const std::string& file);

        void Update(float dt);
        void Render();
        bool Is(const std::string& type) const;
        void Start();
        int GetDamage() const;
    
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};

#endif