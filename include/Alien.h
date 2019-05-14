#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <queue>
#include <vector>
#include <memory>

#include "Timer.h"
#include "Vec2.h"
#include "Component.h"
#include "GameObject.h"

class Alien : public Component {
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();

        void Start();
        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void NotifyCollision(GameObject& other);

        static int alienCount;

    private:
        enum AlienState {MOVING, RESTING};
        AlienState state;
        Timer restTimer;
        Vec2 speed, destination;
        int hp, nMinions;
        std::vector<std::weak_ptr<GameObject>> minionArray;
};  

#endif