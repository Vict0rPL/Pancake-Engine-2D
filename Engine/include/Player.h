/**
 * @file Player.h
 * @brief Definicja klasy Player, reprezentującej gracza w grze.
 *
 * Klasa ta dziedziczy po klasie `SpriteObject` i reprezentuje gracza w kontekście gry, umożliwiając poruszanie się, obsługę wejścia z klawiatury i zapis stanu obiektu w formacie JSON.
 */

#pragma once
#include "SpriteObject.h"

class Scene;  ///< Forward declaration klasy Scene, która jest używana w konstruktorze i metodach klasy Player.

/**
 * @enum Direction
 * @brief Enum opisujący możliwe kierunki, w których może poruszać się gracz.
 *
 * Enum zawiera następujące kierunki:
 * - `None` – brak ruchu
 * - `Up` – ruch w górę
 * - `Down` – ruch w dół
 * - `Left` – ruch w lewo
 * - `Right` – ruch w prawo
 */
enum class Direction { None, Up, Down, Left, Right };

/**
 * @brief Klasa Player reprezentująca gracza w grze.
 *
 * Gracz jest obiektem, który posiada sprite i porusza się w odpowiedzi na wejście z klawiatury. Klasa umożliwia zarządzanie ruchem gracza oraz zapisanie jego stanu do formatu JSON.
 */
class Player : public SpriteObject {
public:
    /**
     * @brief Konstruktor klasy Player.
     *
     * Inicjalizuje obiekt gracza z określonym rendererem SDL, ścieżką do arkusza sprite'ów oraz odniesieniem do sceny, w której gracz będzie aktywny.
     *
     * @param renderer Wskaźnik na renderer SDL, używany do rysowania gracza.
     * @param spriteSheetPath Ścieżka do pliku z arkuszem sprite'ów dla gracza.
     * @param scene Wskaźnik na scenę, w której gracz jest umieszczony.
     */
    Player(SDL_Renderer* renderer, const std::string& spriteSheetPath, Scene* scene);

    /**
     * @brief Metoda aktualizująca stan gracza.
     *
     * Zwykle wywoływana na każdą klatkę, w celu zaktualizowania pozycji gracza w oparciu o czas (deltaTime) oraz aktualny kierunek ruchu.
     *
     * @param deltaTime Czas, który upłynął od ostatniej klatki.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Metoda obsługująca wejście z klawiatury.
     *
     * Na podstawie stanu klawiszy gracz może zmieniać swój kierunek ruchu (np. poruszać się w górę, w dół, w lewo lub w prawo).
     *
     * @param keyboardState Tablica stanu klawiszy, zazwyczaj z SDL, która zawiera informacje o tym, które klawisze są naciśnięte.
     */
    void HandleInput(const bool* keyboardState);

    /**
     * @brief Metoda ustawiająca kierunek ruchu gracza.
     *
     * Ustawia kierunek, w którym gracz będzie się poruszał w kolejnych klatkach.
     *
     * @param dir Nowy kierunek, w którym ma poruszać się gracz.
     */
    void SetDirection(Direction dir);

    /**
     * @brief Metoda konwertująca stan gracza do formatu JSON.
     *
     * Umożliwia zapisanie stanu gracza (np. jego pozycji, prędkości, kierunku) w formacie JSON.
     *
     * @return nlohmann::json Reprezentacja obiektu gracza w formacie JSON.
     */
    nlohmann::json ToJson() const override;

private:
    /// Aktualny kierunek ruchu gracza.
    Direction currentDirection;

    /// Prędkość gracza, wpływająca na jego ruch.
    float speed;

    /// Odniesienie do sceny, w której gracz się znajduje.
    Scene* sceneRef;
};

