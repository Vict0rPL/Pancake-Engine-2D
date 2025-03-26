#include "Engine.h"
#include "Scene.h"
#include <iostream>

Engine::Engine()
    : isRunning(false), window(nullptr), renderer(nullptr), processEventsEnabled(false)
{
}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create an SDL3 window
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
    // Process events only if in game mode
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

void Engine::SetActiveScene(std::unique_ptr<Scene> newScene) {
    activeScene = std::move(newScene);
    if (activeScene) {
        activeScene->Load();
    }
}

Scene* Engine::GetActiveScene() const { return activeScene.get(); }

void Engine::SetProcessEventsEnabled(bool enabled) {
    processEventsEnabled = enabled;
}

// Process events only when in game mode (when processEventsEnabled is true)
void Engine::ProcessEvents() {
    if (!processEventsEnabled) {
        return;
    }
    SDL_PumpEvents(); // Ensure all pending events are pumped into the queue

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            std::cout << "Key Pressed: " << SDL_GetKeyName(event.key.key) << std::endl;
            if (event.key.key == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;

        case SDL_EVENT_KEY_UP:
            std::cout << "Key Released: " << SDL_GetKeyName(event.key.key) << std::endl;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            std::cout << "Mouse Button Down: " << static_cast<int>(event.button.button)
                << " at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            std::cout << "Mouse Button Up: " << static_cast<int>(event.button.button)
                << " at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            std::cout << "Mouse Moved to: (" << event.motion.x << ", " << event.motion.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            std::cout << "Mouse Wheel: x=" << event.wheel.x << " y=" << event.wheel.y << std::endl;
            break;

        default:
            break;
        }
    }
}
