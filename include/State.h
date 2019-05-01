#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"

class State {
    public:
        State();
        ~State();

        bool QuitRequested() const;
        void LoadAssets();
        void Update(double dt);
        void Render();
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go) const;

    private:
        void Input();

        std::unique_ptr<Music> music;
        bool quitRequested, started;
        std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif