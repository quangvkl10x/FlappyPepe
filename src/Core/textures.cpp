#include "Core/textures.h"
#include "Core/engine.h"
#include "SDL2/SDL_image.h"
#include "map"

Textures *Textures::s_Instance = nullptr;
Pillows *Pillows::s_Instance = nullptr;
std::map<Pillow *, bool> checked;
int score = 0;

bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = ((a.x < b.x + b.w) && (a.x + a.w > b.x)) || ((b.x < a.x + a.w) && (b.x + b.w > a.x));
    bool y_overlaps = ((a.y < b.y + b.h) && (a.y + a.h > b.y)) || ((b.y < a.y + a.h) && (b.y + b.h > a.y));
    return (x_overlaps && y_overlaps);
}

void Textures::Init()
{
    SDL_Surface *Surfacer = IMG_Load("src/images/bg.png");
    T_BG = SDL_CreateTextureFromSurface(Engine::get_Instance()->get_Renderer(), Surfacer);
    Surfacer = IMG_Load("src/images/pepe.png");
    T_Pepe = SDL_CreateTextureFromSurface(Engine::get_Instance()->get_Renderer(), Surfacer);
    Surfacer = IMG_Load("src/images/pillow.png");
    T_Pillow = SDL_CreateTextureFromSurface(Engine::get_Instance()->get_Renderer(), Surfacer);
}

void Textures::Render()
{
    SDL_Rect BG_RECT = {0, 0, 850, 478};
    SDL_Rect WD_RECT = {0, 0, 800, 600};
    SDL_RenderCopyEx(Engine::get_Instance()->get_Renderer(), T_BG, &BG_RECT, &WD_RECT, 0, nullptr, SDL_FLIP_NONE);
}

void Pepe::Init()
{
    x = 800 / 2;
    y = 600 / 2;
}

void Pepe::Update()
{
    Uint32 tick = SDL_GetTicks();
    if (tick - prevTick > 15)
    {
        y += JumpValue;
        if (y + 50 >= 600)
            Engine::get_Instance()->Quit();
        if (y <= 0)
            Engine::get_Instance()->Quit();

        SDL_Rect BOX = {x, y, 50, 50};
        for (auto P : Pillows::get_Instance()->List_Pillow)
        {
            SDL_Rect Up = P.first->get_Rect();
            SDL_Rect Down = P.second->get_Rect();
            if (CheckCollision(BOX, Up))
            {
                Engine::get_Instance()->Quit();
            }
            if (CheckCollision(BOX, Down))
            {
                Engine::get_Instance()->Quit();
            }
            if (x <= Up.x + Up.w || checked[P.first])
                continue;
            checked[P.first] = true;
            score++;
        }
    }
    prevTick = tick;
    SDL_Log("%d", score);
    if (stopJumpTime > 0 && tick > stopJumpTime)
    {
        stopJumpTime = 0;
        JumpValue = 5;
    }
}
void Pepe::Render()
{
    SDL_Rect SRC = {0, 0, 618, 618};
    SDL_Rect DES = {x, y, 50, 50};
    SDL_RenderCopyEx(Engine::get_Instance()->get_Renderer(), Textures::get_Instance()->T_Pepe, &SRC, &DES, 0, nullptr, SDL_FLIP_NONE);
}

void Pepe::Jump()
{
    JumpValue = -10;
    Uint32 tick = SDL_GetTicks();
    stopJumpTime = tick + 100;
}

void Pillow::Render(SDL_RendererFlip flip)
{
    SDL_Rect SRC = {0, 0, 361, 817};
    SDL_Rect DES = {x, y, 100, 600};
    SDL_RenderCopyEx(Engine::get_Instance()->get_Renderer(), Textures::get_Instance()->T_Pillow, &SRC, &DES, 0, nullptr, flip);
}

void Pillows::Add()
{
    if (List_Pillow.empty())
    {
        int x = 800;
        int yF = -500 + rand() % 201;
        int yS = yF + 600 + 150;
        List_Pillow.push_back({new Pillow(x, yF), new Pillow(x, yS)});
    }
    auto [top, bot] = List_Pillow.back();
    int x = top->x + 400;
    int yF = -500 + rand() % 201;
    int yS = yF + 600 + 150;
    List_Pillow.push_back({new Pillow(x, yF), new Pillow(x, yS)});
    return;
}
void Pillows::Update()
{
    Uint32 tick = SDL_GetTicks();
    if (tick - prevTick > 15)
    {
        for (auto &P : List_Pillow)
        {
            P.first->x -= 5;
            P.second->x -= 5;
        }
        if (List_Pillow[0].first->x < 0)
        {
            List_Pillow.erase(List_Pillow.begin());
            Add();
        }
        prevTick = tick;
    }
}
void Pillows::Render()
{
    for (auto P : List_Pillow)
    {
        P.first->Render(SDL_FLIP_VERTICAL);
        P.second->Render(SDL_FLIP_NONE);
    }
}
