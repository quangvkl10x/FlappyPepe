#pragma once

#include "texture.h"
#include <vector>

using namespace std;

class land : LTexture
{
public:
    bool init();
    void Free();
    void render();
    void update();

private:
    position posLand;
};