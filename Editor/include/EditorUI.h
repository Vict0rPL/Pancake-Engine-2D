#pragma once

class Engine;

class EditorUI {
public:
    EditorUI(Engine* engine);
    ~EditorUI();

    void InitializeImGui();
    void ShutdownImGui();

    // Main loop function
    void Run();

private:
    Engine* engineRef;
    bool isRunning;
};
