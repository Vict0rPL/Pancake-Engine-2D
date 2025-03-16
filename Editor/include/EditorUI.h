#pragma once

class Engine;

class EditorUI {
public:
    EditorUI(Engine* engine);
    ~EditorUI();

    void InitializeImGui();
    void ShutdownImGui();

    // Main loop function (or you can put this in main.cpp)
    void Run();

private:
    Engine* engineRef;
    bool isRunning;
};
