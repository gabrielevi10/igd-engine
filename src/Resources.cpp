#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    if(imageTable.find(file) == imageTable.end()) {
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
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
    std::unordered_map<std::string, SDL_Texture*>::const_iterator img_it;
    for (img_it = imageTable.begin(); img_it != imageTable.end(); img_it++) {
        SDL_DestroyTexture(img_it->second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    if(musicTable.find(file) == musicTable.end()) {
        Mix_Music* music = Mix_LoadMUS(file.c_str());
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
    std::unordered_map<std::string, Mix_Music*>::const_iterator music_it;
    for (music_it = musicTable.begin(); music_it != musicTable.end(); music_it++) {
        Mix_FreeMusic(music_it->second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    if(soundTable.find(file) == soundTable.end()) {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
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
    std::unordered_map<std::string, Mix_Chunk*>::const_iterator sound_it;
    for (sound_it = soundTable.begin(); sound_it != soundTable.end(); sound_it++) {
        Mix_FreeChunk(sound_it->second);
    }
    musicTable.clear();
}