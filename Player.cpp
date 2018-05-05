#include "include/Player.h"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#elif __linux__
#include <SDL2/SDL_image.h>
#endif
#include <vector>
#include "include/Utils.h"

using namespace std;

Utils utils;

int player_x = 0;
int player_y = 0;
string currentAction = "idle";
SDL_Renderer* renderer;
SDL_Texture* spritesheet;

Player::Player(SDL_Renderer* c_renderer, int x, int y)
{
    player_x = x;
    player_y = y;
    renderer = c_renderer;
    spritesheet = utils.loadTexture(utils.getResourcePath() + "Player/spritesheet.png", renderer);
    //SDL_QueryTexture(playerTexture, NULL, NULL, &playerWidth, &playerHeight);
}

void playSprite(SDL_Renderer *renderer, SDL_Texture* spritesheet, int line, int columns, int ch, int cw, int x, int y){

        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 100) % columns;
        int a = sprite * cw;
        int b = line* ch - ch;
        SDL_Rect srcrect = { a, b, 64, 64 };
        SDL_Rect dstrect = { x, y, ch*2, cw*2 }; // double it's size because the sprite is pretty small
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

void Player::setAction(string action)
{
    currentAction = action;
}

void Player::Idle()
{
    playSprite(renderer, spritesheet, 4, 7, 64, 64, player_x, player_y);
}

void Player::walkForward()
{
    playSprite(renderer, spritesheet, 12, 9, 64, 64, player_x, player_y);
    player_x ++;
}
