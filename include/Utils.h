#pragma once
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#elif __linux__ || _WIN32 || _WIN64
#include <SDL2/SDL_image.h>
#endif

class Utils
{
    public:
        void logSDLError(std::ostream &os, const std::string &msg);
        void logSDLInfo(std::ostream &os, const std::string &msg);
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
        std::string getResourcePath(const std::string &subDir = "");
};
