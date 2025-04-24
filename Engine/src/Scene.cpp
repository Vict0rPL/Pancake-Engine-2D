// Scene.cpp
#include "Scene.h"
#include "Point2D.h"
#include "Line.h"
#include "Square.h"
#include "Circle.h"
#include "Ellipse.h"
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
    file << j.dump(4);
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
        else if (type == "Line") {
            auto& s = objJson["start"];
            auto& e = objJson["end"];
            Point2D p1(s.value("x", 0.0f), s.value("y", 0.0f));
            Point2D p2(e.value("x", 0.0f), e.value("y", 0.0f));
            scene->AddGameObject(std::make_unique<Line>(p1, p2));
        }
        else if (type == "Square") {
            int x = objJson.value("x", 0);
            int y = objJson.value("y", 0);
            int size = objJson.value("size", 0);

            SDL_Color fillColor = {
                objJson["fillColor"].value("r", 255),
                objJson["fillColor"].value("g", 255),
                objJson["fillColor"].value("b", 255),
                objJson["fillColor"].value("a", 255)
            };
            SDL_Color outlineColor = {
                objJson["outlineColor"].value("r", 0),
                objJson["outlineColor"].value("g", 0),
                objJson["outlineColor"].value("b", 0),
                objJson["outlineColor"].value("a", 255)
            };

            scene->AddGameObject(
                std::make_unique<Square>(x, y, size, fillColor, outlineColor)
            );
        }

        else if (type == "Circle") {
            int x = objJson.value("x", 0);
            int y = objJson.value("y", 0);
            int radius = objJson.value("radius", 0);

            SDL_Color fillColor = {
                objJson["fillColor"].value("r", 255),
                objJson["fillColor"].value("g", 255),
                objJson["fillColor"].value("b", 255),
                objJson["fillColor"].value("a", 255)
            };
            SDL_Color outlineColor = {
                objJson["outlineColor"].value("r", 0),
                objJson["outlineColor"].value("g", 0),
                objJson["outlineColor"].value("b", 0),
                objJson["outlineColor"].value("a", 255)
            };

            scene->AddGameObject(
                std::make_unique<Circle>(x, y, radius, fillColor, outlineColor)
            );
        }
        else if (type == "Ellipse") {
            int x = objJson.value("x", 0);
            int y = objJson.value("y", 0);
            int rx = objJson.value("rx", 0);
            int ry = objJson.value("ry", 0);

            SDL_Color fillColor = {
                objJson["fillColor"].value("r", 255),
                objJson["fillColor"].value("g", 255),
                objJson["fillColor"].value("b", 255),
                objJson["fillColor"].value("a", 255)
            };
            SDL_Color outlineColor = {
                objJson["outlineColor"].value("r", 0),
                objJson["outlineColor"].value("g", 0),
                objJson["outlineColor"].value("b", 0),
                objJson["outlineColor"].value("a", 255)
            };

            scene->AddGameObject(
                std::make_unique<Ellipse>(x, y, rx, ry, fillColor, outlineColor)
            );
        }

        else if (type == "Polygon") {
            // 1) read points
            std::vector<SDL_Point> points;
            for (auto& pj : objJson["points"]) {
                points.push_back({ pj.value("x",0), pj.value("y",0) });
            }

            // 2) read fillColor
            SDL_Color fillColor = {
                objJson["fillColor"].value("r",200),
                objJson["fillColor"].value("g",200),
                objJson["fillColor"].value("b",200),
                objJson["fillColor"].value("a",255)
            };
            // 3) read outlineColor
            SDL_Color outlineColor = {
                objJson["outlineColor"].value("r",0),
                objJson["outlineColor"].value("g",0),
                objJson["outlineColor"].value("b",0),
                objJson["outlineColor"].value("a",255)
            };

            // 4) construct with both colors
            scene->AddGameObject(
                std::make_unique<Polygon>(points, fillColor, outlineColor)
            );
        }

        else {
            std::cerr << "Unknown object type in JSON: " << type << "\n";
        }
    }

    return scene;
}
