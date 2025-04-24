#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <tinyfiledialogs.h>

class Engine;

class EditorUI {
public:
    EditorUI(Engine* engine);
    ~EditorUI();

    void InitializeImGui();
    void ShutdownImGui();
    void Run();

private:
    Engine* engineRef;
    bool isRunning;
    bool waitingForPointClick;

    enum class DrawMode {
        None,
        Point,
        Line,
        Square,
        Circle,
        Ellipse,
        Polygon
    };

    DrawMode currentDrawMode = DrawMode::None;
    std::vector<SDL_Point> pendingPoints;
    bool hasProject = false;          // true once we've loaded or created a project
    // Store the path to the user's project folder
    std::string projectFolderPath;
    // Name of the default scene file
    const std::string defaultSceneFilename = "MainScene.json";

    // Helper function to create a "scenes" subfolder if needed
    void EnsureScenesFolderExists(const std::string& projectFolder);

    // Helpers for folder dialogs
    void LoadProjectFolder();
    void CreateNewProjectFolder();
};
