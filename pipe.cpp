#include "pipe.h"
#include "stdio.h"

vector<position> posPipe;

bool pipe::init()
{
    //khởi tạo mảng pos với y random
    posPipe.clear();
    for (char i = 0; i < TOTAL_PIPE; i++)
    {
        position temp;
        //spawn ngoài màn hình, mỗi pipe cách nhau PIPE_DISTANCE
        temp.setPos(SCREEN_WIDTH*2 + i * PIPE_DISTANCE, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
    }
    if (Texture == NULL)
    {
        if (Load("res/image/pipe.png")) return true;
    }
    return false;
}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    for (char i = 0; i < TOTAL_PIPE; i++)
    {
        // nếu ống đi vào màn hình
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -width())
        {
            //render ống trên
            Render(posPipe[i].x, posPipe[i].y);
            //render ống dưới
            Render(posPipe[i].x, posPipe[i].y + height() + PIPE_SPACE, 180);
        }
    }
}

void pipe::update()
{
    for (char i = 0; i < TOTAL_PIPE; i++)
    {
        //nếu pipe ra ngoài màn hình sẽ nhảy tọa độ ra sau cùng
        if (posPipe[i].x < -width())
        {
            //random lại y
            posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
            //đặt lại x về cuối
            posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;
        }
        else
        {
            posPipe[i].x -= 3;
        }
    }
}