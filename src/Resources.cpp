#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file) {
    if(imageTable.find(file) == imageTable.end()) {
        SDL_Texture* aux = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        
        std::shared_ptr<SDL_Texture> texture(aux, 
            [](SDL_Texture* ptr) { SDL_DestroyTexture(ptr); } ); //LAMBDA FUNC
        
        if (texture == nullptr) {
            throw std::runtime_error("Resources IMG_LoadTexture failed: " + std::string(SDL_GetError()));
        }
        else {
            imageTable[file] = texture;
        }
    }
    return imageTable[file];
}

void Resources::ClearImages() {
    for (auto img_it = imageTable.begin(); img_it != imageTable.end(); img_it++) {
        if (img_it->second.unique()) {
            imageTable.erase(img_it);
        }
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(const std::string& file) {
    if(musicTable.find(file) == musicTable.end()) {
        Mix_Music* aux = Mix_LoadMUS(file.c_str());

        std::shared_ptr<Mix_Music> music(aux, 
            [](Mix_Music* ptr) { Mix_FreeMusic(ptr); } );
        
        if (music == nullptr) {
            throw std::runtime_error("Music Open() failed: " + std::string(Mix_GetError()));
        }
        else {
            musicTable[file] = music;
        }
    }
    return musicTable[file];
}

void Resources::ClearMusics() {
    for (auto music_it = musicTable.begin(); music_it != musicTable.end(); music_it++) {
        if (music_it->second.unique()) {
            musicTable.erase(music_it);
        }
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file) {
    if(soundTable.find(file) == soundTable.end()) {
        Mix_Chunk* aux = Mix_LoadWAV(file.c_str());
        
        std::shared_ptr<Mix_Chunk> chunk(aux, 
            [](Mix_Chunk* ptr) { Mix_FreeChunk(ptr); } );

        if (chunk == nullptr) {
            throw std::runtime_error("Sound Open() failed: " + std::string(Mix_GetError()));
        }
        else {
            soundTable[file] = chunk;
        }
    }
    return soundTable[file];
}

void Resources::ClearSounds() {
    for (auto sound_it = soundTable.begin(); sound_it != soundTable.end(); sound_it++) {
        if (sound_it->second.unique()) {
            soundTable.erase(sound_it);
        }
    } 
}

std::shared_ptr<TTF_Font> Resources::GetFont(const std::string& file, int size) {
    if(fontTable.find(file + std::to_string(size)) == fontTable.end()) {
        TTF_Font* aux = TTF_OpenFont(file.c_str(), size);
        
        std::shared_ptr<TTF_Font> font(aux,
            [](TTF_Font* ptr) { TTF_CloseFont(ptr); } );

        if (font == nullptr) {
            throw std::runtime_error("TTF_OpenFont() failed: " + std::string(TTF_GetError()));
        }
        else {
            fontTable[file + std::to_string(size)] = font;
        }
    }
    return fontTable[file + std::to_string(size)];
}

void Resources::ClearFonts() {
    for (auto font_it = fontTable.begin(); font_it != fontTable.end(); font_it++) {
        if (font_it->second.unique()) {
            fontTable.erase(font_it);
        }
    } 
}