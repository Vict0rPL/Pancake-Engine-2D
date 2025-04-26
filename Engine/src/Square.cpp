/**
 * @file Square.cpp
 * @brief Implementacja klasy `Square`, reprezentującej kwadrat w grze.
 *
 * Klasa `Square` umożliwia tworzenie kwadratów, rysowanie ich na ekranie oraz manipulację ich pozycją, obrotem i skalą.
 * Kwadrat jest reprezentowany za pomocą współrzędnych, koloru wypełnienia i koloru obramowania.
 */

#include "Square.h"
#include "Transform.h"   // Mat3
#include <array>

 /**
  * @brief Konstruktor klasy `Square`.
  *
  * Inicjalizuje kwadrat o określonych parametrach: pozycji, rozmiarze oraz kolorach wypełnienia i obramowania.
  * Pozycja kwadratu jest zapisywana w bazowym transformacie.
  *
  * @param x Współrzędna X lewego górnego rogu kwadratu.
  * @param y Współrzędna Y lewego górnego rogu kwadratu.
  * @param size Rozmiar boku kwadratu.
  * @param fill Kolor wypełnienia kwadratu.
  * @param outline Kolor obramowania kwadratu.
  */
Square::Square(int x, int y, int size,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Square")
    , size(size)
    , fillColor(fill)
    , outlineColor(outline)
{
    // zapisuje lewy górny róg w bazowym transformacie
    SetPosition({ float(x), float(y) });
}

/**
 * @brief Rysuje kwadrat na ekranie za pomocą obiektu `PrimitiveRenderer`.
 *
 * Tworzy listę punktów w przestrzeni lokalnej (względem środka kwadratu),
 * a następnie przekształca je przy użyciu macierzy transformacji (skalowanie, obrót, translacja).
 * Kwadrat jest rysowany za pomocą dwóch operacji: wypełnienia i obramowania.
 *
 * @param rdr Obiekt `PrimitiveRenderer`, który służy do rysowania kwadratu.
 */
void Square::Draw(PrimitiveRenderer& rdr) const {
    // połowa boku kwadratu
    float hs = size * 0.5f;

    // lokalne narożniki kwadratu, względem (0, 0)
    std::array<Vector2, 4> local = {
      Vector2{-hs, -hs},
      Vector2{ hs, -hs},
      Vector2{ hs,  hs},
      Vector2{-hs,  hs}
    };

    // tworzymy macierz transformacji T·R·S: najpierw skaluje, potem obraca, potem translacja na (x+hs, y+hs)
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 T = Mat3::Translate(
        GetPosition().x + hs,
        GetPosition().y + hs
    );
    Mat3 M = T * R * S;

    // przekształcamy punkty i zbieramy je do SDL_Points
    std::vector<SDL_Point> pts;
    pts.reserve(local.size());
    for (auto& v : local) {
        Vector2 w = M * v;               // potrzeba przeciążenia operatora Mat3 × Vector2
        pts.push_back({ int(w.x), int(w.y) });
    }

    // rysowanie wypełnienia oraz obramowania
    rdr.FillPolygon(pts, fillColor);
    rdr.DrawPolygon(pts, outlineColor);
}

/**
 * @brief Renderuje kwadrat na ekranie za pomocą SDL_Renderer.
 *
 * Tworzy obiekt `PrimitiveRenderer` i używa go do narysowania kwadratu.
 *
 * @param renderer Wskaźnik na obiekt `SDL_Renderer`, który służy do renderowania.
 */
void Square::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

/**
 * @brief Przemieszcza kwadrat o zadany wektor przesunięcia.
 *
 * Aktualizuje pozycję kwadratu, stosując translację do jego transformacji.
 *
 * @param dx Przemieszczenie kwadratu w osi X.
 * @param dy Przemieszczenie kwadratu w osi Y.
 */
void Square::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Obraca kwadrat o zadany kąt.
 *
 * Aktualizuje kąt obrotu kwadratu w jego transformacji.
 *
 * @param angleRad Kąt obrotu w radianach.
 */
void Square::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skaluje kwadrat o zadany współczynnik.
 *
 * Aktualizuje współczynniki skali kwadratu w jego transformacji.
 *
 * @param sx Współczynnik skali w osi X.
 * @param sy Współczynnik skali w osi Y.
 */
void Square::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Serializuje obiekt kwadratu do formatu JSON.
 *
 * Serializuje dane obiektu kwadratu, takie jak pozycja, rozmiar, kolory i transformacje, do formatu JSON.
 *
 * @return Obiekt JSON reprezentujący dane kwadratu.
 */
nlohmann::json Square::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Square";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["size"] = size;  // oryginalna długość boku
    j["fillColor"] = {
        {"r", fillColor.r}, {"g", fillColor.g},
        {"b", fillColor.b}, {"a", fillColor.a}
    };
    j["outlineColor"] = {
        {"r", outlineColor.r}, {"g", outlineColor.g},
        {"b", outlineColor.b}, {"a", outlineColor.a}
    };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},   {"y", sc.y} };
    return j;
}
