#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Engine
{
private:
    static Engine *s_Instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_Running;
    Engine()
    {
    }

public:
    static Engine *get_Instance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }
    bool Init();
    void Clean();
    void Quit();

    void Update();
    void Render();
    void Event();
    SDL_Renderer *get_Renderer()
    {
        return renderer;
    }
    bool get_Is_Running()
    {
        return is_Running;
    }
};

class Input
{
private:
    static Input *s_Instance;
    const Uint8 *m_Keystates;
    Input()
    {
    }

public:
    static Input *get_Instance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
    }
    void Listen();
    void KeyDown();
};

#endif