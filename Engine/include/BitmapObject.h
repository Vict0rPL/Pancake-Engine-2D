/**
 * @file BitmapObject.h
 * @brief Definicja klasy `BitmapObject` reprezentującej obiekt graficzny w postaci tekstury.
 *
 * Plik zawiera definicję klasy `BitmapObject`, która umożliwia renderowanie obiektów na ekranie przy użyciu bitmapy
 * (tekstury) załadowanej z pliku. Klasa ta jest rozszerzeniem klasy `GameObject` i umożliwia wyświetlanie obrazów w grze.
 */

#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
#include <string>

 /**
  * @brief Klasa BitmapObject reprezentuje obiekt gry, który jest wyświetlany za pomocą tekstury (bitmapy).
  *
  * Klasa `BitmapObject` rozszerza klasę `GameObject` i pozwala na ładowanie oraz renderowanie obiektów
  * z plików graficznych (bitmap) w formacie wspieranym przez SDL (np. PNG, BMP).
  *
  * Wykorzystuje ona tekstury, które są wczytywane z pliku i wyświetlane w określonej pozycji na ekranie.
  */
class BitmapObject : public GameObject {
public:
    /**
     * @brief Konstruktor klasy `BitmapObject`.
     *
     * Tworzy obiekt na podstawie podanego nazwy, renderera oraz ścieżki do pliku graficznego (bitmapy).
     *
     * @param name Nazwa obiektu (dla identyfikacji).
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do rysowania obiektu.
     * @param filePath Ścieżka do pliku graficznego, który ma zostać załadowany jako tekstura.
     */
    BitmapObject(const std::string& name, SDL_Renderer* renderer, const std::string& filePath);

    /**
     * @brief Destruktor klasy `BitmapObject`.
     *
     * Usuwa teksturę i zwalnia zasoby używane przez obiekt.
     */
    ~BitmapObject();

    /**
     * @brief Renderuje obiekt na ekranie.
     *
     * Funkcja ta rysuje teksturę obiektu w odpowiednim miejscu na ekranie,
     * używając renderera SDL.
     *
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do renderowania obiektu.
     */
    void Render(SDL_Renderer* renderer) override;

protected:
    SDL_Texture* texture; ///< Tekstura (bitmapa) obiektu.
    SDL_FRect dstRect;    ///< Prostokąt docelowy, określający pozycję i rozmiar obiektu na ekranie.
};
