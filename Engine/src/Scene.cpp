// Scene.cpp
#include "Scene.h"
#include "Point2D.h"
#include "Polygon.h"
#include <fstream>
#include <iostream>

void Scene::Load() {
    // initialize default objects here if later needed
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
    file << j.dump(4);  // indent of 4 spaces
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
        std::string type = objJson.value("type", "");

        if (type == "Point2D") {
            float x = objJson.value("x", 0.0f);
            float y = objJson.value("y", 0.0f);
            scene->AddGameObject(std::make_unique<Point2D>(x, y));
        }
        else if (type == "Polygon") {
            std::vector<SDL_Point> points;
            for (auto& pj : objJson["points"]) {
                points.push_back({ pj.value("x", 0), pj.value("y", 0) });
            }
            SDL_Color fillColor{
                objJson["fillColor"].value("r", 255),
                objJson["fillColor"].value("g", 255),
                objJson["fillColor"].value("b", 255),
                objJson["fillColor"].value("a", 255)
            };
            SDL_Color outlineColor{
                objJson["outlineColor"].value("r", 0),
                objJson["outlineColor"].value("g", 0),
                objJson["outlineColor"].value("b", 0),
                objJson["outlineColor"].value("a", 255)
            };
            scene->AddGameObject(std::make_unique<Polygon>(points, fillColor, outlineColor));
        }
        // TODO: Extend for other object types (Line, Square, Circle, Ellipse, etc.)
    }

    return scene;
}
