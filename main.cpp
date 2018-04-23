/*
 * main.cpp
 *
 *  Created on: 16 Apr 2018
 *      Author: lucianmusat
 */

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "cleanup.h"
#include "include/Player.h"
#include "include/Utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "string"

const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;
const int FRAMERATE = 60;
const int VERSION = 1.0;

int main(int, char**){

    Utils utils;
    const std::string RESOURCE_PATH = utils.getResourcePath();

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
        utils.logSDLInfo(std::cout, "SDL_Init");
		return 1;
	}
    IMG_Init(IMG_INIT_JPG);
	SDL_Window* window = SDL_CreateWindow("Project Framboos", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		utils.logSDLInfo(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		utils.logSDLInfo(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//Temporary background until we build the stage classes.
	struct stat info;

	if(stat(RESOURCE_PATH.c_str(), &info) != 0) {
	    printf("Error: cannot access %s!!\n", RESOURCE_PATH.c_str());
	    return -1;
	}

	SDL_Texture* background = utils.loadTexture(RESOURCE_PATH + "stage2.png", renderer);

	if (background == nullptr){
		cleanup(background, renderer, window);
		SDL_Quit();
		return 1;
	}

    bool quit = false;
	int bW, bH, iW, iH;
	int player_velocity = 10;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);

    SDL_Rect stageBackground;
    stageBackground.x = 0;
    stageBackground.y = 0;
    stageBackground.w = bW;
    stageBackground.h = SCREEN_HEIGHT;

    utils.logSDLInfo(std::cout, "Starting");
    SDL_Event event;
    Player player1(renderer, 100, SCREEN_HEIGHT - 164);


    while( !quit ){
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_q:
                            quit = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RIGHT:
                            player1.setAction("walkforward");
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( event.key.keysym.sym ){
                        case SDLK_RIGHT:
                            player1.setAction("idle");
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
    utils.renderTexture(background, renderer, 0, 0);
    player1.Render();
    SDL_RenderPresent(renderer);
    }

	cleanup(background, renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}



