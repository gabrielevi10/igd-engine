#ifndef SOUND_HPP
#define SOUND_HPP

#include "Component.h"

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Sound : public Component {
    public:
        Sound(GameObject&);
        Sound(GameObject&, const std::string&);
        ~Sound();

        void Play(int);
        void Stop();
        void Open(const std::string&);
        bool IsOpen() const;
        
        void Update(const float&);
        void Render();
        bool Is(const std::string&);

    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif