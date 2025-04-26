/**
 * @file Point2D.h
 * @brief Definicja klasy Point2D, reprezentującej punkt w 2D.
 *
 * Klasa ta dziedziczy po klasach `GameObject` i `TransformableObject`, umożliwiając przechowywanie i manipulację współrzędnymi punktu w przestrzeni 2D.
 */

#ifndef POINT2D_H
#define POINT2D_H

#include "GameObject.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"

 /**
  * @brief Klasa Point2D reprezentująca punkt w 2D.
  *
  * Klasa ta przechowuje współrzędne punktu (x, y), umożliwia ich ustawianie i pobieranie, a także rysowanie punktu w przestrzeni 2D.
  * Klasa dziedziczy po klasach `GameObject` i `TransformableObject`, co pozwala na manipulację położeniem, skalowaniem oraz rotacją punktu.
  */
class Point2D : public GameObject, public TransformableObject {
public:
    /**
     * @brief Konstruktor klasy Point2D.
     *
     * Inicjalizuje punkt o podanych współrzędnych (x, y).
     *
     * @param x Współrzędna X punktu.
     * @param y Współrzędna Y punktu.
     */
    Point2D(float x, float y);

    /**
     * @brief Zwraca współrzędną X punktu.
     *
     * @return Współrzędna X punktu.
     */
    float GetX() const { return TransformableObject::position.x; }

    /**
     * @brief Zwraca współrzędną Y punktu.
     *
     * @return Współrzędna Y punktu.
     */
    float GetY() const { return TransformableObject::position.y; }

    /**
     * @brief Ustawia nową wartość współrzędnej X.
     *
     * @param nx Nowa wartość współrzędnej X.
     */
    void SetX(float nx) { TransformableObject::position.x = nx; }

    /**
     * @brief Ustawia nową wartość współrzędnej Y.
     *
     * @param ny Nowa wartość współrzędnej Y.
     */
    void SetY(float ny) { TransformableObject::position.y = ny; }

    /**
     * @brief Ustawia nowe wartości współrzędnych X i Y.
     *
     * @param nx Nowa wartość współrzędnej X.
     * @param ny Nowa wartość współrzędnej Y.
     */
    void SetCoordinates(float nx, float ny) {
        TransformableObject::position.x = nx;
        TransformableObject::position.y = ny;
    }

    /**
     * @brief Rysuje punkt na ekranie przy użyciu `PrimitiveRenderer`.
     *
     * Metoda ta wykorzystuje renderer do narysowania punktu w przestrzeni 2D.
     *
     * @param renderer Renderer do rysowania.
     */
    void Draw(PrimitiveRenderer& renderer) const;

    /**
     * @brief Metoda aktualizująca stan punktu (pusta w przypadku tej klasy).
     *
     * W tej klasie metoda nie wykonuje żadnych operacji, ale jest wymagana przez interfejs `GameObject`.
     *
     * @param deltaTime Czas, który upłynął od ostatniej klatki.
     */
    virtual void Update(float deltaTime) override {}

    /**
     * @brief Renderuje punkt na ekranie przy użyciu SDL.
     *
     * Ta metoda wywołuje funkcje renderujące SDL, aby wyświetlić punkt w odpowiednim miejscu na ekranie.
     *
     * @param renderer Renderer SDL używany do renderowania punktu.
     */
    virtual void Render(SDL_Renderer* renderer) override;

    // Metody z TransformableObject:

    /**
     * @brief Translacja punktu o zadane przesunięcie.
     *
     * Przesuwa punkt o wektor (dx, dy).
     *
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    void Translate(float dx, float dy) override;

    /**
     * @brief Rotacja punktu o zadany kąt.
     *
     * Rotuje punkt o podany kąt (w radianach).
     *
     * @param angleRad Kąt rotacji w radianach.
     */
    void Rotate(float angleRad) override;

    /**
     * @brief Skalowanie punktu.
     *
     * Skalowanie nie wpływa na punkt, ponieważ nie ma fizycznych wymiarów, ale metoda ta jest wymagana przez interfejs.
     *
     * @param sx Skalowanie w osi X.
     * @param sy Skalowanie w osi Y.
     */
    void Scale(float sx, float sy) override;

    /**
     * @brief Konwertuje stan punktu do formatu JSON.
     *
     * Umożliwia zapisanie stanu punktu, w tym jego współrzędnych, do formatu JSON.
     *
     * @return nlohmann::json Reprezentacja obiektu punktu w formacie JSON.
     */
    virtual nlohmann::json ToJson() const override;
};

#endif // POINT2D_H
