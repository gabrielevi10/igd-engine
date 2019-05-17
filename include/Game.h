#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <stack>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

class Game {
    private:
        Game(std::string, int width, int height);

    public:
        ~Game();
        
        static Game& GetInstance();
        SDL_Renderer* GetRenderer() const;
        State& GetCurrentState() const;
        
        void Push(State* state);
        void Run();
        double GetDeltaTime() const;
    
    private:
        void CalculateDeltaTime();
        
        uint32_t frameStart;
        double dt;
        static Game* instance;
        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::stack<std::unique_ptr<State>> stateStack;
};

#endif