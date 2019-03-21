#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.hpp"

class Game {
	private: // constructor
        Game(std::string, int width, int height);

    public: // methods
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer() const;
        State& GetState() const;
		static Game& GetInstance();
    
    private: // attributes
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer *renderer;
        State* state;
};

#endif