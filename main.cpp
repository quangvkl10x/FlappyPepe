#include "game.h"
#include "texture.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

//set limit FPS
const short int FPS = 60;
const short int frameDelay = 1000 / FPS;


int main(int argc, char** argv)
{
    Uint32 frameStartTime;
    Uint32 frameEndTime;

    game game;
    bool isGameOverMenu = false;
    bool isPause = false;

    while(!game.isQuit())
    {
        frameStartTime = SDL_GetTicks();
        
        if (game.isDie())
        {
            if (isGameOverMenu) game.sound.playDie();

            //vòng lặp game over menu và start menu
            while(game.isDie() && !game.isQuit())
            {
                //default render
                game.renderBackground();
                game.pipe.render();
                game.land.render();
                
                game.takeInput();

                if (isGameOverMenu) //nếu ở game over menu
                {
                    //chim tiếp tục rơi xuống đất
                    game.bird.render();
                    game.bird.deathFall();

                    //render game over menu
                    game.renderGameOver();
                    game.renderMedal();
                    game.renderScoreSmall();
                    game.renderBestScore();
                    game.renderPlayButton();

                    //check replay
                    if (game.Input.Type == game::input::CLICK || game.Input.Type == game::input::SPACE)
                    {
                        if (game.checkPlayButton()) isGameOverMenu = false; //nếu replay thì thoát game over menu -> start menu
                        game.resetInput();
                    }
                }
                else //nếu ở start menu
                {
                    //khởi tạo lại dữ liệu
                    game.pipe.init();
                    game.bird.init();

                    //render start menu
                    game.bird.render();
                    game.renderTutorial();

                    //check start play
                    if (game.Input.Type == game::input::CLICK || game.Input.Type == game::input::SPACE)
                    {
                        game.Restart(); //die = false, thoát vòng lặp start menu
                    }
                    //land luôn chạy trong start menu
                    game.land.update();
                }
                game.display();
            }
        }
        else //PLAYING
        {
            game.renderBackground();
            game.pipe.render();
            game.land.render();
            game.bird.render();
            game.renderScoreLarge();
            
            game.takeInput();

            if (game.Input.Type == game::input::PAUSE)
            {
                isPause = true;
                game.resetInput();
            }

            if (!isPause) //playing
            {
                if (game.Input.Type == game::input::CLICK || game.Input.Type == game::input::SPACE)
                {
                    game.sound.playFlap();
                    game.bird.resetTime(); 
                    game.resetInput();
                }
                game.bird.update(game.getPipeWidth(), game.getPipeHeight());
                game.pipe.update();
                game.land.update();

                if (game.isDie()) isGameOverMenu = true;
            }
            else //pause tab
            {
                //render pause tab
                game.renderPauseTab();
                game.renderScoreSmall();
                game.renderBestScore();
                game.renderPlayButton();

                //check continue
                if (game.Input.Type == game::input::CLICK || game.Input.Type == game::input::SPACE)
                {
                    if (game.checkPlayButton())
                    {
                        isPause = 0;
                    }
                    game.resetInput();
                }
            }
            game.display();
        }

        //Limit FPS
        frameEndTime = SDL_GetTicks();
        if (frameDelay > (frameEndTime-frameStartTime))
            SDL_Delay(frameDelay - (frameEndTime-frameStartTime));
    }
    return 0;
}
