#include "Engine.h"
#include "Scene.h"
#include <iostream>

Engine::Engine()
    : isRunning(false), window(nullptr), renderer(nullptr) {
}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create an SDL3 window (API changed slightly from SDL2)
    // For SDL3, signature: SDL_CreateWindow(const char* title, int w, int h, Uint32 flags)
    window = SDL_CreateWindow("Engine Window", 800, 600, 0);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_ShowWindow(window);

    // Create a renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create and load the active scene
    activeScene = std::make_unique<Scene>();
    activeScene->Load();

    isRunning = true;
    return true;
}

void Engine::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Engine::Update(float deltaTime) {
    // If you want the Engine to handle its own events, do it here:
    ProcessEvents();

    // Update the active scene
    if (activeScene) {
        activeScene->Update(deltaTime);
    }
}

void Engine::Render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    // Render the scene
    if (activeScene) {
        activeScene->Render(renderer);
    }
}

// Optional: Engine handles game-specific events
void Engine::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
        // Handle other game-related inputs here
    }
}
