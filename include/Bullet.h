#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
    public:
        Bullet(GameObject& associated, double angle, double speed, 
                int damage, double maxDistance, const std::string& 
                file, bool targetsPlayer, int frames);

        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void Start();
        int GetDamage() const;
        void NotifyCollision(GameObject& other);
        bool TargetsPlayer() const;

    private:
        Vec2 speed;
        double distanceLeft;
        int damage;
        bool targetsPlayer;
};

#endif