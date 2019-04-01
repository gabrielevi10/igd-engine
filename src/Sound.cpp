#include "Sound.h"

#include <iostream>
#include <stdexcept>

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr) {}

Sound::Sound(GameObject& associatetd, const std::string& file) : Component(associated) {
    Open(file);
}

Sound::~Sound() {
    if (!Mix_Playing(channel)) {
        if (chunk != nullptr) {
            Stop();
            Mix_FreeChunk(chunk);
        }
        else {
            delete chunk;
        }
    }
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel == -1) {
        throw std::runtime_error("Sound Play() failed: " + std::string(Mix_GetError()));
    }
}

void Sound::Stop() {
    if (chunk != nullptr) {
        int returned_code = Mix_HaltChannel(channel);
        if (returned_code != 0) {
            throw std::runtime_error("Sound Stop() failed: " + std::string(Mix_GetError()));
        }
    }
}

void Sound::Open(const std::string& file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        throw std::runtime_error("Sound Open() failed: " + std::string(Mix_GetError()));
    }
}

void Sound::Update(const float& dt) {}

void Sound::Render() {}

bool Sound::Is(const std::string& type) {
    return (type == "Sound");
}