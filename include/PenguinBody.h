#ifndef PEGUINBODY_H
#define PEGUINBODY_H

#include "Component.h"
#include "GameObject.h"

class PenguinBody : public Component {
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;

        static PenguinBody* player;

    private:
        std::weak_ptr<GameObject> penguinCannon;
        Vec2 speed;
        double linearSpeed, angle;
        int hp;
};

#endif