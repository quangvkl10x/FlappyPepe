#pragma once

#include <SDL_mixer.h>
#include <string>
#include "texture.h"

using namespace std;

class sound:LTexture
{
public:
    bool init();
    void Free();

    void playFlap();
    void playDie();

private:
    Mix_Chunk* flap = NULL;
    Mix_Chunk* die = NULL;
    Mix_Chunk* drop = NULL;
};