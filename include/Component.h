#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "GameObject.h"

class GameObject;

class Component {
    public:
        Component(GameObject& a) : associated(a) {};
        virtual ~Component() = default;

        virtual void Update(double dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(const std::string&) const = 0;
        virtual void Start() = 0;
    
    protected:
        GameObject& associated;
};

#endif