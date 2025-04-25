// BitmapHandler.cpp
#include "BitmapHandler.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

SDL_Texture* BitmapHandler::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

void BitmapHandler::DestroyTexture(SDL_Texture* texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
