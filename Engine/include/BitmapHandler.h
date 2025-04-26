/**
 * @file BitmapHandler.h
 * @brief Definicja klasy `BitmapHandler` odpowiedzialnej za ładowanie i usuwanie tekstur.
 *
 * Plik zawiera definicję klasy `BitmapHandler`, która udostępnia funkcje statyczne do ładowania i usuwania tekstur
 * (bitmap) w aplikacjach wykorzystujących SDL.
 */

#pragma once
#include <SDL3/SDL.h>
#include <string>

 /**
  * @brief Klasa `BitmapHandler` zapewnia statyczne metody do ładowania i usuwania tekstur.
  *
  * Klasa ta zawiera funkcje pomocnicze do ładowania tekstur z plików graficznych oraz ich usuwania,
  * co pozwala na zarządzanie zasobami graficznymi w aplikacjach wykorzystujących SDL.
  */
class BitmapHandler {
public:
    /**
     * @brief Ładuje teksturę z pliku.
     *
     * Funkcja wczytuje plik graficzny z podanej ścieżki i konwertuje go do formatu tekstury,
     * którą można następnie wykorzystać do renderowania w aplikacji.
     *
     * @param renderer Wskaźnik do renderera SDL, który będzie używany do tworzenia tekstury.
     * @param filePath Ścieżka do pliku graficznego (np. PNG, BMP), który ma zostać załadowany jako tekstura.
     * @return Wskaźnik na wczytaną teksturę, lub nullptr w przypadku błędu.
     */
    static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath);

    /**
     * @brief Zwalnia zasoby tekstury.
     *
     * Funkcja ta zwalnia pamięć zajmowaną przez teksturę, która nie jest już potrzebna.
     * Należy wywołać ją, aby uniknąć wycieków pamięci.
     *
     * @param texture Wskaźnik na teksturę, która ma zostać usunięta.
     */
    static void DestroyTexture(SDL_Texture* texture);
};
