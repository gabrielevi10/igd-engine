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
        void Update(float dt);
        void Render();
    
    private:
        void Input();
        void AddObject(int, int);

        Music* music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif