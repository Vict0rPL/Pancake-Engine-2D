#pragma once

class Engine;

class EditorUI {
public:
    EditorUI(Engine* engine);
    ~EditorUI();

    // Renders the editor interface, including the Play button
    void Render();

private:
    Engine* engineRef;
};
