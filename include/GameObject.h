#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include<vector>
#include<string>

#include "Rect.h"
#include "Component.h"

class Component;

class GameObject {
    public:
        GameObject();
        ~GameObject();

        void Update(const float& dt);
        void Render();
        bool IsDead() const;
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(const std::string& type);
        
        Rect box;
    
    private:
        std::vector<Component*> components;
        bool isDead;
};

#endif