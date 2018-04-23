#include "include/Utils.h"
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

void Utils::logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}
void Utils::logSDLInfo(std::ostream &os, const std::string &msg){
	os << " info: " << msg << std::endl;
}

SDL_Texture* Utils::loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	if(SDL_SetColorKey( loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 112, 136, 136))) printf("%s", SDL_GetError());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadImage");
	}
	return texture;
}

void Utils::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

std::string Utils::getResourcePath(const std::string &subDir){
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()){
		char *basePath = SDL_GetBasePath();
		if (basePath){
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
