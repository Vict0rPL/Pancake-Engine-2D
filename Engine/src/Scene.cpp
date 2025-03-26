// Scene.cpp
#include "Scene.h"
#include "Point2D.h"  // <-- Include so the compiler knows about Point2D
#include <fstream>
#include <iostream>

void Scene::Load() {
    // Optionally initialize default objects here.
}

void Scene::Update(float deltaTime) {
    for (auto& obj : gameObjects) {
        obj->Update(deltaTime);
    }
}

void Scene::Render(SDL_Renderer* renderer) {
    for (auto& obj : gameObjects) {
        obj->Render(renderer);
    }
}

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

bool Scene::SerializeToJson(const std::string& filename) const {
    nlohmann::json j;
    j["gameObjects"] = nlohmann::json::array();
    for (const auto& obj : gameObjects) {
        j["gameObjects"].push_back(obj->ToJson());
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return false;
    }
    file << j.dump(4);  // Pretty-print with an indent of 4 spaces
    return true;
}

std::unique_ptr<Scene> Scene::LoadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << " for reading.\n";
        return std::make_unique<Scene>();
    }
    nlohmann::json j;
    file >> j;
    auto scene = std::make_unique<Scene>();
    for (auto& objJson : j["gameObjects"]) {
        std::string type = objJson["type"];
        if (type == "Point2D") {
            float x = objJson["x"];
            float y = objJson["y"];
            scene->AddGameObject(std::make_unique<Point2D>(x, y));
        }
        // Extend for other object types...
    }
    return scene;
}
