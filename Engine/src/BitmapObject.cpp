/**
 * @file BitmapObject.cpp
 * @brief Implementacja klasy `BitmapObject`, reprezentującej obiekt graficzny oparty na tekście bitmapowym (np. sprite).
 *
 * Klasa ta rozszerza `GameObject` i umożliwia ładowanie, renderowanie oraz zarządzanie teksturą obrazu bitmapowego w grze lub aplikacji graficznej.
 * Obiekt `BitmapObject` przechowuje teksturę i może ją renderować w określonym miejscu na ekranie.
 */

#include "BitmapObject.h"
#include "BitmapHandler.h"

 /**
  * @brief Konstruktor klasy BitmapObject.
  *
  * Tworzy obiekt `BitmapObject` i ładuje teksturę z pliku za pomocą `BitmapHandler`.
  * Ustawia również domyślną pozycję i rozmiar obiektu.
  *
  * @param name Nazwa obiektu, dziedziczona po `GameObject`.
  * @param renderer Wskaźnik na renderer SDL, który jest używany do rysowania obiektów.
  * @param filePath Ścieżka do pliku obrazu, który ma zostać załadowany jako tekstura.
  */
BitmapObject::BitmapObject(const std::string& name, SDL_Renderer* renderer, const std::string& filePath)
    : GameObject(name), texture(BitmapHandler::LoadTexture(renderer, filePath)) {
    dstRect = { 100, 100, 64, 64 };  // Domyślna pozycja i rozmiar
}

/**
 * @brief Destruktor klasy BitmapObject.
 *
 * Zwalnia zasoby tekstury za pomocą metody `DestroyTexture` z klasy `BitmapHandler`.
 */
BitmapObject::~BitmapObject() {
    BitmapHandler::DestroyTexture(texture);
}

/**
 * @brief Renderuje obiekt BitmapObject za pomocą `SDL_Renderer`.
 *
 * Funkcja ta rysuje teksturę obiektu na ekranie w zadanej pozycji i rozmiarze,
 * wykorzystując `SDL_Renderer` oraz `SDL_RenderTexture`.
 *
 * @param renderer Wskaźnik do renderera SDL, który jest używany do rysowania obiektów.
 */
void BitmapObject::Render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
    }
}
