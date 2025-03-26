#pragma once

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "GameObject.h"
#include <SDL3/SDL.h>  // or <SDL.h> depending on your SDL setup

class Scene {
public:
    virtual ~Scene() = default;  // Virtual destructor for polymorphic base

    virtual void Load();                       // Mark as virtual
    virtual void Update(float deltaTime);      // Mark as virtual
    virtual void Render(SDL_Renderer* renderer); // Mark as virtual

    void AddGameObject(std::unique_ptr<GameObject> gameObject);

    bool SerializeToJson(const std::string& filename) const;
    static std::unique_ptr<Scene> LoadFromJson(const std::string& filename);

protected:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
