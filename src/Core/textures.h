#ifndef TEXTURES_H
#define TEXTURES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <random>

class Textures
{
private:
    static Textures *s_Instance;
    Textures()
    {
    }

public:
    static Textures *get_Instance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Textures();
    }
    void Init();
    void Clean();

    void Render();
    SDL_Texture *T_Pepe;
    SDL_Texture *T_BG;
    SDL_Texture *T_Pillow;
};

class Pepe
{
private:
    int x, y;
    int JumpValue = 5;
    Uint32 prevTick;
    Uint32 stopJumpTime;

public:
    void Init();
    void Update();
    void Render();
    void Jump();
};

class Pillow
{
private:
    int x, y;
    Pillow(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

public:
    SDL_Rect get_Rect()
    {
        return {x, y, 100, 600};
    }
    void Clean();
    void Quit();

    void Update();
    void Render(SDL_RendererFlip flip);
    void Event();

    friend class Pillows;
};

class Pillows
{
private:
    static Pillows *s_Instance;
    Uint32 prevTick = 0;
    Pillows()
    {
    }

public:
    static Pillows *get_Instance()
    {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Pillows();
    }
    std::vector<std::pair<Pillow *, Pillow *>> List_Pillow;
    void Add();
    void Update();
    void Render();
};

class Timer
{
private:
    static Textures *s_Instace;
    Timer() {}
};
#endif