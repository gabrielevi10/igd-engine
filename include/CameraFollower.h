#ifndef CAMERAFOLLOWER_HPP
#define CAMERAFOLLOWER_HPP

#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& go);

        void Update(float dt);
        void Render();
        bool Is(const std::string& type) const;
};

#endif