#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool sound::init()
{
    string flap_path = "res/sound/flap.mp3";
    string die_path = "res/sound/die.mp3";

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        flap = Mix_LoadWAV( flap_path.c_str() );
        if ( flap == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        die = Mix_LoadWAV( die_path.c_str() );
        if (die == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(flap);
    flap = NULL;
    Mix_FreeChunk(die);
    die = NULL;

    Mix_Quit();
}

void sound::playFlap()
{
    Mix_PlayChannel(-1, flap, 0);
}

void sound::playDie()
{
    Mix_PlayChannel(-1, die, 0);
}