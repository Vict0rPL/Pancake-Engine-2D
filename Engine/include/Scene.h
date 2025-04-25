#pragma once

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "GameObject.h"
#include <SDL3/SDL.h>  // or <SDL.h> depending on your SDL setup

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Load();
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    void AddGameObject(std::unique_ptr<GameObject> gameObject);

    void MarkForRemoval(GameObject* obj);

    bool SerializeToJson(const std::string& filename) const;
    static std::unique_ptr<Scene> LoadFromJson(const std::string& filename, SDL_Renderer* renderer);

    std::vector<std::unique_ptr<GameObject>>& GetGameObjects() {
        return gameObjects;
    }

    const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const {
        return gameObjects;
    }

    std::vector<GameObject*> objectsToRemove;

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
