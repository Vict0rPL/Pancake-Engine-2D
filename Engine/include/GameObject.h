#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <vector>

struct Vector2 {
    float x, y;

    Vector2() = default;
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    Vector2& operator+=(Vector2 const& o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    Vector2  operator+ (Vector2 const& o) const {
        return { x + o.x, y + o.y };
    }

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

    // Pure virtual method to convert a game object to JSON.
    virtual nlohmann::json ToJson() const = 0;

    /// Returns this object’s name
    const std::string& GetName() const { return name; }

};

#endif // GAMEOBJECT_H
