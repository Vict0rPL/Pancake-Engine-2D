/**
 * @file Line.cpp
 * @brief Implementacja klasy `Line` reprezentującej linię w przestrzeni 2D.
 *
 * Klasa `Line` reprezentuje obiekt gry w postaci linii łączącej dwa punkty. Implementuje podstawowe operacje transformacji (przemieszczanie,
 * obracanie, skalowanie) oraz rysowanie linii, biorąc pod uwagę te transformacje.
 */

#include "Line.h"
#include "Transform.h"          // dla Mat3
#include <algorithm>            // dla std::min/std::max, jeśli potrzebne

 /**
  * @brief Konstruktor klasy `Line`.
  *
  * Tworzy nowy obiekt typu `Line` reprezentujący linię łączącą dwa punkty.
  * Kolor konturu ustawiany jest na czarny domyślnie.
  *
  * @param s Punkt początkowy linii.
  * @param e Punkt końcowy linii.
  */
Line::Line(const Point2D& s, const Point2D& e)
    : GameObject("Line")
    , startPoint(s)
    , endPoint(e)
{
    // Kolor konturu ustawiany na czarny (domyślnie)
    outlineColor = { 0, 0, 0, 255 };
    // Pozycja, rotacja, skala są domyślnie ustawione w TransformableObject
}

/**
 * @brief Rysuje linię przy użyciu renderera.
 *
 * W tej metodzie tworzone są transformacje obiektu linii (przemieszczenie, obrót, skalowanie) oraz rysowana jest linia po uwzględnieniu
 * tych transformacji.
 *
 * @param rdr Renderer do rysowania linii.
 */
void Line::Draw(PrimitiveRenderer& rdr) const {
    // 1) Lokalna reprezentacja punktów początkowego i końcowego
    Vector2 p1{ startPoint.GetX(), startPoint.GetY() };
    Vector2 p2{ endPoint.GetX(),   endPoint.GetY() };

    // 2) Budowa macierzy transformacji T·R·S wokół zdefiniowanej pozycji
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    // 3) Zastosowanie transformacji na punktach
    Vector2 w1 = M * p1;
    Vector2 w2 = M * p2;

    // 4) Rysowanie przekształconej linii
    rdr.DrawLine(int(w1.x), int(w1.y),
        int(w2.x), int(w2.y),
        outlineColor);
}

/**
 * @brief Renderuje linię na ekranie.
 *
 * Ta metoda używa renderera SDL oraz klasy pomocniczej `PrimitiveRenderer` do narysowania linii na ekranie.
 *
 * @param renderer Wskaźnik na renderer SDL.
 */
void Line::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

/**
 * @brief Przesuwa linię w przestrzeni.
 *
 * Metoda ta wywołuje metodę bazową `Translate` klasy `TransformableObject` w celu przemieszczenia obiektu.
 *
 * @param dx Przemieszczenie w osi X.
 * @param dy Przemieszczenie w osi Y.
 */
void Line::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Obraca linię w przestrzeni.
 *
 * Metoda ta wywołuje metodę bazową `Rotate` klasy `TransformableObject` w celu obrócenia obiektu.
 *
 * @param angleRad Kąt obrotu w radianach.
 */
void Line::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skaluje linię w przestrzeni.
 *
 * Metoda ta wywołuje metodę bazową `Scale` klasy `TransformableObject` w celu skalowania obiektu.
 *
 * @param sx Skalowanie w osi X.
 * @param sy Skalowanie w osi Y.
 */
void Line::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Zwraca reprezentację obiektu linii w formacie JSON.
 *
 * Ta metoda tworzy obiekt JSON, który przechowuje dane dotyczące linii, takie jak punkty początkowy i końcowy,
 * pozycja, rotacja i skala obiektu.
 *
 * @return Obiekt JSON zawierający dane linii.
 */
nlohmann::json Line::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Line";
    j["start"] = { {"x", startPoint.GetX()}, {"y", startPoint.GetY()} };
    j["end"] = { {"x", endPoint.GetX()},   {"y", endPoint.GetY()} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
