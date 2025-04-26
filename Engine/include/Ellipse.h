/**
 * @file Ellipse.h
 * @brief Definicja klasy Ellipse reprezentującej elipsę jako obiekt gry.
 */

#pragma once

#include "GameObject.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"
#include <nlohmann/json.hpp>

 /**
  * @brief Klasa reprezentująca elipsę (ellipse) w grze.
  *
  * Dziedziczy po GameObject oraz TransformableObject.
  * Elipsa posiada wypełnienie oraz kontur i obsługuje transformacje.
  */
class Ellipse : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor elipsy.
     *
     * @param cx Współrzędna X środka elipsy.
     * @param cy Współrzędna Y środka elipsy.
     * @param rx Promień w osi X.
     * @param ry Promień w osi Y.
     * @param fill Kolor wypełnienia.
     * @param outline Kolor konturu.
     */
    Ellipse(int cx, int cy, int rx, int ry, SDL_Color fill, SDL_Color outline);

    /**
     * @brief Rysuje elipsę za pomocą zadanego renderera prymitywów.
     *
     * @param renderer Referencja do obiektu PrimitiveRenderer używanego do rysowania.
     */
    virtual void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Renderuje elipsę przy użyciu SDL_Renderera.
     *
     * @param renderer Wskaźnik na SDL_Renderer.
     */
    virtual void Render(SDL_Renderer* renderer) override;

    /**
     * @brief Serializuje dane elipsy do formatu JSON.
     *
     * @return Obiekt JSON opisujący elipsę.
     */
    virtual nlohmann::json ToJson() const override;

    // Transformacje odziedziczone z TransformableObject:

    /**
     * @brief Przesuwa elipsę o zadany wektor.
     *
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    void Translate(float dx, float dy) override;

    /**
     * @brief Obraca elipsę o zadany kąt (w radianach).
     *
     * @param angleRad Kąt obrotu w radianach.
     */
    void Rotate(float angleRad) override;

    /**
     * @brief Skaluje elipsę względem osi X i Y.
     *
     * @param sx Współczynnik skalowania w osi X.
     * @param sy Współczynnik skalowania w osi Y.
     */
    void Scale(float sx, float sy) override;

    /**
     * @brief Pobiera współrzędną X środka elipsy.
     *
     * @return Wartość współrzędnej X.
     */
    int GetX() const { return x; }

    /**
     * @brief Pobiera współrzędną Y środka elipsy.
     *
     * @return Wartość współrzędnej Y.
     */
    int GetY() const { return y; }

private:
    int x; ///< Współrzędna X środka elipsy.
    int y; ///< Współrzędna Y środka elipsy.
    int rx; ///< Promień w osi X.
    int ry; ///< Promień w osi Y.
    SDL_Color fillColor; ///< Kolor wypełnienia elipsy.
    SDL_Color outlineColor; ///< Kolor konturu elipsy.
};
