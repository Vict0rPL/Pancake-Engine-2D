#include "EditorUI.h" 
#include "Engine.h" 
#include "PrimitiveRenderer.h" 
#include "Point2D.h" 
#include <imgui.h> 
#include <backends/imgui_impl_sdl3.h> 
#include <backends/imgui_impl_sdlrenderer3.h> 
#include <iostream>

EditorUI::EditorUI(Engine* engine)
    : engineRef(engine), isRunning(true) {
}

EditorUI::~EditorUI() {
    ShutdownImGui();
}

void EditorUI::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    //Initialize ImGui backends using the engine's SDL window/renderer
    ImGui_ImplSDL3_InitForSDLRenderer(engineRef->GetWindow(), engineRef->GetRenderer());
    ImGui_ImplSDLRenderer3_Init(engineRef->GetRenderer());
}

void EditorUI::ShutdownImGui() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::Run() {
    // Example fixed timestep 
    const float fps = 60.0f;
    const float frameDelay = 1000.0f / fps;
    // We'll use a persistent flag to control point drawing.
// (Alternatively, you could make it a member variable of EditorUI.)
    static bool drawPoint = false;

    while (isRunning && engineRef->IsRunning()) {
        Uint32 frameStart = SDL_GetTicks();

        // Process events specifically for ImGui and the Editor.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);

            // Also handle quitting the Editor
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
                engineRef->Stop();
            }
        }

        // Start a new ImGui frame so we can update our UI state.
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        // Draw the Editor UI window.
        ImGui::Begin("Editor UI");
        ImGui::Text("Dear ImGui Editor Window");
        if (ImGui::Button("Stop Engine")) {
            engineRef->Stop();
        }
        // Checkbox to toggle drawing of the point. (later add support to draw based on click)
        ImGui::Checkbox("Draw Point", &drawPoint);
        ImGui::End();

        // Call ImGui::Render to capture the UI state
        ImGui::Render();

        // Update and render the engine scene
        engineRef->Update(1.0f / fps);
        engineRef->Render();

        // If the option is enabled, draw the point
        if (drawPoint) {
            // Create a PrimitiveRenderer using the engine's SDL_Renderer
            PrimitiveRenderer primitiveRenderer(engineRef->GetRenderer());
            // Create a Point2D at a fixed position (200,200) and draw it
            Point2D point(200.0f, 200.0f);
            point.Draw(primitiveRenderer);
        }

        // Render the ImGui overlay (draws the UI window)
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), engineRef->GetRenderer());

        // Present everything to the screen
        SDL_RenderPresent(engineRef->GetRenderer());

        // Frame limiting
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
