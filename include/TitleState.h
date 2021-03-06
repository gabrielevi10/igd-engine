#ifndef TILESTATE_H
#define TILESTATE_H

#include "State.h"
#include "Timer.h"

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
    
    private:
        Timer timer;
        bool flag;
};

#endif