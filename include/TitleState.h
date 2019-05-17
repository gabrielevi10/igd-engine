#ifndef TILESTATE_H
#define TILESTATE_H

#include "State.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();
        
        void LoadAssets();
        void Update(double dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};

#endif