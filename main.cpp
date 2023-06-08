#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include "Core/engine.h"

signed main(int argc, char *argv[])
{
    Engine::get_Instance()->Init();
    while (Engine::get_Instance()->get_Is_Running())
    {
        Engine::get_Instance()->Event();
        Engine::get_Instance()->Update();
        Engine::get_Instance()->Render();
    }
    Engine::get_Instance()->Clean();
    return 0;
}