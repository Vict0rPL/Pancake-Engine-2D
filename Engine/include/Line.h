/**
 * @file Line.h
 * @brief Definicja klasy Line, reprezentującej linię w przestrzeni 2D.
 *
 * Klasa ta dziedziczy po `GameObject` oraz `TransformableObject` i umożliwia rysowanie oraz transformowanie linii.
 * Posiada metody pozwalające na rysowanie linii, transformowanie jej (przesunięcie, rotację, skalowanie) oraz konwersję do formatu JSON.
 */

#ifndef LINE_H
#define LINE_H

#include "GameObject.h"
#include "Point2D.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"
#include <nlohmann/json.hpp>

 /**
  * @brief Klasa Line reprezentująca linię w przestrzeni 2D.
  *
  * Ta klasa umożliwia tworzenie obiektów linii, ich rysowanie, transformowanie (przesunięcie, rotację, skalowanie) oraz konwertowanie do formatu JSON.
  */
class Line : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor klasy Line.
     *
     * Umożliwia stworzenie linii na podstawie dwóch punktów (punkt początkowy i końcowy).
     *
     * @param start Punkt początkowy linii.
     * @param end Punkt końcowy linii.
     */
    Line(const Point2D& start, const Point2D& end);

    /**
     * @brief Metoda rysująca linię przy użyciu obiektu PrimitiveRenderer.
     *
     * Umożliwia narysowanie linii na ekranie.
     *
     * @param renderer Obiekt PrimitiveRenderer do rysowania linii.
     */
    virtual void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Metoda renderująca linię.
     *
     * Zwykle wywoływana na każdą klatkę, aby narysować linię za pomocą SDL.
     *
     * @param renderer Wskaźnik na renderer SDL, używany do rysowania linii.
     */
    virtual void Render(SDL_Renderer* renderer) override;

    /**
     * @brief Metoda przesuwająca linię o wektor (dx, dy).
     *
     * Przesuwa początkowy i końcowy punkt linii.
     *
     * @param dx Przemieszczenie w osi X.
     * @param dy Przemieszczenie w osi Y.
     */
    void Translate(float dx, float dy) override;

    /**
     * @brief Metoda rotująca linię o zadany kąt.
     *
     * Rotacja linii odbywa się względem jej początkowego punktu.
     *
     * @param angleRad Kąt rotacji w radianach.
     */
    void Rotate(float angleRad) override;

    /**
     * @brief Metoda skalująca linię.
     *
     * Skalowanie linii zmienia odległość między punktami początkowym i końcowym.
     *
     * @param sx Skalowanie w osi X.
     * @param sy Skalowanie w osi Y.
     */
    void Scale(float sx, float sy) override;

    /**
     * @brief Metoda konwertująca linię do formatu JSON.
     *
     * Konwertuje linię na obiekt JSON, zawierający współrzędne punktów oraz kolor konturu.
     *
     * @return nlohmann::json Reprezentacja obiektu linii w formacie JSON.
     */
    virtual nlohmann::json ToJson() const override;

private:
    /// Punkt początkowy linii.
    Point2D startPoint;

    /// Punkt końcowy linii.
    Point2D endPoint;

    /// Kolor konturu linii.
    SDL_Color outlineColor;
};

#endif // LINE_H
