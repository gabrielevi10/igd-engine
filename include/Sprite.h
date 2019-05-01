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
        void SetScale(double scaleX, double scaleY);
        Vec2 GetScale() const;
        void SetAngle(double angle);
        double GetAngle() const;
        
        void Update(const double dt);
        void Render();
        void Render(double x, double y);
        bool Is(const std::string&) const;
        void Start();

    private:
        SDL_Texture* texture;
        int width, height;
        double angle;
        SDL_Rect clipRect;
        Vec2 scale;
}; 

#endif