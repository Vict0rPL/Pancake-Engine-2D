/**
 * @file SpriteObject.cpp
 * @brief Implementacja klasy `SpriteObject`, która reprezentuje obiekt wyświetlający animacje sprite'ów.
 *
 * Klasa `SpriteObject` jest odpowiedzialna za animowanie sprite'ów w grze, odtwarzanie ich klatek na podstawie czasu oraz renderowanie odpowiednich części tekstury na ekranie.
 */

#include "SpriteObject.h"

 /**
  * @brief Konstruktor klasy `SpriteObject`.
  *
  * Inicjalizuje obiekt `SpriteObject` na podstawie podanych parametrów. Obiekt ten jest związany z określoną teksturą sprite'a, jego rozmiarami i liczbą klatek animacji.
  *
  * @param renderer Wskaźnik na obiekt SDL_Renderer, który będzie używany do renderowania sprite'a.
  * @param spriteSheetPath Ścieżka do arkusza sprite'ów, który zawiera animację.
  * @param frameWidth Szerokość pojedynczej klatki w sprite'ach.
  * @param frameHeight Wysokość pojedynczej klatki w sprite'ach.
  * @param numFrames Liczba klatek w animacji.
  * @param frameDuration Czas trwania jednej klatki animacji (w sekundach).
  */
SpriteObject::SpriteObject(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight, int numFrames, float frameDuration)
    : BitmapObject("SpriteObject", renderer, spriteSheetPath),
    frameWidth(frameWidth), frameHeight(frameHeight),
    numFrames(numFrames), currentFrame(0),
    frameDuration(frameDuration), frameTimer(0.0f)
{
    dstRect.w = static_cast<float>(frameWidth);
    dstRect.h = static_cast<float>(frameHeight);
}

/**
 * @brief Aktualizuje stan animacji sprite'a.
 *
 * Metoda ta jest odpowiedzialna za przełączanie klatek animacji w zależności od upływającego czasu. Po upływie `frameDuration`, zmienia klatkę na kolejną w cyklu.
 *
 * @param deltaTime Czas, który minął od ostatniej aktualizacji (w sekundach).
 */
void SpriteObject::Update(float deltaTime) {
    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer -= frameDuration;
        currentFrame = (currentFrame + 1) % numFrames;
    }
}

/**
 * @brief Renderuje aktualną klatkę animacji na ekranie.
 *
 * Ta metoda rysuje aktualną klatkę animacji na podstawie tekstury sprite'a. Używa odpowiednich współrzędnych w arkuszu sprite'ów, aby wyświetlić właściwą część tekstury.
 *
 * @param renderer Wskaźnik na obiekt SDL_Renderer, który będzie używany do renderowania sprite'a.
 */
void SpriteObject::Render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_FRect dst = dstRect;
        SDL_FRect src = {
            static_cast<float>(currentFrame * frameWidth),
            static_cast<float>(directionRow * frameHeight),  ///< <-- zmiana tutaj!
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
        SDL_RenderTexture(renderer, texture, &src, &dst);
    }
}
