#pragma once

#include <SDL3/SDL.h>
#include <memory>

class Scene;

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize();
    void Shutdown();

    // Called each frame by the Editor (main loop)
    void Update(float deltaTime);
    void Render();
    void SetActiveScene(std::unique_ptr<Scene> newScene);
    Scene* GetActiveScene() const;

    // Accessors so the Editor can grab the SDL pointers for ImGui initialization
    SDL_Window* GetWindow() const { return window; }
    SDL_Renderer* GetRenderer() const { return renderer; }

    bool IsRunning() const { return isRunning; }
    void Stop() { isRunning = false; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::unique_ptr<Scene> activeScene;

    void ProcessEvents(); //Engine also handles game input
};
