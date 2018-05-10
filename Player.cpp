#include "include/Player.h"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#elif __linux__ || _WIN32 || _WIN64
#include <SDL2/SDL_image.h>
#endif
#include <vector>
#include "include/Utils.h"

Utils utils;

Player::Player(SDL_Renderer* c_renderer, std::string spritesheet_file, int x, int y)
{
    this->x = x;
    this->y = y;
    this->renderer = c_renderer;
    this->spritesheet = utils.loadTexture(utils.getResourcePath() + spritesheet_file, renderer);
//    this->spritesheet = utils.loadTexture(utils.getResourcePath() + "Player/spritesheet.png", renderer);
    //SDL_QueryTexture(playerTexture, NULL, NULL, &playerWidth, &playerHeight);
}

void playSprite(SDL_Renderer *renderer, SDL_Texture* spritesheet, int line, int columns, int ch, int cw, int x, int y){

        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 100) % columns;
        int a = sprite * cw;
        int b = line* ch - ch;
        // First is height and then width!
        SDL_Rect srcrect = { a, b, 60, 100 };
        SDL_Rect dstrect = { x, y, ch, cw*2 }; // double it's size because the sprite is pretty small
        SDL_RenderCopy(renderer, spritesheet, &srcrect, &dstrect);
        //utils.logSDLInfo(cout, to_string(x) + ":" + to_string(y));
}

void Player::Render()
{
    if (currentAction == "idle")
        Idle();
    if (currentAction == "walkforward")
        walkForward();
}

void Player::setAction(std::string action)
{
    currentAction = action;
}

void Player::walk_forward(){
	this->currentAction = "walkforward";
}

void Player::idle(){
	this->currentAction = "idle";
}

void Player::Idle()
{
    playSprite(renderer, spritesheet, 1, 5, 100, 60, this->x, this->y);
}

void Player::walkForward()
{
    playSprite(renderer, spritesheet, 2, 8, 64, 64, this->x, this->y);
    this->x++;
}
