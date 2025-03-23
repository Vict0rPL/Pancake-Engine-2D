#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"

class SDL_Renderer;

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Load();
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);

protected:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
