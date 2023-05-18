#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class position
{
public:
    int x, y, angle, state;
    void setPos(const int x, const int y);
};

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool Load(string path);

    int getWidth();
    int getHeight();

    void Render(int x, int y, int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void free();
public:
    SDL_Texture* Texture;
    int tWidth;
    int tHeight;

public:
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static bool quit;
    static bool die;
    static short int score;

    const int SCREEN_WIDTH = 350;
    const int SCREEN_HEIGHT = 625;

    const int TOTAL_PIPE = 4;
    //khoảng cách ống trên và dưới
    const int PIPE_SPACE = 160;
    //khoảng cách 2 ống
    const int PIPE_DISTANCE = 220;
    const int LAND_HEIGHT = 140;
    // bird.png 50x35
    const int BIRD_WIDTH = 50;
    const int BIRD_HEIGHT = 35;
};