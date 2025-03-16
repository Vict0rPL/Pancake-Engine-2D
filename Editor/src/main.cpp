#include "Engine.h"
#include "EditorUI.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Engine engine;
    if (!engine.Initialize()) {
        std::cerr << "Engine failed to initialize!\n";
        return -1;
    }

    EditorUI editor(&engine);

    // Basic loop to simulate an "editor"
    bool isRunning = true;
    while (isRunning) {
        // Here you might poll for events, handle input for both engine and editor
        // In a real scenario, you'd separate engine ticks from editor UI rendering
        editor.Render();
        engine.Run(); // Or a specialized update loop for editor mode
        isRunning = false; // For now, just run once. Extend this for a real editor.
    }

    engine.Shutdown();
    return 0;
}
