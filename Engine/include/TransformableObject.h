/**
 * @file TransformableObject.h
 * @brief Definicja klasy `TransformableObject` odpowiedzialnej za transformacje obiektów 2D w przestrzeni.
 *
 * Plik zawiera definicję klasy `TransformableObject`, która umożliwia wykonywanie podstawowych operacji transformacyjnych na obiektach, takich jak:
 * - Przesunięcie (Translate)
 * - Obrót (Rotate)
 * - Skalowanie (Scale)
 *
 * Klasa ta przechowuje informacje o położeniu, rotacji i skali obiektów oraz umożliwia ich modyfikację.
 */

#pragma once
#include "GameObject.h"

 /**
  * @brief Klasa TransformableObject reprezentuje obiekt 2D, który można poddać transformacjom.
  *
  * Klasa ta przechowuje informacje o pozycji, rotacji i skali obiektów oraz udostępnia metody do ich modyfikacji.
  * Można ją stosować do wszelkiego rodzaju obiektów, które wymagają możliwości przesunięcia, obrotu i skalowania,
  * takich jak figury geometryczne w grze lub aplikacji graficznej.
  */
class TransformableObject {
public:
    /**
     * @brief Wirtualny destruktor.
     *
     * Destruktor klasy `TransformableObject`. Dzięki temu możemy poprawnie usunąć obiekty tej klasy lub jej pochodne.
     */
    virtual ~TransformableObject() = default;

    /**
     * @brief Przesuwa obiekt o zadaną wartość w osi X i Y.
     *
     * Metoda ta zmienia pozycję obiektu, dodając do jego współrzędnych wektory przesunięcia.
     *
     * @param dx Przesunięcie w osi X.
     * @param dy Przesunięcie w osi Y.
     */
    virtual void Translate(float dx, float dy) {
        position += Vector2{ dx,dy };
    }

    /**
     * @brief Obraca obiekt o zadany kąt w radianach.
     *
     * Metoda ta zmienia kąt obrotu obiektu, dodając do jego obecnego kąta obrotu wartość `angleRad`.
     *
     * @param angleRad Kąt obrotu w radianach.
     */
    virtual void Rotate(float angleRad) {
        rotation += angleRad;
    }

    /**
     * @brief Skaluje obiekt według zadanych współczynników w osiach X i Y.
     *
     * Metoda ta zmienia skalę obiektu, mnożąc obecne wartości skali w osiach X i Y przez odpowiednie współczynniki.
     *
     * @param sx Skalowanie w osi X.
     * @param sy Skalowanie w osi Y.
     */
    virtual void Scale(float sx, float sy) {
        scale_ = Vector2{ scale_.x * sx, scale_.y * sy };
    }

    /**
     * @brief Zwraca obecną pozycję obiektu.
     *
     * Metoda ta zwraca wektor, który przechowuje bieżącą pozycję obiektu w przestrzeni 2D.
     *
     * @return Pozycja obiektu w przestrzeni.
     */
    const Vector2& GetPosition() const { return position; }

    /**
     * @brief Zwraca obecny kąt obrotu obiektu.
     *
     * Metoda ta zwraca kąt obrotu obiektu w radianach.
     *
     * @return Kąt obrotu obiektu.
     */
    float GetRotation() const { return rotation; }

    /**
     * @brief Zwraca obecne wartości skali obiektu.
     *
     * Metoda ta zwraca wektor, który przechowuje obecne wartości skali obiektu w osiach X i Y.
     *
     * @return Wartości skali obiektu.
     */
    const Vector2& GetScale() const { return scale_; }

    /**
     * @brief Ustala pozycję obiektu.
     *
     * Metoda ta umożliwia ustawienie nowej pozycji obiektu.
     *
     * @param p Nowa pozycja obiektu w przestrzeni.
     */
    void SetPosition(const Vector2& p) { position = p; }

    /**
     * @brief Ustala kąt obrotu obiektu.
     *
     * Metoda ta umożliwia ustawienie nowego kąta obrotu obiektu.
     *
     * @param r Nowy kąt obrotu obiektu w radianach.
     */
    void SetRotation(float r) { rotation = r; }

    /**
     * @brief Ustala skalę obiektu.
     *
     * Metoda ta umożliwia ustawienie nowej skali obiektu.
     *
     * @param s Nowa skala obiektu w przestrzeni 2D.
     */
    void SetScale(const Vector2& s) { scale_ = s; }

protected:
    Vector2 position{ 0,0 }; ///< Pozycja obiektu w przestrzeni 2D.
    float   rotation{ 0 }; ///< Kąt obrotu obiektu w radianach.
    Vector2 scale_{ 1,1 }; ///< Skala obiektu w osiach X i Y.
};
