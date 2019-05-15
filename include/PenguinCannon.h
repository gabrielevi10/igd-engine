#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

#include <memory>

class PenguinCannon : public Component {
    public: 
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void Start();
        void NotifyCollision(GameObject& other);

        void Shoot();
        
    private:
        std::weak_ptr<GameObject> penguinBody;
        double angle;
        Timer timer;
};

#endif