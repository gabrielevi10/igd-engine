#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"

class Sprite : public Component {
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, const std::string& file, int frameCount = 1, double frameTime = 1);
        ~Sprite();

        void Open(const std::string& file);
        void SetClip(int x, int  y, int w, int h);
        int GetWidth() const;
        int GetHeight() const;
        bool IsOpen() const;
        void SetScale(double scaleX, double scaleY);
        Vec2 GetScale() const;
        void SetAngle(double angle);
        double GetAngle() const;
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(double frameTime);

        void Update(const double dt);
        void Render();
        void Render(double x, double y);
        bool Is(const std::string&) const;
        void Start();

    private:
        SDL_Texture* texture;
        int width, height, frameCount, currentFrame;
        double angle, timeElapsed, frameTime;
        SDL_Rect clipRect;
        Vec2 scale;
};

#endif