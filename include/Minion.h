#ifndef MINION_H
#define MINION_H

#include <memory>

#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Minion : public Component {
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, double arcOffSetDeg = 0);

        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void Start();
        void Shoot(Vec2 target);
    
    private:
        std::weak_ptr<GameObject> alienCenter;
        double arc;
};

#endif