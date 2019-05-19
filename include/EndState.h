#ifndef ENDSTATE_H
#define  ENDSTATE_H

#include "State.h"
#include "Music.h"
#include "Timer.h"

class EndState : public State {
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update(double dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        Music backgroundMusic;
        Timer timer;
        bool flag;
};

#endif