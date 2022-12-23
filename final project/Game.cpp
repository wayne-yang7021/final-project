#include "game.h"
#include <cstring>
#include <string>
#include <time.h>
#include <cmath>
SDL_Texture* background = NULL;
SDL_Texture* background1 = NULL;
SDL_Texture* snowman = NULL;
SDL_Texture* start = NULL;
SDL_Texture* startorg = NULL;
SDL_Texture* board = NULL;
SDL_Texture* over = NULL;
SDL_Texture* cry = NULL;
SDL_Texture* solidTexture = NULL;
SDL_Texture* resta = NULL;
//SDL_Texture* solidTexture = NULL;
SDL_Rect a; 
SDL_Rect restart; 
SDL_Rect bigRestart;
SDL_Rect b;
SDL_Rect c;
//SDL_Rect scoreboard{ 400,0,200,70 };
SDL_Rect* boardrect;
SDL_Rect scoreboard;
SDL_Rect finalscore;
int turn = 9;
int m = 7;
int score = 0;


using namespace std;



Game::Game()
{

}
Game::~Game()
{

}
bool Game::running()
{
	return isRunning;
}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystem Initialised..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "window created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			cout << "Renderer created" << endl;
		}
		isRunning = true;

		const char* pic = new char[100];
		pic = "startPage.png";
		background = setPicture(pic);


		pic = "snowman.png";
		snowman = setPicture(pic);
		pic = "startClick.png";
		start = setPicture(pic);
		pic = "startOnclick.png";
		startorg = setPicture(pic);
		pic = "gamePage.jpg";
		background1 = setPicture(pic);
		pic = "board.jpg";
		board = setPicture(pic);
		pic = "gameover.jpg";
		over = setPicture(pic);
		pic = "cry.png";
		cry = setPicture(pic);
		pic = "restart.png";
		resta = setPicture(pic);
		//a1 = ""
		a = { 0, 480, 100, 150 };
		restart = { 300, 500, 200, 80 };
		bigRestart = { 295, 495, 210 , 90 };
		b = { 60,80,200,200 };
		c = { 55,75,210,210 };
		finalscore = { 200,200,200,100 };
		scoreboard = { 450,30,100,50 };
		boardrect = new SDL_Rect[10];
		turn = 9; 
		m = 7;
		score = 0;

		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, start, NULL, NULL);
		render();
	}

	else
	{
		isRunning = false;
	}

}

SDL_Texture* Game::setPicture(const char* a)
{
	SDL_Surface* imageSurface = NULL;
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		cout << "Fail to initialize SDL_image for PNG files: " << IMG_GetError() << endl;
	}

	imageSurface = IMG_Load(a);
	if (imageSurface == NULL)
	{
		cout << "SDL could not load image!! SDL Error: " << SDL_GetError() << endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	return texture;
}

void Game::createScoreBoard(int score)
{
	cout << score << endl;
	TTF_Init();

	TTF_Font* font = TTF_OpenFont("Ayumi-Normal.ttf", 120);

	if (!font)
	{
		SDL_Log("font l	oad failed");
	}

	string a = "score: " + to_string(score);
	const char* scorenum = a.c_str(); //這裡要算分數
	SDL_Surface* solidSurface = TTF_RenderUTF8_Solid(font, scorenum, { 0, 0, 0, 255 });
	solidTexture = SDL_CreateTextureFromSurface(renderer, solidSurface);

	SDL_FreeSurface(solidSurface);
	TTF_CloseFont(font);
	TTF_Quit();

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;


	default:
		break;
	}
}

void Game::setboard()
{
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		boardrect[i].x = rand() % 500;
		boardrect[i].y = 70 * i;
		boardrect[i].w = 100;
		boardrect[i].h = 20;
	}
}


