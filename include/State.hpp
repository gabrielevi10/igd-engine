#ifndef STATE_HPP
#define STATE_HPP

#include "Music.hpp"
#include "Sprite.hpp"

class State {
    public: // methods and constructor
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    
    private: // attributes
        Sprite* bg;
        Music* music;
        bool quitRequested;
};

#endif