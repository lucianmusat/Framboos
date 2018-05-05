#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#elif __linux__
#include <SDL2/SDL_image.h>
#endif

class Utils
{
    public:
        void logSDLError(std::ostream &os, const std::string &msg);
        void logSDLInfo(std::ostream &os, const std::string &msg);
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
        std::string getResourcePath(const std::string &subDir = "");
};

#endif // UTILS_H
