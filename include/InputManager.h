#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <unordered_map>
#define SDL_ICLUDE
#include "SDL_include.h"

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define SPACE_KEY           SDLK_SPACE
#define A_KEY               SDLK_a
#define D_KEY               SDLK_d
#define S_KEY               SDLK_s
#define W_KEY               SDLK_w

class InputManager {
    private:
        InputManager();
        ~InputManager();

    public:
        void Update();

        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        int GetMouseX() const;
        int GetMouseY() const;

        bool QuitRequested() const;

        static InputManager& GetInstance();
    
    private:
        bool mouseState[6];
        int mouseUpdate[6];

        std::unordered_map<int, bool> keyState; 
        std::unordered_map<int, int> keyUpdate;

        bool quitRequested;

        int updateCounter;

        int mouseX, mouseY;
};

#endif