// BitmapObject.h
#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
#include <string>

class BitmapObject : public GameObject {
public:
    BitmapObject(const std::string& name, SDL_Renderer* renderer, const std::string& filePath);
    ~BitmapObject();

    void Render(SDL_Renderer* renderer) override;

protected:
    SDL_Texture* texture;
    SDL_FRect dstRect;
};
