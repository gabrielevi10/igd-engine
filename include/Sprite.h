#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"

class Sprite : public Component {
    public:
        Sprite(GameObject&);
        Sprite(const std::string&, GameObject&);
        ~Sprite();

        void Open(const std::string&);
        void SetClip(int x, int  y, int w, int h);
        int GetWidth() const;
        int GetHeight() const;
        bool IsOpen() const;
        
        void Update(const float&);
        void Render();
        bool Is(const std::string&);

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
}; 

#endif