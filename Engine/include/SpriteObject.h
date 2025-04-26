/**
 * @file SpriteObject.h
 * @brief Definicja klasy SpriteObject, która reprezentuje obiekt graficzny (sprite) w grze.
 *
 * Klasa SpriteObject jest rozszerzeniem klasy BitmapObject i służy do animacji obiektów graficznych w grze, wykorzystując arkusze sprite'ów.
 */

#pragma once
#include "BitmapObject.h"

 /**
  * @brief Klasa SpriteObject reprezentująca animowany obiekt sprite'a w grze.
  *
  * Klasa ta rozszerza BitmapObject i dodaje funkcjonalność animacji obiektów za pomocą arkuszy sprite'ów.
  * Umożliwia ona przechowywanie informacji o aktualnej klatce animacji, kierunku (wiersz w arkuszu) oraz zarządzanie czasem trwania animacji.
  */
class SpriteObject : public BitmapObject {
public:
    /**
     * @brief Konstruktor klasy SpriteObject.
     *
     * Konstruktor inicjalizuje obiekt sprite'a z określonym arkuszem sprite'ów i parametrami animacji.
     *
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do renderowania sprite'a.
     * @param spriteSheetPath Ścieżka do pliku arkusza sprite'ów.
     * @param frameWidth Szerokość pojedynczej klatki animacji w arkuszu.
     * @param frameHeight Wysokość pojedynczej klatki animacji w arkuszu.
     * @param numFrames Liczba klatek animacji w jednym wierszu arkusza sprite'ów.
     * @param frameDuration Czas trwania jednej klatki animacji (w sekundach).
     */
    SpriteObject(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight, int numFrames, float frameDuration);

    /**
     * @brief Aktualizuje stan sprite'a na podstawie upływu czasu.
     *
     * Metoda ta jest wywoływana w każdej klatce gry, aby zaktualizować animację sprite'a, w tym przełączenie klatki animacji.
     *
     * @param deltaTime Czas, jaki upłynął od ostatniej klatki (w sekundach).
     */
    void Update(float deltaTime) override;

    /**
     * @brief Renderuje aktualną klatkę animacji na ekranie.
     *
     * Metoda ta rysuje aktualną klatkę animacji sprite'a z arkusza sprite'ów na ekranie, bazując na kierunku i czasie trwania klatki.
     *
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do rysowania.
     */
    void Render(SDL_Renderer* renderer) override;

protected:
    /**
     * @brief Numer aktualnej klatki animacji.
     *
     * Przechowuje numer klatki, która jest obecnie wyświetlana w animacji.
     */
    int currentFrame;

    /**
     * @brief Numer wiersza w arkuszu sprite'ów, który odpowiada aktualnemu kierunkowi.
     *
     * Może być używany do określenia, która część arkusza jest używana dla różnych kierunków (np. górny, dolny, lewy, prawy).
     */
    int directionRow = 0;  // numer wiersza w sprite sheet (dla kierunku)

private:
    /**
     * @brief Szerokość pojedynczej klatki w arkuszu sprite'ów.
     */
    int frameWidth;

    /**
     * @brief Wysokość pojedynczej klatki w arkuszu sprite'ów.
     */
    int frameHeight;

    /**
     * @brief Liczba klatek animacji w jednym wierszu arkusza sprite'ów.
     */
    int numFrames;

    /**
     * @brief Czas trwania jednej klatki animacji (w sekundach).
     */
    float frameDuration;

    /**
     * @brief Timer do śledzenia czasu trwania klatki animacji.
     *
     * Używany do przełączania klatek animacji po upływie odpowiedniego czasu.
     */
    float frameTimer;
};
