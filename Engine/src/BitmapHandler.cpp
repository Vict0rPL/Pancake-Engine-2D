/**
 * @file BitmapHandler.cpp
 * @brief Implementacja klasy `BitmapHandler` do ładowania i usuwania tekstur.
 *
 * Plik zawiera implementację metod klasy `BitmapHandler`, które umożliwiają ładowanie tekstur z plików
 * oraz ich usuwanie, co pozwala na zarządzanie zasobami graficznymi w aplikacjach wykorzystujących bibliotekę SDL.
 */

#include "BitmapHandler.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

 /**
  * @brief Ładuje teksturę z pliku.
  *
  * Ta funkcja wczytuje plik graficzny (np. PNG, JPG) z podanej ścieżki, konwertuje go na teksturę SDL,
  * którą można następnie wykorzystać do renderowania. Jeśli wystąpi błąd, funkcja zwróci nullptr.
  *
  * @param renderer Wskaźnik do renderera SDL, który będzie używany do tworzenia tekstury.
  * @param filePath Ścieżka do pliku graficznego, który ma zostać załadowany jako tekstura.
  * @return Wskaźnik na wczytaną teksturę, lub nullptr w przypadku błędu.
  */
SDL_Texture* BitmapHandler::LoadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    // Ładowanie pliku graficznego do powierzchni SDL
    SDL_Surface* surface = IMG_Load(filePath.c_str());

    // Sprawdzanie, czy udało się załadować obraz
    if (!surface) {
        std::cerr << "Nie udało się załadować bitmapy: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Tworzenie tekstury z powierzchni
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Zwalnianie powierzchni po utworzeniu tekstury
    SDL_DestroySurface(surface);

    return texture;
}

/**
 * @brief Zwalnia teksturę.
 *
 * Funkcja ta usuwa teksturę z pamięci. Należy wywołać ją, gdy tekstura nie jest już potrzebna,
 * aby uniknąć wycieków pamięci.
 *
 * @param texture Wskaźnik na teksturę, która ma zostać usunięta.
 */
void BitmapHandler::DestroyTexture(SDL_Texture* texture) {
    // Sprawdzanie, czy tekstura jest ważna
    if (texture) {
        SDL_DestroyTexture(texture);  // Zwalnianie tekstury
    }
}
