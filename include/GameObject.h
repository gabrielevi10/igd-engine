#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include<vector>
#include<string>
#include<memory>

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
        void AddComponent(std::unique_ptr<Component>);
        void RemoveComponent(std::unique_ptr<Component>);
        Component* GetComponent(const std::string& type);
        
        Rect box;
    
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
};

#endif