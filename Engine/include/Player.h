#pragma once
#include "SpriteObject.h"

enum class Direction { None, Up, Down, Left, Right };

class Player : public SpriteObject {
public:
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath);

    void Update(float deltaTime) override;
    void HandleInput(const bool* keyboardState);
    void SetDirection(Direction dir);
    nlohmann::json ToJson() const override;

private:
    Direction currentDirection;
    float speed;
};
