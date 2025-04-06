// EditorUI.cpp
#include "EditorUI.h"
#include "Engine.h"
#include "Scene.h"
#include "Point2D.h"
#include "Line.h"
#include "Square.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <iostream>
#include <filesystem> // C++17 or above for std::filesystem


EditorUI::EditorUI(Engine* engine)
    : engineRef(engine), isRunning(true), projectFolderPath(""), waitingForPointClick(false)
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
        SDL_Event event;

        // Process SDL events
        while (SDL_PollEvent(&event)) {
            if (!inGameMode) {
                ImGui_ImplSDL3_ProcessEvent(&event);
            }
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
                engineRef->Stop();
            }

            // Check for a mouse click when waiting for the user to add a point
           // Obsługa kliknięć dla trybów rysowania prymitywów
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Jeśli nie jesteśmy w trybie dodawania, sprawdź istniejący kod (np. dodawanie punktu)
                if (currentDrawMode != DrawMode::None) {
                    pendingPoints.push_back({ mouseX, mouseY });

                    // Dla poszczególnych trybów decydujemy, kiedy mamy wystarczająco punktów:
                    Scene* currentScene = engineRef->GetActiveScene();
                    if (!currentScene) continue;

                    // Przykłady:
                    if (currentDrawMode == DrawMode::Point && pendingPoints.size() == 1) {
                        // Dodaj nowy Point2D
                        currentScene->AddGameObject(std::make_unique<Point2D>(static_cast<float>(mouseX), static_cast<float>(mouseY)));
                        currentDrawMode = DrawMode::None;
                    }
                    else if (currentDrawMode == DrawMode::Line && pendingPoints.size() == 2) {
                        // Utwórz obiekt Line na podstawie dwóch kliknięć
                        Point2D p1(pendingPoints[0].x, pendingPoints[0].y);
                        Point2D p2(pendingPoints[1].x, pendingPoints[1].y);
                        currentScene->AddGameObject(std::make_unique<Line>(p1, p2));
                        currentDrawMode = DrawMode::None;
                    }
                    else if (currentDrawMode == DrawMode::Square && pendingPoints.size() == 1) {
                        // Przykładowo: utwórz kwadrat o stałym rozmiarze, gdzie kliknięty punkt to lewy górny róg
                        int size = 50; // przykładowy rozmiar
                        currentScene->AddGameObject(std::make_unique<Square>(pendingPoints[0].x, pendingPoints[0].y, size));
                        currentDrawMode = DrawMode::None;
                    }
                    else if (currentDrawMode == DrawMode::Circle && pendingPoints.size() == 1) {
                        // Utwórz koło o stałym promieniu, kliknięty punkt to środek
                        int radius = 30;
                        currentScene->AddGameObject(std::make_unique<Circle>(pendingPoints[0].x, pendingPoints[0].y, radius));
                        currentDrawMode = DrawMode::None;
                    }
                    else if (currentDrawMode == DrawMode::Ellipse && pendingPoints.size() == 1) {
                        // Utwórz elipsę o stałych promieniach
                        int rx = 40, ry = 20;
                        currentScene->AddGameObject(std::make_unique<Ellipse>(pendingPoints[0].x, pendingPoints[0].y, rx, ry));
                        currentDrawMode = DrawMode::None;
                    }
                    else if (currentDrawMode == DrawMode::Polygon) {
                        // Dla wielokąta możesz umożliwić zbieranie dowolnej liczby punktów.
                        // Na przykład, jeżeli użytkownik kliknie prawym przyciskiem, zakończ zbieranie i utwórz wielokąt.
                        if (event.button.button == SDL_BUTTON_RIGHT && pendingPoints.size() >= 3) {
                            currentScene->AddGameObject(std::make_unique<Polygon>(pendingPoints));
                            currentDrawMode = DrawMode::None;
                        }
                    }
                }
                else {
                    // Jeśli nie jesteśmy w żadnym trybie – zachowaj dotychczasową logikę (np. dodawanie Point2D)
                    if (waitingForPointClick) {
                        Scene* currentScene = engineRef->GetActiveScene();
                        if (currentScene) {
                            currentScene->AddGameObject(std::make_unique<Point2D>(static_cast<float>(mouseX), static_cast<float>(mouseY)));
                            // Zapisz scenę do JSON, jak wcześniej
                            std::filesystem::path scenePath = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
                            if (!currentScene->SerializeToJson(scenePath.string())) {
                                std::cerr << "Failed to save scene.\n";
                            }
                        }
                        waitingForPointClick = false;
                    }
                }
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
            // store user input in folderBuffer as they type
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

        ImGui::Separator();
        ImGui::Text("Dodaj prymitywy:");
        if (ImGui::Button("Punkt")) {
            currentDrawMode = DrawMode::Point;
            pendingPoints.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Linia")) {
            currentDrawMode = DrawMode::Line;
            pendingPoints.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Kwadrat")) {
            currentDrawMode = DrawMode::Square;
            pendingPoints.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Koło")) {
            currentDrawMode = DrawMode::Circle;
            pendingPoints.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Elipsa")) {
            currentDrawMode = DrawMode::Ellipse;
            pendingPoints.clear();
        }
        if (ImGui::Button("Wielokąt")) {
            currentDrawMode = DrawMode::Polygon;
            pendingPoints.clear();
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
