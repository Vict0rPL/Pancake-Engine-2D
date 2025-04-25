// SpriteObject.h
#pragma once
#include "BitmapObject.h"

class SpriteObject : public BitmapObject {
public:
    SpriteObject(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight, int numFrames, float frameDuration);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

protected:
	int currentFrame;

private:
    int frameWidth, frameHeight, numFrames;
    float frameDuration, frameTimer;
};
