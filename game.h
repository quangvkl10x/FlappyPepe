#pragma once

#include "bird.h"
#include "pipe.h"
#include "land.h"
#include "sound.h"
#include "texture.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class game:LTexture
{
public:
    struct input
    {
        enum type { QUIT, CLICK, SPACE, NONE, PAUSE};
        type Type;
    };

    input Input;

    bird bird;
    pipe pipe;
    sound sound;
    land land;
public:
    game();

    ~game();

    bool initGraphic();
    void releaseGraphic();

    void takeInput();
    void resetInput() {Input.Type = input::NONE;}

    void display();

    void renderScoreSmall();
    void renderScoreLarge();
    void renderBestScore();
    void renderTutorial();
    void renderBackground();
    void renderResume();
    void renderPause();
    void renderPauseTab();
    void renderGameOver();
    void renderMedal();

    void renderPlayButton();
    bool checkPlayButton();

    void Restart();

    bool isQuit() {return quit;}
    bool isDie() {return die;}

    int getPipeWidth() {return pipe.width();}
    int getPipeHeight() {return pipe.height();}
private: 
    int bestScore;
};