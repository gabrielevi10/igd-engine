#ifndef STATE_HPP
#define STATE_HPP

#include "Music.h"
#include "Sprite.h"

class State {
    public: // methods and constructor
        State();
        ~State();

        bool QuitRequested() const;
        void LoadAssets();
        void Update(float dt);
        void Render();
    
    private: // attributes
        Sprite* bg;
        Music* music;
        bool quitRequested;
};

#endif