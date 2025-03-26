#pragma once

#include <string>

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

    // Store the path to the user's project folder
    std::string projectFolderPath;
    // Name of the default scene file
    const std::string defaultSceneFilename = "MainScene.json";

    // Helper function to create a "scenes" subfolder if needed
    void EnsureScenesFolderExists(const std::string& projectFolder);
};
