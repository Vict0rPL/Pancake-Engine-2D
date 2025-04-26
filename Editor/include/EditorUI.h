#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <tinyfiledialogs.h>
#include "imgui.h"

class Engine;

/**
 * @brief Klasa odpowiedzialna za interfejs użytkownika edytora.
 *
 * Zarządza inicjalizacją, działaniem i zamykaniem interfejsu graficznego
 * przy użyciu ImGui oraz obsługą operacji projektowych (ładowanie, tworzenie projektu).
 */
class EditorUI {
public:
    /**
     * @brief Konstruktor klasy EditorUI.
     *
     * @param engine Wskaźnik na główny silnik gry.
     */
    EditorUI(Engine* engine);

    /**
     * @brief Destruktor klasy EditorUI.
     */
    ~EditorUI();

    /**
     * @brief Inicjalizuje bibliotekę ImGui.
     */
    void InitializeImGui();

    /**
     * @brief Czyści zasoby ImGui.
     */
    void ShutdownImGui();

    /**
     * @brief Główna pętla obsługi interfejsu użytkownika.
     */
    void Run();

private:
    Engine* engineRef; ///< Wskaźnik na główny silnik (Engine).
    bool isRunning; ///< Flaga określająca, czy UI działa.
    bool waitingForPointClick; ///< Czy czekamy na kliknięcie użytkownika (np. dla rysowania punktów).

    /**
     * @brief Dostępne tryby rysowania.
     */
    enum class DrawMode {
        None,    ///< Brak trybu.
        Point,   ///< Rysowanie punktu.
        Line,    ///< Rysowanie linii.
        Square,  ///< Rysowanie kwadratu.
        Circle,  ///< Rysowanie koła.
        Ellipse, ///< Rysowanie elipsy.
        Polygon, ///< Rysowanie wielokąta.
        Fill     ///< Wypełnienie.
    };

    DrawMode currentDrawMode = DrawMode::None; ///< Aktualnie wybrany tryb rysowania.
    ImVec4 fillColor = ImVec4(1, 1, 1, 1); ///< Kolor wypełnienia (domyślnie biały).
    ImVec4 outlineColor = ImVec4(0, 0, 0, 1); ///< Kolor konturu (domyślnie czarny).
    std::vector<SDL_Point> pendingPoints; ///< Punkty oczekujące na przetworzenie (np. przy rysowaniu wielokątów).
    bool hasProject = false; ///< Flaga informująca, czy projekt został załadowany lub utworzony.
    std::string projectFolderPath; ///< Ścieżka do katalogu projektu.
    const std::string defaultSceneFilename = "MainScene.json"; ///< Nazwa domyślnego pliku sceny.

    /**
     * @brief Zapewnia istnienie katalogu "scenes" w projekcie.
     *
     * @param projectFolder Ścieżka do katalogu projektu.
     */
    void EnsureScenesFolderExists(const std::string& projectFolder);

    /**
     * @brief Otwiera okno dialogowe w celu załadowania istniejącego katalogu projektu.
     */
    void LoadProjectFolder();

    /**
     * @brief Otwiera okno dialogowe w celu stworzenia nowego katalogu projektu.
     */
    void CreateNewProjectFolder();
};