void Game::mouse()
{
	if (crush == false)
	{
	flag1:

		createScoreBoard(score);
		int x = 0, y = 0;
		for (int i = 1; i <= 20; i++)
		{
			a.y -= 20 - 1 * i;
			for (int j = 0; j < 8; j++)
			{
				handleEvents();
				SDL_GetMouseState(&x, &y);
				if (x > 520)
				{
					a.x = 520;
				}
				else {
					a.x = x;
				}
				//cout << x << endl;
				SDL_RenderCopy(renderer, background1, NULL, NULL);
				for (int k = 0; k < 10; k++)
				{
					SDL_RenderCopy(renderer, board, NULL, &boardrect[k]);
				}
				SDL_RenderCopy(renderer, solidTexture, NULL, &scoreboard);
				SDL_RenderCopy(renderer, snowman, NULL, &a);

				SDL_RenderPresent(renderer);

				SDL_Delay(1);
			}
		}
		SDL_Delay(50);


		for (int i = 0; i < 20; i++)
		{
			a.y += 1 * i;
			for (int j = 0; j < 8; j++)
			{
				handleEvents();
				SDL_GetMouseState(&x, &y);
				if (x > 520)
				{
					a.x = 520;
				}
				else {
					a.x = x;
				}

				if (a.x + 50 < boardrect[m].x + 100 && a.x + 50 > boardrect[m].x && abs(a.y + 100 - boardrect[m].y) <= 5)
				{
					score += 2;
					//cout << a.y << endl;
					for (int l = 0; l < 70; l++)
					{
						SDL_RenderCopy(renderer, background1, NULL, NULL);
						handleEvents();
						SDL_GetMouseState(&x, &y);
						if (x > 520)
						{
							a.x = 520;
						}
						else {
							a.x = x;
						}

						for (int k = 0; k < 10; k++)
						{
							boardrect[k].y += 1;
							SDL_RenderCopy(renderer, board, NULL, &boardrect[k]);
						}

						SDL_RenderCopy(renderer, snowman, NULL, &a);
						//createScoreBoard();
						SDL_RenderCopy(renderer, solidTexture, NULL, &scoreboard);

						SDL_RenderPresent(renderer);
					}


					boardrect[turn].x = rand() % 500;
					boardrect[turn].y = 0;
					turn--;
					if (turn == -1)
					{
						turn = 9;
					}

					m--;
					if (m < 0)
					{
						m = 9;
					}

					goto flag1;

				}

				else if (a.y == 395 && (a.x + 50 > boardrect[m].x + 100 || a.x + 50 < boardrect[m].x))
				{
					cout << "game over!" << endl;
					for (int g = 0; g < 300; g++)
					{
						a.y++;
						SDL_RenderCopy(renderer, background1, NULL, NULL);
						for (int k = 0; k < 10; k++)
						{
							SDL_RenderCopy(renderer, board, NULL, &boardrect[k]);
						}
						SDL_RenderCopy(renderer, solidTexture, NULL, &scoreboard);
						SDL_RenderCopy(renderer, cry, NULL, &a);
						//createScoreBoard();
						//SDL_RenderCopy(renderer, solidTexture, NULL, &scoreboard);

						SDL_RenderPresent(renderer);
						SDL_Delay(1);
						crush = true;
					}
					
				}

				//cout << x << endl;
				SDL_RenderCopy(renderer, background1, NULL, NULL);
				for (int k = 0; k < 10; k++)
				{
					SDL_RenderCopy(renderer, board, NULL, &boardrect[k]);
				}

				SDL_RenderCopy(renderer, snowman, NULL, &a);
				//createScoreBoard();
				SDL_RenderCopy(renderer, solidTexture, NULL, &scoreboard);

				SDL_RenderPresent(renderer);
				SDL_Delay(1);
			}
		}
	}
}


void Game::startgame()
{
	int temp = 0;
	int x = 0, y = 0;

	while (temp != 1000)
	{
		SDL_GetMouseState(&x, &y);
		SDL_Event event;
		SDL_PollEvent(&event);
		SDL_Point mousedirect;
		mousedirect.x = x;
		mousedirect.y = y;
		cout << mousedirect.x << "," << mousedirect.y << endl;


		if (SDL_PointInRect(&mousedirect, &b))
		{
			SDL_RenderCopy(renderer, background, NULL, NULL);
			SDL_RenderCopy(renderer, start, NULL, &c);
			render();

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				break;
			}
		}

		else
		{
			SDL_RenderCopy(renderer, background, NULL, NULL);
			SDL_RenderCopy(renderer, startorg , NULL, &b);
			render();
		}

		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			break;
		}


	}

}

