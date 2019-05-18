#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"


Text::Text(GameObject& associated, const std::string& fontFile, 
            int fontSize, TextStyle style, const std::string& text, SDL_Color color) :
    Component(associated),
    texture(nullptr),
    text(text),
    fontFile(fontFile),
    style(style),
    fontSize(fontSize),
    color(color) {

    RemakeTexture();
}
    
Text::~Text() {}

void Text::Update(double dt) {}

void Text::Render() {
    if (texture != nullptr) {
        SDL_Rect dstrect, clipRect;
        clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};
        dstrect.x = associated.box.x - Camera::pos.x;
        dstrect.y = associated.box.y - Camera::pos.y;
        dstrect.w = (int)associated.box.w;
        dstrect.h = (int)associated.box.h;

        int returned_code = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstrect, 0, nullptr, SDL_FLIP_NONE);
        if (returned_code != 0) {
            throw std::runtime_error("Text Render() failed: " + std::string(SDL_GetError()));
        }
    }
}

bool Text::Is(const std::string& type) const {
    return (type == "Text");
}

void Text::Start() {}

void Text::SetText(const std::string& text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(const std::string& fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        texture = nullptr;
    }
    SDL_Surface* aux;
    font = Resources::GetFont(fontFile, fontSize);
    if (style == SOLID) {
        aux = TTF_RenderText_Solid(font.get(), text.c_str(), color); 
    }
    else if (style == SHADED) {
        aux = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 0});
    }
    else if (style == BLENDED) {
        aux = TTF_RenderText_Blended(font.get(), text.c_str(), color);
    }

    associated.box.w = aux->w;
    associated.box.h = aux->h;
    
    SDL_Texture* t = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), aux);
    texture = std::shared_ptr<SDL_Texture>(t, [](SDL_Texture* ptr) {SDL_DestroyTexture(ptr);});
    SDL_FreeSurface(aux);
}

void Text::NotifyCollision(GameObject& other) {}