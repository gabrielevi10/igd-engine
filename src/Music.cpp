#include "Music.h"
#include "Resources.h"

#include <stdexcept>
#include <iostream>

Music::Music() : music(nullptr) {}

Music::Music(const std::string& file) : music(nullptr) {
    Open(file);
}

Music::~Music() {}

void Music::Play(int times) {
    if (music != nullptr) {
        if (Mix_PlayMusic(music.get(), times) == -1) {
            throw std::runtime_error("Music Play() failed: " + std::string(Mix_GetError()));
        }
    }
}

void Music::Stop(int msToStop) {
    if (Mix_FadeOutMusic(msToStop) == 0) {
        throw std::runtime_error("Music Stop() failed: " + std::string(Mix_GetError()));
    }
}

void Music::Open(const std::string& file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() const {
    return music != nullptr;
}