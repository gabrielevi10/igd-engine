#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.h"
#include "Vec2.h"

class Camera {
    public:
        void Follow(GameObject* newFocus);
        void Unfollow();
        void Update(float dt);

        Vec2 speed, pos;
    private:
        GameObject* focus;  
};

#endif