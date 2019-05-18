#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <memory>

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
    public:
        Music();
        Music(const std::string& file);
        ~Music();

        void Play(int time = -1);
        void Stop(int msToStop);
        void Open(const std::string& file);
        bool IsOpen() const;

    private:
        std::shared_ptr<Mix_Music> music;
};

#endif