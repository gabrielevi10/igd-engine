#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.h"
#include "Vec2.h"

class Camera {
    public:
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(double dt);

        static Vec2 speed, pos;
    private:
        static GameObject* focus;  
};

#endif