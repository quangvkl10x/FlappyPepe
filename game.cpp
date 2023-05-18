#include "game.h"


game::game()
{
    initGraphic();
	bird.init();
    pipe.init();
    land.init();
    sound.init();
}

game::~game()
{
    bird.Free();
    pipe.Free();
    land.Free();
    sound.Free();
    free();
    releaseGraphic();
}



bool game::initGraphic()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "FlappyPepe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

void game::releaseGraphic()
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//nhận các input QUIT, CLICK, SPACE, ESCAPE
void game::takeInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            Input.Type = input::QUIT;
            quit = true;
        }
		// PLAY input
        else if (event.type == SDL_MOUSEBUTTONDOWN) Input.Type = input::CLICK;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && event.key.repeat == 0) Input.Type = input::SPACE;
		// PAUSE input
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0) Input.Type = input::PAUSE;
    }
}

//display rồi clear renderer
void game::display()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

//render score trên tab Pause và Game Over
void game::renderScoreSmall()
{
	string s = to_string(score);
	char len = s.length();
	LTexture image;

	for (char i = len - 1; i >= 0; i--)
	{
		//load ảnh các số theo score
		char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png");
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png");
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png");
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png");
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png");
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png");
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png");
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png");
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png");
		}
		else
		{
			image.Load("res/number/small/0.png");
		}

		//render các số từ phải qua trái, bắt đầu tại 260x268
		image.Render(260 - image.getWidth() * (len-1-i) - 5 * (len-i-1), 268);
	}
	image.free();
}

//render score trực tiếp
void game::renderScoreLarge()
{
    string s = to_string(score);
	char len = s.length();
	LTexture image;

	for (char i = 0; i < len; i++)
	{
		char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/large/1.png");
		}
		else if (number == 2)
		{
			image.Load("res/number/large/2.png");
		}
		else if (number == 3)
		{
			image.Load("res/number/large/3.png");
		}
		else if (number == 4)
		{
			image.Load("res/number/large/4.png");
		}
		else if (number == 5)
		{
			image.Load("res/number/large/5.png");
		}
		else if (number == 6)
		{
			image.Load("res/number/large/6.png");
		}
		else if (number == 7)
		{
			image.Load("res/number/large/7.png");
		}
		else if (number == 8)
		{
			image.Load("res/number/large/8.png");
		}
		else if (number == 9)
		{
			image.Load("res/number/large/9.png");
		}
		else 
		{
			image.Load("res/number/large/0.png");
		}
		// căn giữa
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len-1) * 10)) / 2 + (i+30) * i, 100);
	}
	image.free();
}

void game::renderBestScore()
{
	ifstream fileIn("res/data/bestScore.txt");
	fileIn >> bestScore; 
	ofstream fileOut("res/data/bestScore.txt", ios::trunc);

	//render best score
	string s = to_string(bestScore);
	char len = s.length();
	LTexture image;

	for (char i = len-1; i >= 0; i--)
	{
		signed char number = s[i] - '0';
		if (number == 1)
		{
			image.Load("res/number/small/1.png");
		}
		else if (number == 2)
		{
			image.Load("res/number/small/2.png");
		}
		else if (number == 3)
		{
			image.Load("res/number/small/3.png");
		}
		else if (number == 4)
		{
			image.Load("res/number/small/4.png");
		}
		else if (number == 5)
		{
			image.Load("res/number/small/5.png");
		}
		else if (number == 6)
		{
			image.Load("res/number/small/6.png");
		}
		else if (number == 7)
		{
			image.Load("res/number/small/7.png");
		}
		else if (number == 8)
		{
			image.Load("res/number/small/8.png");
		}
		else if (number == 9)
		{
			image.Load("res/number/small/9.png");
		}
		else
		{
			image.Load("res/number/small/0.png");
		}
		image.Render(260 - image.getWidth()*(len-i-1) - 5*(len-i-1), 315);
	}
	image.free();

	if (score > bestScore)
	{
		bestScore = score; 
	}
	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void game::renderTutorial()
{
	LTexture image;
	image.Load("res/image/tutorial.png");
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 240);
	image.free();
}

void game::renderBackground()
{
	LTexture image;
	image.Load("res/image/background.png");
	image.Render(0, 0);
	image.free();
}

void game::renderResume()
{
	LTexture image;
	image.Load("res/image/resume.png");
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::renderPause()
{
	LTexture image;
	image.Load("res/image/pause.png");
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::renderPauseTab()
{
	LTexture image;
	image.Load("res/image/pauseTab.png");
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
	image.free();
}


void game::renderGameOver()
{
	LTexture image;
	image.Load("res/image/gameOver.png");
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::renderMedal()
{
	LTexture image;
		
	if (score > 100) image.Load("res/medal/gold.png");
	else if (score > 30 && score <= 100) image.Load("res/medal/silver.png");
	else image.Load("res/medal/bronze.png");
	image.Render(76, 278);

	image.free();
}

void game::renderPlayButton()
{
	LTexture image;
	image.Load("res/image/playButton.png");
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
	image.free();
}

bool game::checkPlayButton()
{
	if (Input.Type == input::SPACE) return true;
	else if (Input.Type == input::CLICK)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60) return true;
	}
	return false;
}

void game::Restart()
{
    die = false;
    score = 0;
    bird.resetTime();
}