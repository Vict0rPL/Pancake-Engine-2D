#include "EditorUI.h"
#include "Engine.h"
#include <iostream>

EditorUI::EditorUI(Engine* engine)
    : engineRef(engine) {
}

EditorUI::~EditorUI() {}

void EditorUI::Render() {
    // In a real editor, you'd use a GUI library to draw windows, panels, etc.
    // For now, you can just stub this out or add your own code to switch engine states.

    // Example "Play" button logic (pseudo-code):
    /*
    if (ImGui::Button("Play")) {
        // Trigger engine to enter play mode or run a game simulation
        // engineRef->StartSimulation();
    }
    */
}
