/**
 * @file Game.h
 * @brief Definicja klasy Game reprezentującej główną scenę gry.
 */

#pragma once

#include "Scene.h"

 /**
  * @brief Klasa Game reprezentuje właściwą rozgrywkę, dziedziczy po Scene.
  */
class Game : public Scene {
public:
    /**
     * @brief Konstruktor klasy Game.
     */
    Game();

    /**
     * @brief Destruktor klasy Game.
     */
    ~Game() override;

    /**
     * @brief Ładuje scenę. Wywoływane raz, gdy scena zostaje aktywowana.
     */
    void Load() override;

    /**
     * @brief Aktualizuje stan sceny. Wywoływane w każdej klatce.
     *
     * @param deltaTime Czas (w sekundach) od ostatniej klatki.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Renderuje scenę. Wywoływane w każdej klatce, aby narysować obiekty.
     *
     * @param renderer Wskaźnik na renderer SDL.
     */
    void Render(SDL_Renderer* renderer) override;
};
