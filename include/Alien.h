#ifndef ALIEN_HPP
#define ALIEN_HPP

#include <queue>
#include <vector>
#include <memory>

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
    
    private:
        class Action {
            public:
                typedef enum ActionType {MOVE, SHOOT} ActionType;
                Action(ActionType type, double x, double y);

                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp, nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
};  

#endif