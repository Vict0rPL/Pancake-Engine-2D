#pragma once

#include <SDL3/SDL.h>

struct Vector2 {
    float x, y;
};

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;

    // Basic transform data
    Vector2 position{ 0.0f, 0.0f };
    float rotation = 0.0f;
    Vector2 scale{ 1.0f, 1.0f };
};
