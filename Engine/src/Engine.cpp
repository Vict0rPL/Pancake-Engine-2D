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
    //Change this to run in play mode only
    window = SDL_CreateWindow("Game", 800, 600, NULL);

    SDL_ShowWindow(window);

    SDL_SetWindowPosition(window,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED);


    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

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

void Engine::Run() {
    const float fps = 60.0f;
    const float frameDelay = 1000.0f / fps;

    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks();

        ProcessEvents();
        Update(1.0f / fps);
        Render();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
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

void Engine::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
        // Handle other inputs/events
    }
}

void Engine::Update(float deltaTime) {
    if (activeScene) {
        activeScene->Update(deltaTime);
    }
}

void Engine::Render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Cornflower blue
    SDL_RenderClear(renderer);

    //if (activeScene) {
    //    activeScene->Render(renderer);
    //}

    // Present to screen
    SDL_RenderPresent(renderer);
}
