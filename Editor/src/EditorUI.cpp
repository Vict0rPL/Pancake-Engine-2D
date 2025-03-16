#include "EditorUI.h"
#include "Engine.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer.h>
#include <iostream>

EditorUI::EditorUI(Engine* engine)
    : engineRef(engine), isRunning(true) {
}

EditorUI::~EditorUI() {
    ShutdownImGui();
}

void EditorUI::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize ImGui backends using the engine's SDL window/renderer
    ImGui_ImplSDL3_InitForSDLRenderer(engineRef->GetWindow(), engineRef->GetRenderer());
    ImGui_ImplSDLRenderer_Init(engineRef->GetRenderer());
}

void EditorUI::ShutdownImGui() {
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::Run() {
    // Example fixed timestep
    const float fps = 60.0f;
    const float frameDelay = 1000.0f / fps;

    while (isRunning && engineRef->IsRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        // Process events specifically for ImGui
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Let ImGui process the event
            ImGui_ImplSDL3_ProcessEvent(&event);

            // Also handle quitting the Editor
            if (event.type == SDL_EVENT_QUIT) {
                // Stop both the Editor and the Engine
                isRunning = false;
                engineRef->Stop();
            }
        }

        // Update the engine (which might also poll events if you want)
        engineRef->Update(1.0f / fps);

        // Engine does its own SDL rendering (no SDL_RenderPresent call)
        engineRef->Render();

        // Start a new ImGui frame
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui::NewFrame();

        // -------------------------------------------------------------------
        // Draw your Editor UI here
        // -------------------------------------------------------------------
        ImGui::Begin("Editor UI");
        ImGui::Text("Hello from Dear ImGui (Editor)!");
        // Example button that calls an Engine method
        if (ImGui::Button("Stop Engine")) {
            engineRef->Stop();
        }
        ImGui::End();

        // Render the ImGui overlay
        ImGui::Render();
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        // Finally present everything to the screen
        SDL_RenderPresent(engineRef->GetRenderer());

        // Frame limiting
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
