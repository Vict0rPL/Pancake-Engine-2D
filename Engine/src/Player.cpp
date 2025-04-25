#include "Player.h"
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp> 

Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath)
    : SpriteObject(renderer, spriteSheetPath, 32, 32, 4, 0.1f), currentDirection(Direction::None), speed(100.0f)
{
}

void Player::HandleInput(const bool* keyboardState)  // <- tutaj była niezgodność!
{
    currentDirection = Direction::None;

    if (keyboardState[SDL_SCANCODE_W]) currentDirection = Direction::Up;
    else if (keyboardState[SDL_SCANCODE_S]) currentDirection = Direction::Down;
    else if (keyboardState[SDL_SCANCODE_A]) currentDirection = Direction::Left;
    else if (keyboardState[SDL_SCANCODE_D]) currentDirection = Direction::Right;
}

void Player::Update(float deltaTime) {
    if (currentDirection != Direction::None) {
        // animacja działa tylko w ruchu
        SpriteObject::Update(deltaTime);

        float dx = 0.0f, dy = 0.0f;
        switch (currentDirection) {
        case Direction::Up:    dy = -speed * deltaTime; break;
        case Direction::Down:  dy = speed * deltaTime; break;
        case Direction::Left:  dx = -speed * deltaTime; break;
        case Direction::Right: dx = speed * deltaTime; break;
        default: break;
        }
        switch (currentDirection) {
        case Direction::Up:    directionRow = 0; break;
        case Direction::Down:  directionRow = 1; break;
        case Direction::Left:  directionRow = 2; break;
        case Direction::Right: directionRow = 3; break;
        default: directionRow = 0; break;  // kierunek domyślny, góra
        }


        dstRect.x += dx;
        dstRect.y += dy;
    }
    else {
        currentFrame = 0;  // Reset animacji, jeśli stoi w miejscu
    }
}

nlohmann::json Player::ToJson() const {
    nlohmann::json j;
    j["type"] = "Player";
    j["position"] = { {"x", position.x}, {"y", position.y} };
    j["rotation"] = rotation;
    j["scale"] = { {"x", scale.x}, {"y", scale.y} };
    return j;
}

