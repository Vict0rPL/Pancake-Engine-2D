/**
 * @file Circle.h
 * @brief Definicja klasy Circle reprezentującej okrąg jako obiekt gry.
 */

#pragma once

#include "GameObject.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"
#include <nlohmann/json.hpp>

 /**
  * @brief Klasa reprezentująca okrąg (circle) w grze.
  *
  * Dziedziczy po GameObject oraz TransformableObject.
  * Okrąg posiada wypełnienie oraz kontur i obsługuje transformacje.
  */
class Circle : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor okręgu.
     *
     * @param cx Współrzędna X środka okręgu.
     * @param cy Współrzędna Y środka okręgu.
     * @param r Promień okręgu.
     * @param fill Kolor wypełnienia.
     * @param outline Kolor konturu.
     */
    Circle(int cx, int cy, int r, SDL_Color fill, SDL_Color outline);

    /**
     * @brief Rysuje okrąg za pomocą zadanego renderera prymitywów.
     *
     * @param renderer Referencja do obiektu PrimitiveRenderer używanego do rysowania.
     */
    virtual void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Renderuje okrąg przy użyciu SDL_Renderera.
     *
     * @param renderer Wskaźnik na SDL_Renderer.
     */
    virtual void Render(SDL_Renderer* renderer) override;

    /**
     * @brief Serializuje dane okręgu do formatu JSON.
     *
     * @return Obiekt JSON opisujący okrąg.
     */
    virtual nlohmann::json ToJson() const override;

    // Transformacje odziedziczone z TransformableObject:

    /**
     * @brief Przesuwa okrąg o zadany wektor.
     *
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    void Translate(float dx, float dy) override;

    /**
     * @brief Obraca okrąg o zadany kąt (w radianach).
     *
     * @param angleRad Kąt obrotu w radianach.
     */
    void Rotate(float angleRad) override;

    /**
     * @brief Skaluje okrąg względem osi X i Y.
     *
     * @param sx Współczynnik skalowania w osi X.
     * @param sy Współczynnik skalowania w osi Y.
     */
    void Scale(float sx, float sy) override;

    /**
     * @brief Pobiera współrzędną X środka okręgu.
     *
     * @return Wartość współrzędnej X.
     */
    int GetX() const { return x; }

    /**
     * @brief Pobiera współrzędną Y środka okręgu.
     *
     * @return Wartość współrzędnej Y.
     */
    int GetY() const { return y; }

    /**
     * @brief Pobiera promień okręgu.
     *
     * @return Promień.
     */
    int GetRadius() const { return radius; }

    /**
     * @brief Zwraca prostokąt ograniczający okrąg (bounding box).
     *
     * Używa przeskalowanego promienia na podstawie aktualnej skali transformacji.
     *
     * @return SDL_FRect opisujący prostokąt ograniczający.
     */
    SDL_FRect GetRect() const {
        float radiusScaled = radius * ((GetScale().x + GetScale().y) * 0.5f);
        return {
            GetPosition().x - radiusScaled,
            GetPosition().y - radiusScaled,
            radiusScaled * 2.0f,
            radiusScaled * 2.0f
        };
    }

private:
    int x; ///< Współrzędna X środka okręgu.
    int y; ///< Współrzędna Y środka okręgu.
    int radius; ///< Promień okręgu.
    SDL_Color fillColor; ///< Kolor wypełnienia okręgu.
    SDL_Color outlineColor; ///< Kolor konturu okręgu.
};
