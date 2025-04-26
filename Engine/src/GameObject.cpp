/**
 * @file GameObject.cpp
 * @brief Implementacja klasy `GameObject`, która stanowi bazę dla wszystkich obiektów w grze.
 *
 * Klasa `GameObject` jest klasą bazową dla wszystkich obiektów w grze. Obejmuje ona podstawową funkcjonalność, taką jak nazwa obiektu,
 * metody do aktualizowania oraz renderowania obiektów. Pozwala na rozszerzenie przez inne klasy, które mogą implementować szczegółową
 * logikę aktualizacji i renderowania.
 */

#include "GameObject.h"
#include <iostream>

 /**
  * @brief Konstruktor klasy `GameObject`.
  *
  * Inicjalizuje nazwę obiektu gry.
  *
  * @param name Nazwa obiektu gry.
  */
GameObject::GameObject(const std::string& name)
    : name(name)
{
}

/**
 * @brief Destruktor klasy `GameObject`.
 *
 * Destruktor klasy `GameObject` jest pusty. Można go rozbudować w przyszłości, jeśli obiekt wymaga zwolnienia zasobów.
 */
GameObject::~GameObject() {
}

/**
 * @brief Aktualizuje stan obiektu gry.
 *
 * Jest to metoda domyślna, która może zostać nadpisana w klasach pochodnych w celu implementacji konkretnej logiki aktualizacji
 * obiektów gry, np. ruchu, interakcji z innymi obiektami, czy detekcji kolizji.
 *
 * @param deltaTime Czas, który upłynął od ostatniej aktualizacji. Może być używane do płynnej animacji.
 */
void GameObject::Update(float deltaTime) {
    // Domyślna aktualizacja
}

/**
 * @brief Renderuje obiekt gry.
 *
 * Jest to metoda domyślna, która może zostać nadpisana w klasach pochodnych w celu implementacji konkretnej logiki renderowania
 * obiektów gry na ekranie.
 *
 * @param renderer Wskaźnik na renderer SDL, który będzie używany do rysowania obiektów gry na ekranie.
 */
void GameObject::Render(SDL_Renderer* /*renderer*/) {
    // Domyślne renderowanie
}
