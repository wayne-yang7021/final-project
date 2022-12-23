#pragma once
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    //void update();
    void render();
    void clean();
    void startgame();
    void mouse();
    void setboard();
    SDL_Texture* setPicture(const char* a);
    bool running();
    void gameover();

    //void createScoreBoard();

private:
    int cnt = 0;
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool crush = false;
};