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

        void Update(double dt);
        void Render();
        bool IsDead() const;
        void RequestDelete();
        void AddComponent(std::shared_ptr<Component>);
        void RemoveComponent(std::shared_ptr<Component>);
        std::shared_ptr<Component> GetComponent(const std::string& type);
        void Start();
        void NotifyCollision(GameObject& other);
        
        Rect box;
        double angleDeg;
    
    private:
        std::vector<std::shared_ptr<Component>> components;
        bool isDead, started;
};

#endif