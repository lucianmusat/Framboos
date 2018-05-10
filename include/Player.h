#pragma once
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#elif __linux__ || _WIN32 || _WIN64
#include <SDL2/SDL_image.h>
#endif
#include "Utils.h"
#include <string>

class Player
{
	int x,y;
	std::string currentAction = "idle";
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;
    void walkForward();
    void Idle();

    public:
        Player(SDL_Renderer*, std::string, int, int);
        void walk_forward();
        void idle();
        void Render();
        void setAction(std::string);
};
