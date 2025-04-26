/**
 * @file Point2D.cpp
 * @brief Implementacja klasy `Point2D` reprezentującej punkt w przestrzeni 2D.
 *
 * Klasa `Point2D` przechowuje pozycję punktu w przestrzeni, umożliwia jego rysowanie, a także obsługuje transformacje takie jak translacja, rotacja i skalowanie.
 *
 * Punkt jest wyświetlany na ekranie w określonej pozycji, a transformacje są zapisywane, ale nie wpływają na wizualne przesunięcie punktu poza metodą translacji.
 */

#include "Point2D.h"

 /**
  * @brief Konstruktor klasy `Point2D`.
  *
  * Tworzy obiekt `Point2D`, który reprezentuje punkt w przestrzeni 2D. Punkt jest inicjowany pozycją (x, y).
  * Rotacja jest ustawiona na 0, a skala na (1, 1) domyślnie.
  *
  * @param x Pozycja punktu w osi X.
  * @param y Pozycja punktu w osi Y.
  */
Point2D::Point2D(float x, float y)
    : GameObject("Point2D")
{
    // zapisanie pozycji punktu w klasie bazowej
    SetPosition({ x, y });
    // rotacja=0 i skala=(1,1) domyślnie
}

/**
 * @brief Rysuje punkt na ekranie.
 *
 * Metoda ta rysuje punkt w pozycji określonej w klasie bazowej `GameObject`.
 *
 * @param renderer Obiekt `PrimitiveRenderer` do rysowania punktu na ekranie.
 */
void Point2D::Draw(PrimitiveRenderer& renderer) const {
    // rysowanie punktu w zapisanej pozycji
    auto p = GetPosition();
    SDL_Color color{ 0, 0, 0, 255 };  // Kolor czarny
    renderer.DrawPoint(int(p.x), int(p.y), color);
}

/**
 * @brief Renderuje punkt na ekranie.
 *
 * Metoda ta jest wywoływana w celu wywołania metody `Draw` przy użyciu obiektu renderer.
 *
 * @param renderer Renderer SDL3 do renderowania punktu.
 */
void Point2D::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer r(renderer);
    Draw(r);
}

/**
 * @brief Translacja punktu w przestrzeni 2D.
 *
 * Ta metoda przesuwa punkt o określony wektor przesunięcia (dx, dy). Transformacje takie jak translacja są zapisywane w obiekcie, ale nie wpływają na wizualne przesunięcie punktu.
 *
 * @param dx Przemieszczenie punktu w osi X.
 * @param dy Przemieszczenie punktu w osi Y.
 */
void Point2D::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Rotacja punktu w przestrzeni 2D.
 *
 * Ta metoda ustawia rotację punktu, ale nie wpływa na wizualne przesunięcie punktu.
 *
 * @param angleRad Kąt rotacji w radianach.
 */
void Point2D::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skalowanie punktu.
 *
 * Ta metoda ustawia skalę punktu, ale nie wpływa na wizualną reprezentację.
 *
 * @param sx Skala punktu w osi X.
 * @param sy Skala punktu w osi Y.
 */
void Point2D::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Zwraca reprezentację punktu w formacie JSON.
 *
 * Ta metoda generuje dane JSON, które zawierają informacje o pozycji, rotacji i skali punktu.
 *
 * @return Obiekt JSON zawierający dane o punkcie (pozycja, rotacja, skala).
 */
nlohmann::json Point2D::ToJson() const {
    auto p = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Point2D";
    j["position"] = { { "x", p.x }, { "y", p.y } };
    j["rotation"] = GetRotation();
    j["scale"] = { { "x", sc.x }, { "y", sc.y } };
    return j;
}
