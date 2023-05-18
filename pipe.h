#pragma once

#include "texture.h"
#include <iostream>
#include <vector>

using namespace std;

//vector chứa tọa độ tất cả ống
extern vector<position> posPipe;

class pipe:LTexture
{
private:
    //pos cao nhất pipe bên trên spawn
    const int randMin = -373 + 30;                          //pipe dài 373 pixel
    //pos thấp nhất pipe bên trên spawn
    const int randMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_SPACE - 30;
public:
    bool init();
    void Free();
    void render();
    void update();

    int width() {return getWidth();}
    int height() {return getHeight();}
};