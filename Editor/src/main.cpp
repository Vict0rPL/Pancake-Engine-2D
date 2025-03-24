#include "Engine.h"
#include "EditorUI.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Create the engine
    Engine engine;
    if (!engine.Initialize()) {
        std::cerr << "Engine failed to initialize!\n";
        return -1;
    }

    // Create the editor, pass the engine pointer
    EditorUI editor(&engine);
    editor.InitializeImGui();

    // Run the editor loop (updates and renders the engine)
    editor.Run();

    // Cleanup
    engine.Shutdown();
    return 0;
}
