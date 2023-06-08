#include "Core/engine.h"
#include "Core/textures.h"

Engine *Engine::s_Instance = nullptr;
Input *Input::s_Instance = nullptr;
Pepe *Player;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) && IMG_Init(IMG_INIT_PNG))
    {
        return false;
    }

    window = SDL_CreateWindow("FlappyPepe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return false;
    Textures::get_Instance()->Init();
    Player = new Pepe();
    Player->Init();
    Pillows::get_Instance()->Add();
    return is_Running = true;
}

void Engine::Clean()
{
    Quit();
    return;
}

void Engine::Quit()
{
    is_Running = false;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return;
}

void Engine::Update()
{
    Pillows::get_Instance()->Update();
    Player->Update();
    return;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 230, 255, 253, 255);
    SDL_RenderClear(renderer);
    Textures::get_Instance()->Render();
    Player->Render();
    Pillows::get_Instance()->Render();
    SDL_RenderPresent(renderer);

    return;
}

void Input::KeyDown()
{
    m_Keystates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Engine::get_Instance()->Quit();
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE)
                Player->Jump();
            break;
        default:
            break;
        }
    }
}

void Engine::Event()
{
    Input::get_Instance()->Listen();
}
