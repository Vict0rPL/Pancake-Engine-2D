/**
 * @file Polygon.h
 * @brief Definicja klasy Polygon, reprezentującej wielokąt w przestrzeni 2D.
 * 
 * Klasa ta dziedziczy po klasach `GameObject` i `TransformableObject`, umożliwiając przechowywanie i manipulowanie współrzędnymi wierzchołków wielokąta, rysowanie go oraz transformowanie (przemieszczanie, rotowanie, skalowanie).
 */

#pragma once

#include "GameObject.h"
#include "PrimitiveRenderer.h"
#include "TransformableObject.h"
#include "Transform.h"            // dla Vector2
#include <vector>
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

/**
 * @brief Klasa Polygon reprezentująca wielokąt w przestrzeni 2D.
 * 
 * Klasa ta przechowuje wierzchołki wielokąta, umożliwia jego rysowanie, oraz pozwala na zastosowanie transformacji, takich jak translacja, rotacja i skalowanie.
 * Dodatkowo, klasa ta pozwala na zapisanie obiektu do formatu JSON.
 */
class Polygon : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor klasy Polygon.
     * 
     * Inicjalizuje wielokąt na podstawie wektora punktów (współrzędnych wierzchołków).
     * 
     * @param pts Wektor punktów (SDL_Point), które określają wierzchołki wielokąta.
     * @param fillColor Kolor wypełnienia wielokąta (domyślnie: szary).
     * @param outlineColor Kolor obramowania wielokąta (domyślnie: czarny).
     */
    Polygon(const std::vector<SDL_Point>& pts,
        SDL_Color fillColor = { 200,200,200,255 },
        SDL_Color outlineColor = { 0,0,0,255 });

    /**
     * @brief Rysuje wielokąt za pomocą `PrimitiveRenderer`.
     * 
     * Metoda ta wykorzystuje renderer do narysowania wielokąta w przestrzeni 2D.
     * 
     * @param renderer Renderer używany do rysowania.
     */
    void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Renderuje wielokąt na ekranie przy użyciu SDL.
     * 
     * Ta metoda wywołuje funkcje renderujące SDL, aby wyświetlić wielokąt na ekranie.
     * 
     * @param renderer Renderer SDL używany do renderowania.
     */
    void Render(SDL_Renderer* renderer) override;

    /**
     * @brief Konwertuje stan wielokąta do formatu JSON.
     * 
     * Umożliwia zapisanie stanu wielokąta (wierzchołków, kolorów) do formatu JSON.
     * 
     * @return nlohmann::json Reprezentacja obiektu wielokąta w formacie JSON.
     */
    nlohmann::json ToJson() const override;

    // Metody transformacji:
    
    /**
     * @brief Translacja wielokąta o zadane przesunięcie.
     * 
     * Przesuwa wielokąt o wektor (dx, dy).
     * 
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    void Translate(float dx, float dy) override;

    /**
     * @brief Rotacja wielokąta o zadany kąt.
     * 
     * Rotuje wielokąt o podany kąt (w radianach).
     * 
     * @param angleRad Kąt rotacji w radianach.
     */
    void Rotate(float angleRad) override;

    /**
     * @brief Skalowanie wielokąta.
     * 
     * Skalowanie wielokąta względem osi X i Y.
     * 
     * @param sx Skalowanie w osi X.
     * @param sy Skalowanie w osi Y.
     */
    void Scale(float sx, float sy) override;

private:
    // Te punkty są lokalnymi (centroid-relatywnymi) wierzchołkami wielokąta.
    std::vector<Vector2> localPts;

    // Kolory:
    SDL_Color fillColor;      ///< Kolor wypełnienia wielokąta.
    SDL_Color outlineColor;   ///< Kolor obramowania wielokąta.
};
