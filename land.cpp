#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::init()
{
    posLand.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    if (Texture == NULL)
    {
        if ( Load("res/image/land.png") ) return true;
    }
    return false;
}

void land::Free()
{
    free();
}

void land::render()
{
    // land.png width = screen_width = 350 pixel
    if (posLand.x > 0)
    {
        Render(posLand.x, posLand.y);
    }

    // render 2 land nối nhau
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0)
    {
        Render(posLand.x, posLand.y);
        Render(posLand.x + SCREEN_WIDTH, posLand.y, 0, NULL);
    }
    else // lặp lại tọa độ
    {
        posLand.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        Render(posLand.x, posLand.y);
    }
}

void land::update()
{
    posLand.x -= 3;
}
