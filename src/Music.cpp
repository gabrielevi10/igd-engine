#include <stdexcept>
#include <iostream>

#include "Music.h"

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop(0);
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if (music != nullptr) {
        if (Mix_PlayMusic(music, times) == -1) {
            throw std::runtime_error("Music Play() failed: " + std::string(Mix_GetError()));
        }
    }
}

void Music::Stop(int msToStop) {
    if (Mix_FadeOutMusic(msToStop) == 0) {
        throw std::runtime_error("Music Stop() failed: " + std::string(Mix_GetError()));
    }
}

void Music::Open(std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw std::runtime_error("Music Open() failed: " + std::string(Mix_GetError()));
    }
}

bool Music::IsOpen() const {
    return music != nullptr;
}