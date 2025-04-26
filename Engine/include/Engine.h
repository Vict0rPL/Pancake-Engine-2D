/**
 * @file Engine.h
 * @brief Definicja klasy Engine odpowiadającej za główną pętlę gry i zarządzanie scenami.
 */

#pragma once

#include "Player.h"
#include <SDL3/SDL.h>
#include <memory>

class Scene;

/**
 * @brief Klasa Engine zarządza główną logiką gry: aktualizacją, renderowaniem, obsługą zdarzeń oraz scenami.
 */
class Engine {
public:
    /**
     * @brief Konstruktor klasy Engine.
     */
    Engine();

    /**
     * @brief Destruktor klasy Engine.
     */
    ~Engine();

    /**
     * @brief Inicjalizuje silnik gry (tworzy okno, renderer itd.).
     * @return true jeśli inicjalizacja się powiodła, w przeciwnym wypadku false.
     */
    bool Initialize();

    /**
     * @brief Czyści zasoby i zamyka silnik.
     */
    void Shutdown();

    /**
     * @brief Aktualizuje stan silnika — wywoływane w każdej klatce przez edytor (główną pętlę).
     *
     * @param deltaTime Czas (w sekundach) od ostatniej klatki.
     */
    void Update(float deltaTime);

    /**
     * @brief Renderuje aktualną scenę.
     */
    void Render();

    /**
     * @brief Ustawia aktywną scenę.
     *
     * @param newScene Wskaźnik na nową scenę (przekazywany jako unique_ptr).
     */
    void SetActiveScene(std::unique_ptr<Scene> newScene);

    /**
     * @brief Zwraca wskaźnik do aktualnie aktywnej sceny.
     *
     * @return Wskaźnik do obiektu Scene.
     */
    Scene* GetActiveScene() const;

    /**
     * @brief Zwraca wskaźnik do okna SDL (potrzebne np. do inicjalizacji ImGui).
     *
     * @return Wskaźnik na SDL_Window.
     */
    SDL_Window* GetWindow() const { return window; }

    /**
     * @brief Zwraca wskaźnik do renderera SDL.
     *
     * @return Wskaźnik na SDL_Renderer.
     */
    SDL_Renderer* GetRenderer() const { return renderer; }

    /**
     * @brief Sprawdza, czy silnik jest aktualnie uruchomiony.
     *
     * @return true jeśli silnik działa, false jeśli został zatrzymany.
     */
    bool IsRunning() const { return isRunning; }

    /**
     * @brief Zatrzymuje działanie silnika.
     */
    void Stop() { isRunning = false; }

    /**
     * @brief Ustawia, czy zdarzenia SDL mają być przetwarzane.
     *
     * @param enabled true aby przetwarzać zdarzenia, false aby je ignorować.
     */
    void SetProcessEventsEnabled(bool enabled);

    /**
     * @brief Wyszukuje obiekt gracza w aktywnej scenie.
     */
    void FindPlayer();

private:
    bool isRunning; ///< Flaga określająca czy silnik działa.
    SDL_Window* window; ///< Wskaźnik na okno SDL.
    SDL_Renderer* renderer; ///< Wskaźnik na renderer SDL.
    std::unique_ptr<Scene> activeScene; ///< Aktywna scena gry.
    Player* player = nullptr; ///< Wskaźnik na gracza (raw pointer, nie zarządza pamięcią).

    bool processEventsEnabled; ///< Flaga kontrolująca przetwarzanie zdarzeń SDL.

    /**
     * @brief Przetwarza zdarzenia SDL, wywoływane tylko gdy processEventsEnabled == true.
     */
    void ProcessEvents();
};
