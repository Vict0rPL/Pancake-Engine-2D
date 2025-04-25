// BitmapHandler.h
#pragma once
#include <SDL3/SDL.h>
#include <string>

class BitmapHandler {
public:
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);
    static void DestroyTexture(SDL_Texture* texture);
};
