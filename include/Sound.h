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

        void Play(int times = 1);
        void Stop();
        void Open(const std::string&);
        bool IsOpen() const;
        
        void Update(const float dt);
        void Render();
        bool Is(const std::string&) const;
        void Start();
        
    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif