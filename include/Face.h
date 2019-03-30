#ifndef FACE_HPP
#define FACE_HPP

#include "Component.h"

class Face : public Component {
    public:
        Face(GameObject& associated);
        
        void Damage(int damage);
        
        void Update(const float& dt);
        void Render();
        bool Is(const std::string& type);

    private:
        int hitpoints;
};

#endif