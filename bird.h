#pragma once

#include "texture.h"
#include "pipe.h"

using namespace std;

class bird:LTexture
{
public:
    bool init();
    void render();
    void Free();

    void resetTime() {time = 0;}
    void deathFall();

    void update(int pipeWidth, int pipeHeight);
private:
    int angle, time;
    int x0;
    int ahead = 0; // chỉ số của cột trước mặt
    position posBird;
};