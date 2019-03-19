#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <exception>
#include <stdexcept>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.hpp"

class Game {
	private: // constructor
        Game(std::string, int, int height);

    public: // methods
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
		static Game& GetInstance();
    
    private: // attributes
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer *renderer;
        State* state;
};

#endif