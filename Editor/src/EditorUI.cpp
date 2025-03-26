// EditorUI.cpp
#include "EditorUI.h"
#include "Engine.h"
#include "Scene.h"
#include "Point2D.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <iostream>
#include <filesystem> // C++17 or above for std::filesystem

EditorUI::EditorUI(Engine* engine)
    : engineRef(engine), isRunning(true), projectFolderPath("")
{
}

EditorUI::~EditorUI() {
    ShutdownImGui();
}

void EditorUI::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(engineRef->GetWindow(), engineRef->GetRenderer());
    ImGui_ImplSDLRenderer3_Init(engineRef->GetRenderer());
}

void EditorUI::ShutdownImGui() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

// Helper function to ensure [projectFolder]/scenes exists
void EditorUI::EnsureScenesFolderExists(const std::string& projectFolder) {
    std::filesystem::path scenesPath = std::filesystem::path(projectFolder) / "scenes";
    if (!std::filesystem::exists(scenesPath)) {
        try {
            std::filesystem::create_directories(scenesPath);
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create scenes folder: " << e.what() << std::endl;
        }
    }
}

void EditorUI::Run() {
    const float fps = 60.0f;
    const float frameDelay = 1000.0f / fps;

    bool inGameMode = false;

    // Attempt to load the default scene if a project folder is already set
    // (In practice, you might wait until the user selects a folder.)
    if (!projectFolderPath.empty()) {
        EnsureScenesFolderExists(projectFolderPath);
        std::filesystem::path mainScenePath = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
        if (std::filesystem::exists(mainScenePath)) {
            auto loadedScene = Scene::LoadFromJson(mainScenePath.string());
            engineRef->SetActiveScene(std::move(loadedScene));
        }
    }

    while (isRunning && engineRef->IsRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        

        if (!inGameMode) {
            // Process SDL events
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (!inGameMode) {
                    ImGui_ImplSDL3_ProcessEvent(&event);
                }
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                    engineRef->Stop();
                }
            }

            ImGui_ImplSDL3_NewFrame();
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Editor UI");
            ImGui::Text("Editor Mode Active");

            // Show current project folder
            ImGui::Text("Project Folder: %s", projectFolderPath.empty()
                ? "None selected"
                : projectFolderPath.c_str());

            // Provide a text input to type in the project folder
            static char folderBuffer[256] = "";
            if (ImGui::InputText("Set Project Folder", folderBuffer, IM_ARRAYSIZE(folderBuffer))) {
                // We store user input in folderBuffer as they type
            }

            // Button to confirm project folder
            if (ImGui::Button("Confirm Project Folder")) {
                projectFolderPath = folderBuffer;
                if (!projectFolderPath.empty()) {
                    EnsureScenesFolderExists(projectFolderPath);
                }
            }

            // Stop Engine button
            if (ImGui::Button("Stop Engine")) {
                engineRef->Stop();
            }

            // Add Point to scene and save
            if (ImGui::Button("Add Point")) {
                if (!projectFolderPath.empty()) {
                    // Add a new point to the current scene
                    Scene* currentScene = engineRef->GetActiveScene();
                    if (currentScene) {
                        currentScene->AddGameObject(std::make_unique<Point2D>(200.0f, 200.0f));
                        // Save to JSON in [projectFolder]/scenes/MainScene.json
                        std::filesystem::path scenePath = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
                        if (!currentScene->SerializeToJson(scenePath.string())) {
                            std::cerr << "Failed to save scene.\n";
                        }
                    }
                }
                else {
                    std::cerr << "No project folder set. Cannot add object.\n";
                }
            }

            // Play Game button
            if (ImGui::Button("Play Game")) {
                // Reload the main scene from JSON
                std::filesystem::path scenePath = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
                if (std::filesystem::exists(scenePath)) {
                    auto loadedScene = Scene::LoadFromJson(scenePath.string());
                    engineRef->SetActiveScene(std::move(loadedScene));
                    inGameMode = true;
                    // Enable event processing in game mode:
                    engineRef->SetProcessEventsEnabled(true);
                }
                else {
                    std::cerr << "Scene file not found: " << scenePath.string() << std::endl;
                }
            }

            ImGui::End();
            ImGui::Render();
        }

        // Update and render the active scene
        engineRef->Update(1.0f / fps);
        engineRef->Render();

        if (!inGameMode) {
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), engineRef->GetRenderer());
        }

        SDL_RenderPresent(engineRef->GetRenderer());

        // Frame limiting
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
