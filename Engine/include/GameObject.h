#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <vector>

struct Vector2 {
    float x, y;
};

class GameObject {
public:
    GameObject(const std::string& name = "GameObject");
    virtual ~GameObject();

    // Base-class virtuals
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    // Transform data
    Vector2 position{ 0.0f, 0.0f };
    float rotation = 0.0f;
    Vector2 scale{ 1.0f, 1.0f };

    // Basic flags
    bool isActive = true;
    std::string name;

};

#endif // GAMEOBJECT_H
