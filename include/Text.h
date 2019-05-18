#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <memory>

class Text : public Component {
    public:
        enum TextStyle {SOLID, SHADED, BLENDED}; 

        Text(GameObject& associated, const std::string& fontFile, 
            int fontSize, TextStyle style, const std::string& text, SDL_Color color);

        ~Text();

        void Update(double dt);
        void Render();
        bool Is(const std::string& type) const;
        void Start();
        void NotifyCollision(GameObject& other);
        
        void SetText(const std::string& text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(const std::string& fontFile);
        void SetFontSize(int fontSize);

    private:
        void RemakeTexture();

        std::shared_ptr<TTF_Font> font;
        std::shared_ptr<SDL_Texture> texture;
        std::string text, fontFile;
        TextStyle style;
        int fontSize;
        SDL_Color color;
};

#endif