void Game::gameover()
{
	int x = 0, y = 0;
	while (true)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		SDL_GetMouseState(&x, &y);
		SDL_Point mousedirect;
		mousedirect.x = x;
		mousedirect.y = y;
		cout << mousedirect.x << "," << mousedirect.y << endl;

		if (SDL_PointInRect(&mousedirect, &restart))
		{
			SDL_RenderCopy(renderer, over, NULL, NULL);
			SDL_RenderCopy(renderer, solidTexture, NULL, &finalscore);
			SDL_RenderCopy(renderer, resta, NULL, &bigRestart);
			render();
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				break;
			}
		}
		else
		{
			SDL_RenderCopy(renderer, over, NULL, NULL);
			SDL_RenderCopy(renderer, solidTexture, NULL, &finalscore);
			SDL_RenderCopy(renderer, resta, NULL, &restart);
			render();
		}

		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			break;
		}
	}
}

/*void Game::update()
{
	cnt++;
	cout << cnt << endl;
}*/
void Game::render()
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
/*void Open_Audio()//打開音頻驅動  設置比特率 和 採樣率， 
{
	int audio_rate = 22050;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channel = 2;
	int audio_buffer = 1024;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channel, audio_buffer) != 0)
	{
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
}*/

/*Mix_Music* Load_Musci(char* filename)//加載音樂 filename是音樂的絕對路徑
//至於支持什麼格式與解碼庫有關係。libmad 幾乎支持所有的常見格式 
{
	Mix_Music* music = NULL;
	music = Mix_LoadMUS(");

	if (music == NULL)
	{
		fprintf(stderr, "Unable to load mp3 file: %s\n", Mix_GetError());
	}
	return music;
}*/
void Game::clean()
{
	SDL_RenderClear(renderer);
	SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Clean" << endl;
}

/*bool Game::loadMedia(Mix_Music* gMusic, Mix_Chunk* gEat, Mix_Chunk* gClick, Mix_Chunk* gFly, bool success)
{
	//loadig success flag
	success = true;


	//Load prompt texture
	/*if( !gPromptTexture.loadFromFile( "21_sound_effects_and_music/prompt.png" ) )
	{
		printf( "Failed to load prompt texture!\n" );
		success = false;
	}*/  //這裡有一個啟動音效的按鈕圖片之類的

	//Load music
	/*gMusic = Mix_LoadMUS("background.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}*/

	//Load sound effects
	  //吃到雪花的音效
	/*gEat = Mix_LoadWAV("21_sound_effects_and_music/scratch.wav");
	if (gEat == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//滑鼠的音效
	gClick = Mix_LoadWAV("21_sound_effects_and_music/high.wav");
	if (gClick == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//吃到拐杖糖的音效
	gFly = Mix_LoadWAV("21_sound_effects_and_music/medium.wav");
	if (gFly == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}*/

	//return success;

//}

/*void Game::playMusic()
{
	//The music that will be played
	Mix_Music* gMusic = NULL;

	//The sound effects that will be used
	Mix_Chunk* gEat = NULL;
	Mix_Chunk* gClick = NULL;
	Mix_Chunk* gFly = NULL;
	//auto g;

	//Initialize SDL
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	loadMedia(gMusic, gEat, gClick, gFly, success);

	//Main Loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	SDL_PollEvent(&e);

	//Handle key press
	if (e.type == SDL_KEYDOWN)
	{

		Mix_PlayMusic(gMusic, -1);
		/*switch (e.key.keysym.sym)
		{
			//Play high sound effect
		case SDLK_1: //要改條件
			Mix_PlayChannel(-1, gEat, 0);
			break;

			//Play medium sound effect
		case SDLK_2:
			Mix_PlayChannel(-1, gClick, 0);
			break;

			//Play low sound effect
		case SDLK_3:
			Mix_PlayChannel(-1, gFly, 0);
			break;

			//Play scratch sound effect

		case SDLK_9:
			//If there is no music playing
			if (Mix_PlayingMusic() == 0)
			{
				//Play the music
				Mix_PlayMusic(gMusic, -1);
			}
			//If music is being played
			else
			{
				//If the music is paused
				if (Mix_PausedMusic() == 1)
				{
					//Resume the music
					Mix_ResumeMusic();
				}
				//If the music is playing
				else
				{
					//Pause the music
					Mix_PauseMusic();
				}
			}
			break;

		case SDLK_0:
			//Stop the music
			Mix_HaltMusic();
			break;
		}*/
	//}
//}

