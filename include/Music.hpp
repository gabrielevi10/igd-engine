#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
    public:
        Music();
        Music(std::string file);
        ~Music();

        void Play(int time = -1);
        void Stop(int msToStop);
        void Open(std::string file);
        bool IsOpen() const;

    private:
        Mix_Music* music;
};

#endif