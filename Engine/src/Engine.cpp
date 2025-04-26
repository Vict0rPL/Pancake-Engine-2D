/**
 * @file Engine.cpp
 * @brief Implementacja silnika gry `Engine`, odpowiedzialnego za inicjalizację, aktualizację, renderowanie i zarządzanie sceną.
 *
 * Klasa `Engine` pełni rolę głównego silnika gry, zarządzając procesem gry, renderowaniem i obsługą zdarzeń.
 * Odpowiada również za inicjalizację SDL, zarządzanie oknem oraz rendererem, a także za przechowywanie aktywnej sceny.
 */

#include "Engine.h"
#include "Scene.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

 /**
  * @brief Konstruktor klasy `Engine`.
  *
  * Inicjalizuje wszystkie człony klasy `Engine`, ustawiając stan gry na "nieuruchomiona".
  *
  * @note Domyślnie wszystkie wskaźniki są ustawione na `nullptr`, a flaga `processEventsEnabled` jest ustawiona na `false`.
  */
Engine::Engine()
    : isRunning(false), window(nullptr), renderer(nullptr), processEventsEnabled(false)
{
}

/**
 * @brief Destruktor klasy `Engine`.
 *
 * Zamyka i zwalnia zasoby silnika gry (okno, renderer), a następnie kończy działanie SDL.
 */
Engine::~Engine() {
    Shutdown();
}

/**
 * @brief Inicjalizuje silnik gry.
 *
 * Ta funkcja odpowiada za inicjalizację SDL, utworzenie okna, załadowanie ikony okna, stworzenie renderer'a,
 * oraz załadowanie aktywnej sceny.
 *
 * @return `true` jeśli inicjalizacja przebiegła pomyślnie, `false` w przeciwnym przypadku.
 */
bool Engine::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Tworzenie okna SDL3
    window = SDL_CreateWindow("Pancake Engine", 1000, 800, 0);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Ładowanie ikony okna
    SDL_Surface* iconSurface = SDL_LoadBMP("../Engine/assets/pancake.bmp");
    if (!iconSurface) {
        std::cerr << "Failed to load icon BMP: " << SDL_GetError() << std::endl;
    }
    else {
        SDL_SetWindowIcon(window, iconSurface);
        SDL_DestroySurface(iconSurface);
    }

    // Pokazanie okna
    SDL_ShowWindow(window);

    // Tworzenie renderer'a
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Tworzenie i ładowanie aktywnej sceny
    activeScene = std::make_unique<Scene>();
    activeScene->Load();

    isRunning = true;
    return true;
}

/**
 * @brief Zamyka silnik gry i zwalnia zasoby.
 *
 * Funkcja ta niszczy renderer, okno i kończy działanie SDL.
 */
void Engine::Shutdown() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

/**
 * @brief Aktualizuje stan gry na podstawie upływu czasu.
 *
 * Funkcja ta odpowiada za przetwarzanie zdarzeń, obsługę wejścia od gracza oraz aktualizację stanu aktywnej sceny.
 *
 * @param deltaTime Czas, który upłynął od ostatniej aktualizacji.
 */
void Engine::Update(float deltaTime) {
    // Przetwarzanie zdarzeń tylko w trybie gry
    ProcessEvents();

    const bool* state = SDL_GetKeyboardState(NULL);

    if (player) {
        player->HandleInput(state);
    }

    // Aktualizacja aktywnej sceny
    if (activeScene) {
        activeScene->Update(deltaTime);
    }
}

/**
 * @brief Renderuje zawartość gry na ekranie.
 *
 * Funkcja ta rysuje scenę, czyszcząc ekran przed renderowaniem nowej klatki.
 */
void Engine::Render() {
    // Czyszczenie ekranu
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    // Renderowanie aktywnej sceny
    if (activeScene) {
        activeScene->Render(renderer);
    }
}

/**
 * @brief Ustawia nową aktywną scenę.
 *
 * Funkcja ta ustawia nową scenę, której zasoby są ładowane.
 *
 * @param newScene Wskaźnik na nową scenę, która ma zostać ustawiona jako aktywna.
 */
void Engine::SetActiveScene(std::unique_ptr<Scene> newScene) {
    activeScene = std::move(newScene);
    if (activeScene) {
        activeScene->Load();
    }
}

/**
 * @brief Zwraca wskaźnik do aktywnej sceny.
 *
 * Funkcja ta zwraca wskaźnik na aktualnie aktywną scenę.
 *
 * @return Wskaźnik na obiekt `Scene`, który reprezentuje aktywną scenę.
 */
Scene* Engine::GetActiveScene() const { return activeScene.get(); }

/**
 * @brief Włącza lub wyłącza przetwarzanie zdarzeń.
 *
 * Funkcja ta umożliwia włączenie lub wyłączenie przetwarzania zdarzeń w silniku gry.
 *
 * @param enabled Flaga, która określa, czy przetwarzanie zdarzeń jest włączone.
 */
void Engine::SetProcessEventsEnabled(bool enabled) {
    processEventsEnabled = enabled;
}

/**
 * @brief Przetwarza zdarzenia wejściowe (tylko w trybie gry).
 *
 * Funkcja ta obsługuje zdarzenia takie jak naciśnięcie klawiszy, kliknięcia myszy i inne.
 * Zdarzenia są analizowane i odpowiednie akcje są podejmowane w zależności od typu zdarzenia.
 */
void Engine::ProcessEvents() {
    if (!processEventsEnabled) {
        return;
    }
    SDL_PumpEvents(); // Zapewnienie, że wszystkie zdarzenia zostaną załadowane do kolejki

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            std::cout << "Key Pressed: " << SDL_GetKeyName(event.key.key) << std::endl;
            if (event.key.key == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;

        case SDL_EVENT_KEY_UP:
            std::cout << "Key Released: " << SDL_GetKeyName(event.key.key) << std::endl;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            std::cout << "Mouse Button Down: " << static_cast<int>(event.button.button)
                << " at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            std::cout << "Mouse Button Up: " << static_cast<int>(event.button.button)
                << " at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            std::cout << "Mouse Moved to: (" << event.motion.x << ", " << event.motion.y << ")" << std::endl;
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            std::cout << "Mouse Wheel: x=" << event.wheel.x << " y=" << event.wheel.y << std::endl;
            break;

        default:
            break;
        }
    }
}

/**
 * @brief Szuka obiektu gracza w aktywnej scenie.
 *
 * Funkcja ta przeszukuje wszystkie obiekty w aktywnej scenie i próbuje znaleźć obiekt klasy `Player`.
 * Jeśli obiekt gracza zostanie znaleziony, przypisuje go do zmiennej `player`.
 */
void Engine::FindPlayer() {
    player = nullptr;
    if (activeScene) {
        for (auto& obj : activeScene->GetGameObjects()) {
            if (Player* p = dynamic_cast<Player*>(obj.get())) {
                player = p;
                break;
            }
        }
    }
}
