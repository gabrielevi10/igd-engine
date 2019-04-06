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
        Sprite(GameObject&, const std::string&);
        ~Sprite();

        void Open(const std::string&);
        void SetClip(int x, int  y, int w, int h);
        int GetWidth() const;
        int GetHeight() const;
        bool IsOpen() const;
        
        void Update(const float dt);
        void Render();
        void Render(float x, float y);
        bool Is(const std::string&);

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
}; 

#endif