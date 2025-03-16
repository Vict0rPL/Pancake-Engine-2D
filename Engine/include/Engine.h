#pragma once

#include <SDL3/SDL.h>
#include <memory>

class Scene;

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize();
    void Run();
    void Shutdown();

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::unique_ptr<Scene> activeScene;

    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
};
