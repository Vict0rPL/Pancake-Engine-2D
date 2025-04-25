// BitmapObject.cpp
#include "BitmapObject.h"
#include "BitmapHandler.h"

BitmapObject::BitmapObject(const std::string& name, SDL_Renderer* renderer, const std::string& filePath)
    : GameObject(name), texture(BitmapHandler::LoadTexture(renderer, filePath)) {
    dstRect = { 100, 100, 64, 64 };  // Domyślna pozycja i rozmiar
}

BitmapObject::~BitmapObject() {
    BitmapHandler::DestroyTexture(texture);
}

void BitmapObject::Render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
    }
}
