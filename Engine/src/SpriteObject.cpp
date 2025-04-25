// SpriteObject.cpp
#include "SpriteObject.h"

SpriteObject::SpriteObject(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight, int numFrames, float frameDuration)
    : BitmapObject("SpriteObject", renderer, spriteSheetPath),
    frameWidth(frameWidth), frameHeight(frameHeight),
    numFrames(numFrames), currentFrame(0),
    frameDuration(frameDuration), frameTimer(0.0f)
{
    dstRect.w = static_cast<float>(frameWidth);
    dstRect.h = static_cast<float>(frameHeight);
}

void SpriteObject::Update(float deltaTime) {
    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer -= frameDuration;
        currentFrame = (currentFrame + 1) % numFrames;
    }
}

void SpriteObject::Render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_FRect dst = dstRect;
        SDL_FRect src = { static_cast<float>(currentFrame * frameWidth), 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
        SDL_RenderTexture(renderer, texture, &src, &dst);
    }
}
