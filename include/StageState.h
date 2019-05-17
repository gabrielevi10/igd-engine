#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "TileSet.h"
#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "GameObject.h"

class StageState : public State {
    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(double dt);
        void Render();
        
        void Start();
        void Pause();
        void Resume();

    private:
        TileSet* tileSet;
        Music backgroundMusic;
};

#endif