#include "Player.h"
#include "Square.h"
#include "Circle.h"
#include "Scene.h"
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp> 
#include <algorithm>
#include <iostream>

Player::Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, Scene* scene)
    : SpriteObject(renderer, spriteSheetPath, 32, 32, 4, 0.1f),
    currentDirection(Direction::None),
    speed(100.0f),
    sceneRef(scene)
{
}

void Player::HandleInput(const bool* keyboardState) {
    currentDirection = Direction::None;

    if (keyboardState[SDL_SCANCODE_W]) currentDirection = Direction::Up;
    else if (keyboardState[SDL_SCANCODE_S]) currentDirection = Direction::Down;
    else if (keyboardState[SDL_SCANCODE_A]) currentDirection = Direction::Left;
    else if (keyboardState[SDL_SCANCODE_D]) currentDirection = Direction::Right;
}

void Player::Update(float deltaTime) {
    if (currentDirection != Direction::None) {
        SpriteObject::Update(deltaTime);

        float dx = 0.0f, dy = 0.0f;
        switch (currentDirection) {
        case Direction::Up:    dy = -speed * deltaTime; break;
        case Direction::Down:  dy = speed * deltaTime; break;
        case Direction::Left:  dx = -speed * deltaTime; break;
        case Direction::Right: dx = speed * deltaTime; break;
        default: break;
        }
        directionRow = (currentDirection == Direction::Up) ? 0 :
            (currentDirection == Direction::Down) ? 1 :
            (currentDirection == Direction::Left) ? 2 : 3;

        // Predict next position (future rectangle)
        SDL_FRect futureRect = dstRect;
        futureRect.x += static_cast<int>(dx);
        futureRect.y += static_cast<int>(dy);

        bool canMove = true;

        // Check collision with Squares (block movement)
        for (auto& obj : sceneRef->GetGameObjects()) {
            if (obj->GetName() == "Square") {
                auto* square = dynamic_cast<Square*>(obj.get());
                if (square) {
                    SDL_FRect squareRect = square->GetRect();
                    if (SDL_HasRectIntersectionFloat(&futureRect, &squareRect)) {
                        canMove = false;
                        break;
                    }

                }
            }
        }

        if (canMove) {
            dstRect.x += static_cast<int>(dx);
            dstRect.y += static_cast<int>(dy);
        }

        // Circle collection (remove if player touches)
        sceneRef->GetGameObjects().erase(
            std::remove_if(
                sceneRef->GetGameObjects().begin(),
                sceneRef->GetGameObjects().end(),
                [&](std::unique_ptr<GameObject>& obj) {
                    if (obj->GetName() == "Circle") {
                        auto* circle = dynamic_cast<Circle*>(obj.get());
                        if (circle) {
                            SDL_FRect circleRect = circle->GetRect();
                            if (SDL_HasRectIntersectionFloat(&dstRect, &circleRect)) {
                                std::cout << "Collected a circle!\n";
                                return true;  // remove this circle
                            }
                        }
                    }
                    return false;
                }),
            sceneRef->GetGameObjects().end()
        );

        // Victory condition (no circles left)
        bool circlesRemaining = std::any_of(
            sceneRef->GetGameObjects().begin(),
            sceneRef->GetGameObjects().end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return obj->GetName() == "Circle";
            }
        );

        if (!circlesRemaining) {
            std::cout << "You collected all the circles! You won!" << std::endl;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory!", "You collected all circles!", nullptr);
            exit(0);  // stop game after win
        }
    }
    else {
        currentFrame = 0;  // Stop animation when idle
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
