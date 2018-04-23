#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Utils.h"

class Player
{
    public:
        Player(SDL_Renderer*, int, int);
        void Idle();
        void walkForward();
        void Render();
        void setAction(std::string);
};

#endif // PLAYER_H
