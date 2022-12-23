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
SDL_Rect a; 
SDL_Rect restart; 
SDL_Rect b;
SDL_Rect c;
SDL_Rect scoreboard{ 400,0,200,70 };
SDL_Rect* boardrect;
int turn = 9;
int m = 7;


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

		const char* a1 = new char[100];
		a1 = "startPage.png";
		background = setPicture(a1);


		a1 = "snowman.png";
		snowman = setPicture(a1);
		a1 = "startClick.png";
		start = setPicture(a1);
		a1 = "startOnclick.png";
		startorg = setPicture(a1);
		a1 = "gamePage.jpg";
		background1 = setPicture(a1);
		a1 = "board.jpg";
		board = setPicture(a1);
		a1 = "gameover.jpg";
		over = setPicture(a1);
		a1 = "cry.png";
		cry = setPicture(a1);
		a1 = "restart.png";
		resta = setPicture(a1);
		//a1 = ""
		a = { 0, 480, 100, 150 };
		restart = { 300, 500, 200, 80 };
		b = { 60,80,200,200 };
		c = { 55,75,210,210 };
		boardrect = new SDL_Rect[10];
		turn = 9; 
		m = 7;

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
			SDL_RenderCopy(renderer, resta, NULL, &restart);
			render();
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				break;
			}
		}
		else
		{
			SDL_RenderCopy(renderer, over, NULL, NULL);
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
/*void Open_Audio()//���}���W�X��  �]�m��S�v �M �ļ˲v�A 
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

/*Mix_Music* Load_Musci(char* filename)//�[������ filename�O���֪�������|
//�ܩ�������榡�P�ѽX�w�����Y�Clibmad �X�G����Ҧ����`���榡 
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
	}*/  //�o�̦��@�ӱҰʭ��Ī����s�Ϥ�������

	//Load music
	/*gMusic = Mix_LoadMUS("background.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}*/

	//Load sound effects
	  //�Y�쳷�᪺����
	/*gEat = Mix_LoadWAV("21_sound_effects_and_music/scratch.wav");
	if (gEat == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//�ƹ�������
	gClick = Mix_LoadWAV("21_sound_effects_and_music/high.wav");
	if (gClick == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//�Y�����}������
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
		case SDLK_1: //�n�����
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

