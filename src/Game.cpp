#include <stdexcept>
#include <iostream>
#include <memory>
#include <chrono>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    if (instance != nullptr) {
        throw std::runtime_error("Game can't be instancied more than one time");
    }
    else {
        instance = this;
    }

    int returned_code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (returned_code != 0) {
        throw std::runtime_error("SDL_Init() failed: " + std::string(SDL_GetError()));
    }
    
    returned_code = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (returned_code != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
        throw std::runtime_error("IMG_Init() failed: " + std::string(IMG_GetError()));
    }

    returned_code = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
    if (returned_code != (MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC)) {
        throw std::runtime_error("Mix_Init() failed: " + std::string(Mix_GetError()));
    }

    returned_code = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    if (returned_code != 0) {
        throw std::runtime_error("Mix_OpenAudio() failed: " + std::string(Mix_GetError()));
    }

    returned_code = Mix_AllocateChannels(32);
    if (returned_code != 32) {
        throw std::runtime_error("Mix_AllocateChannels() failed: " + std::string(Mix_GetError()));
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        throw std::runtime_error("SDL_CreateWindow() failed: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error("SDL_CreateRenderer() failed: " + std::string(SDL_GetError()));
    }

    returned_code = TTF_Init();
    if (returned_code != 0) {
        throw std::runtime_error("TTF_Init() failed: " + std::string(TTF_GetError()));
    }

    storedState = nullptr;
}

Game::~Game() {
    if (storedState != nullptr) {
        delete storedState;
    }
    while (!stateStack.empty()) {
        stateStack.pop();
    }
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Gabriel Levi - 16/0006490", 1024, 600);
    }
    return *instance;
}

State& Game::GetCurrentState() const {
    return *stateStack.top().get();
}

SDL_Renderer* Game::GetRenderer() const {
    return renderer;
}

double Game::GetDeltaTime() const {
    return dt;
}

void Game::CalculateDeltaTime() {
    uint32_t aux = frameStart;
    frameStart = SDL_GetTicks();   
    dt = (double)(frameStart - aux)/1000;
}

void Game::Run() {
    if (storedState != nullptr) {
        stateStack.emplace(storedState);
        storedState = nullptr;
    }
    else {
        return;
    }

    stateStack.top()->Start();

    while (!stateStack.top()->QuitRequested() && !stateStack.empty()) {
        if (stateStack.top()->PopRequested()) {
            stateStack.pop();

            Resources::ClearImages();
            Resources::ClearSounds();
            Resources::ClearMusics();
            
            if (!stateStack.empty()) {
                stateStack.top()->Resume();
            }

        }

        if (storedState != nullptr) {
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        CalculateDeltaTime();
        InputManager::GetInstance().Update();

        if (!stateStack.empty()) {
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    while (!stateStack.empty()) {
        stateStack.pop();
    }

    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();
}

void Game::Push(State* state) {
    storedState = state;   
}