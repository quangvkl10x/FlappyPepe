#include "bird.h"
#include <stdio.h>
#include <iostream>

bool bird::init()
{
    posBird.setPos(75, SCREEN_HEIGHT / 2 - 10);
    ahead = 0;
    angle = 0;
    if (Texture == NULL)
    {
        if (Load("res/image/pepe.png")) return true;
    }
    return false;
}

void bird::Free()
{
    free();
}

void bird::render()
{
    Render(posBird.x, posBird.y, angle);
}

void bird::deathFall()
{
    if (posBird.y < SCREEN_HEIGHT - LAND_HEIGHT - BIRD_HEIGHT)
    {
        if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            // x = x0 + v0.t + 1/2.gt^2
            posBird.y = x0 - 7.3 * time + time * time * 0.18;
            time++;
        }
    }
}


//update pos, score, check die
void bird::update(int pipeWidth,int pipeHeight)
{
    if (!die)
    {
        if (time == 0)
        {
            x0 = posBird.y;
            angle = -25;
        }
        else if (angle < 90 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posBird.y = x0 - 7.3 * time + time * time * 0.18;
            time++;
        }


        // va chạm cột
        if ( (posBird.x + getWidth() > posPipe[ahead].x + 5) && (posBird.x + 5 < posPipe[ahead].x + pipeWidth) &&
             (posBird.y + 5 < posPipe[ahead].y + pipeHeight || posBird.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5) )
        {
            die = true;
        }

        //chạm nóc/sàn
        if (posBird.y > SCREEN_HEIGHT - LAND_HEIGHT -  BIRD_HEIGHT - 5 || posBird.y < - 10 )
        {
            die = true;
        }
        
        // vượt qua
        else if (posBird.x > posPipe[ahead].x + pipeWidth/2 )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPE;
            score++;
        }
    }
}