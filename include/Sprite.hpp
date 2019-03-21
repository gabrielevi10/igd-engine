#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Sprite {
    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int  y, int w, int h);
        void Render(int x, int y);
        int GetWidth() const;
        int GetHeight() const;
        bool IsOpen() const;

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
}; 

#endif