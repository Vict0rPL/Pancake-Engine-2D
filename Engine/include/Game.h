#pragma once

#include "Scene.h"

class Game : public Scene {
public:
    Game();
    ~Game() override;

    void Load() override;                   // Called once when the scene is set active
    void Update(float deltaTime) override;  // Called every frame
    void Render(SDL_Renderer* renderer) override;  // Called every frame to draw
};
