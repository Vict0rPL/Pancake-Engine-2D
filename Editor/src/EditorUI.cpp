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
#include "Player.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <iostream>
#include "TransformableObject.h"
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

// Opens a native “select folder” dialog and loads the project
void EditorUI::LoadProjectFolder() {
    const char* path = tinyfd_selectFolderDialog("Select Existing Project Folder", nullptr);
    if (!path) return;

    projectFolderPath = path;
    hasProject = true;

    // make sure <project>/scenes exists
    EnsureScenesFolderExists(projectFolderPath);

    // our main scene JSON
    auto scenePath = std::filesystem::path(projectFolderPath)
        / "scenes"
        / defaultSceneFilename;

    if (std::filesystem::exists(scenePath)) {
        // load it
        auto loaded = Scene::LoadFromJson(scenePath.string(), engineRef->GetRenderer());
        engineRef->SetActiveScene(std::move(loaded));
    }
    else {
        // no scene yet: create an empty one, hook it up and immediately save
        auto newScene = std::make_unique<Scene>();
        engineRef->SetActiveScene(std::move(newScene));
        engineRef->GetActiveScene()->SerializeToJson(scenePath.string());
    }
}


// Opens a native “choose directory” dialog and creates a new project there
void EditorUI::CreateNewProjectFolder() {
    const char* path = tinyfd_selectFolderDialog("Select Where to Create New Project", nullptr);
    if (path) {
        projectFolderPath = path;
        hasProject = true;
        // Create project folder + “scenes” subfolder
        std::filesystem::create_directories(projectFolderPath);
        EnsureScenesFolderExists(projectFolderPath);
        // Initialize an empty scene and save it
        auto scene = std::make_unique<Scene>();
        engineRef->SetActiveScene(std::move(scene));
        auto sceneFile = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
        engineRef->GetActiveScene()->SerializeToJson(sceneFile.string());
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
            auto loadedScene = Scene::LoadFromJson(mainScenePath.string(), engineRef->GetRenderer());
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
                            // Tworzymy kwadrat o stałym rozmiarze, gdzie kliknięty punkt to lewy górny róg
                            int size = 50; // przykładowy rozmiar

                            // Konwersja z ImGui-owego ImVec4 na SDL_Color
                            SDL_Color f = {
                                static_cast<Uint8>(fillColor.x * 255.0f),
                                static_cast<Uint8>(fillColor.y * 255.0f),
                                static_cast<Uint8>(fillColor.z * 255.0f),
                                static_cast<Uint8>(fillColor.w * 255.0f)
                            };
                            SDL_Color o = {
                                static_cast<Uint8>(outlineColor.x * 255.0f),
                                static_cast<Uint8>(outlineColor.y * 255.0f),
                                static_cast<Uint8>(outlineColor.z * 255.0f),
                                static_cast<Uint8>(outlineColor.w * 255.0f)
                            };

                            currentScene->AddGameObject(
                                std::make_unique<Square>(
                                    pendingPoints[0].x,
                                    pendingPoints[0].y,
                                    size,
                                    f,
                                    o
                                )
                            );

                            currentDrawMode = DrawMode::None;
                        }

                        else if (currentDrawMode == DrawMode::Circle && pendingPoints.size() == 1) {
                            // Utwórz koło o stałym promieniu, kliknięty punkt to środek
                            int radius = 30;

                            // Konwersja ImVec4 → SDL_Color
                            SDL_Color f = {
                                static_cast<Uint8>(fillColor.x * 255.0f),
                                static_cast<Uint8>(fillColor.y * 255.0f),
                                static_cast<Uint8>(fillColor.z * 255.0f),
                                static_cast<Uint8>(fillColor.w * 255.0f)
                            };
                            SDL_Color o = {
                                static_cast<Uint8>(outlineColor.x * 255.0f),
                                static_cast<Uint8>(outlineColor.y * 255.0f),
                                static_cast<Uint8>(outlineColor.z * 255.0f),
                                static_cast<Uint8>(outlineColor.w * 255.0f)
                            };

                            currentScene->AddGameObject(
                                std::make_unique<Circle>(
                                    pendingPoints[0].x,
                                    pendingPoints[0].y,
                                    radius,
                                    f,
                                    o
                                )
                            );
                            currentDrawMode = DrawMode::None;
                        }
                        else if (currentDrawMode == DrawMode::Ellipse && pendingPoints.size() == 1) {
                            // Utwórz elipsę o stałych promieniach
                            int rx = 40, ry = 20;

                            // Konwersja ImVec4 → SDL_Color
                            SDL_Color f = {
                                static_cast<Uint8>(fillColor.x * 255.0f),
                                static_cast<Uint8>(fillColor.y * 255.0f),
                                static_cast<Uint8>(fillColor.z * 255.0f),
                                static_cast<Uint8>(fillColor.w * 255.0f)
                            };
                            SDL_Color o = {
                                static_cast<Uint8>(outlineColor.x * 255.0f),
                                static_cast<Uint8>(outlineColor.y * 255.0f),
                                static_cast<Uint8>(outlineColor.z * 255.0f),
                                static_cast<Uint8>(outlineColor.w * 255.0f)
                            };

                            currentScene->AddGameObject(
                                std::make_unique<Ellipse>(
                                    pendingPoints[0].x,
                                    pendingPoints[0].y,
                                    rx,
                                    ry,
                                    f,
                                    o
                                )
                            );
                            currentDrawMode = DrawMode::None;
                        }

                        else if (currentDrawMode == DrawMode::Polygon) {
                            if (event.button.button == SDL_BUTTON_RIGHT && pendingPoints.size() >= 3) {
                                // convert ImGui fillColor → SDL_Color
                                SDL_Color f = {
                                    static_cast<Uint8>(fillColor.x * 255.0f),
                                    static_cast<Uint8>(fillColor.y * 255.0f),
                                    static_cast<Uint8>(fillColor.z * 255.0f),
                                    static_cast<Uint8>(fillColor.w * 255.0f)
                                };
                                // convert ImGui outlineColor → SDL_Color
                                SDL_Color o = {
                                    static_cast<Uint8>(outlineColor.x * 255.0f),
                                    static_cast<Uint8>(outlineColor.y * 255.0f),
                                    static_cast<Uint8>(outlineColor.z * 255.0f),
                                    static_cast<Uint8>(outlineColor.w * 255.0f)
                                };

                                currentScene->AddGameObject(
                                    std::make_unique<Polygon>(pendingPoints, f, o)
                                );
                                pendingPoints.clear();
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
        }
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Editor UI");
        ImGui::Text("Editor Mode Active");

        if (!hasProject) {
            if (ImGui::Button("Load Project")) {
                LoadProjectFolder();
            }
            ImGui::SameLine();
            if (ImGui::Button("New Project")) {
                CreateNewProjectFolder();
            }
        }
        else {
            ImGui::Text("Project: %s", projectFolderPath.c_str());
            if (ImGui::Button("Unload Project")) {
                hasProject = false;
                projectFolderPath.clear();
            }
        }

        if (hasProject) {
            ImGui::Separator();

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

            ImGui::Separator();
            if (ImGui::Button("Dodaj Playera")) {
                Scene* currentScene = engineRef->GetActiveScene();
                if (currentScene) {
                    currentScene->AddGameObject(
                        std::make_unique<Player>(
                            engineRef->GetRenderer(),
                            "../Engine/assets/pacman.png"  // <-- Ścieżka do sprite sheetu
                        )
                    );
                    std::cout << "Player added to the scene.\n";
                }
            }


            ImGui::Separator();
            // color-picker for fill
            ImGui::ColorEdit4("Fill Color", (float*)&fillColor);
            ImGui::ColorEdit4("Outline Color", (float*)&outlineColor);

            if (ImGui::Button("Fill")) {
                currentDrawMode = DrawMode::Fill;
                pendingPoints.clear();
            }

            ImGui::Separator();

            // --- TRANSFORM PANEL ---
            ImGui::Text("Transforms");

            // grab scene & objects
            auto scene = engineRef->GetActiveScene();
            auto& objs = scene->GetGameObjects();

            // build name list for combo
            static int selectedIndex = 0;
            std::vector<const char*> names;
            for (auto& obj : objs) {
                names.push_back(obj->GetName().c_str());
            }
            if (!names.empty()) {
                ImGui::Combo("Select Object", &selectedIndex,
                    names.data(), (int)names.size());
            }

            // Translate
            static float tx[2] = { 0.0f,0.0f };
            ImGui::InputFloat2("Translate (dx,dy)", tx);
            ImGui::SameLine();
            if (ImGui::Button("Apply Translate") && !names.empty()) {
                auto* gameObj = objs[selectedIndex].get();
                if (auto* t = dynamic_cast<TransformableObject*>(gameObj)) {
                    t->Translate(tx[0], tx[1]);
                }
            }

            // Rotate
            static float angleDeg = 0.0f;
            ImGui::InputFloat("Rotate (deg)", &angleDeg);
            ImGui::SameLine();
            if (ImGui::Button("Apply Rotate") && !names.empty()) {
                float rad = angleDeg * 3.14159265f / 180.0f;
                auto* gameObj = objs[selectedIndex].get();
                if (auto* t = dynamic_cast<TransformableObject*>(gameObj)) {
                    // we pass (0,0) here; each shape’s Rotate() ignores it and uses its own center
                    t->Rotate(rad);
                }
            }


            // Scale
            static float scaleXY[2] = { 1.0f, 1.0f };
            ImGui::InputFloat2("Scale (sx,sy)", scaleXY);
            ImGui::SameLine();
            if (ImGui::Button("Apply Scale") && !names.empty()) {
                auto* gameObj = objs[selectedIndex].get();
                if (auto* t = dynamic_cast<TransformableObject*>(gameObj)) {
                    // again pivot (0,0) is ignored by each shape, which scales around its own center
                    t->Scale(scaleXY[0], scaleXY[1]);
                }
            }


            // --- end TRANSFORM PANEL ---


			ImGui::Separator();

            if (ImGui::Button("Save Scene")) {
                // build the path to MainScene.json
                std::filesystem::path scenePath =
                    std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
                // serialize current scene
                if (engineRef->GetActiveScene()) {
                    if (!engineRef->GetActiveScene()->SerializeToJson(scenePath.string())) {
                        std::cerr << "Failed to save scene to " << scenePath << "\n";
                    }
                }
            }

			ImGui::Separator();

            // Play Game button
            if (ImGui::Button("Play Game")) {
                // Reload the main scene from JSON
                std::filesystem::path scenePath = std::filesystem::path(projectFolderPath) / "scenes" / defaultSceneFilename;
                if (std::filesystem::exists(scenePath)) {
                    auto loadedScene = Scene::LoadFromJson(scenePath.string(), engineRef->GetRenderer());
                    engineRef->SetActiveScene(std::move(loadedScene));
                    inGameMode = true;
                    // Enable event processing in game mode:
                    engineRef->SetProcessEventsEnabled(true);
                }
                else {
                    std::cerr << "Scene file not found: " << scenePath.string() << std::endl;
                }
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
