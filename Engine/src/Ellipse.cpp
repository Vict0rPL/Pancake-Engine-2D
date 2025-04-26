/**
 * @file Ellipse.cpp
 * @brief Implementacja klasy `Ellipse`, reprezentującej elipsę w przestrzeni 2D.
 *
 * Klasa ta dziedziczy po `GameObject` i pozwala na rysowanie, transformowanie oraz serializowanie obiektów elips w przestrzeni 2D.
 * Obiekt `Ellipse` posiada właściwości takie jak promień wzdłuż osi X i Y, kolor wypełnienia oraz kolor obramowania.
 */

#include "Ellipse.h"
#include "PrimitiveRenderer.h"

 /**
  * @brief Konstruktor klasy `Ellipse`.
  *
  * Tworzy obiekt `Ellipse` o zadanej pozycji, promieniach (wzdłuż osi X i Y), kolorze wypełnienia i obramowania.
  * Ustawia także początkową pozycję i wartości transformacji (rotacja = 0, skala = (1,1)).
  *
  * @param x Współrzędna X centrum elipsy.
  * @param y Współrzędna Y centrum elipsy.
  * @param radiusX Promień elipsy wzdłuż osi X.
  * @param radiusY Promień elipsy wzdłuż osi Y.
  * @param fill Kolor wypełnienia elipsy.
  * @param outline Kolor obramowania elipsy.
  */
Ellipse::Ellipse(int x, int y, int radiusX, int radiusY,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Ellipse")
    , rx(radiusX)
    , ry(radiusY)
    , fillColor(fill)
    , outlineColor(outline)
{
    SetPosition({ float(x), float(y) });
}

/**
 * @brief Rysuje elipsę za pomocą `PrimitiveRenderer`.
 *
 * Funkcja ta rysuje elipsę, uwzględniając aktualną transformację (przesunięcie, obrót, skalowanie).
 * Elipsa jest rysowana jako wypełniony kształt z obramowaniem.
 *
 * @param rdr Referencja do obiektu `PrimitiveRenderer`, który odpowiada za rysowanie kształtów.
 */
void Ellipse::Draw(PrimitiveRenderer& rdr) const {
    auto pos = GetPosition();  // Pobiera aktualną pozycję
    auto sc = GetScale();      // Pobiera aktualną skalę

    // Przemnożenie promieni przez skalę
    int drawRx = int(rx * sc.x);
    int drawRy = int(ry * sc.y);

    // Rysowanie elipsy z wypełnieniem i obramowaniem
    rdr.FillEllipse(int(pos.x), int(pos.y), drawRx, drawRy, fillColor);
    rdr.DrawEllipse(int(pos.x), int(pos.y), drawRx, drawRy, outlineColor);
}

/**
 * @brief Renderuje elipsę za pomocą `SDL_Renderer`.
 *
 * Używa `PrimitiveRenderer` do renderowania elipsy na ekranie.
 *
 * @param renderer Wskaźnik na obiekt `SDL_Renderer`, który jest używany do renderowania obiektów.
 */
void Ellipse::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

/**
 * @brief Przemieszcza obiekt elipsy o zadany wektor (dx, dy).
 *
 * Funkcja wywołuje metodę `Translate` z klasy bazowej `TransformableObject`, która aktualizuje pozycję obiektu.
 *
 * @param dx Przemieszczenie w osi X.
 * @param dy Przemieszczenie w osi Y.
 */
void Ellipse::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Rotuje obiekt elipsy o zadany kąt (w radianach).
 *
 * Funkcja wywołuje metodę `Rotate` z klasy bazowej `TransformableObject`, która aktualizuje kąt obrotu.
 *
 * @param angleRad Kąt obrotu w radianach.
 */
void Ellipse::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skaluje obiekt elipsy o zadany współczynnik wzdłuż osi X i Y.
 *
 * Funkcja wywołuje metodę `Scale` z klasy bazowej `TransformableObject`, która aktualizuje skalę obiektu.
 *
 * @param sx Współczynnik skali wzdłuż osi X.
 * @param sy Współczynnik skali wzdłuż osi Y.
 */
void Ellipse::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Serializuje obiekt elipsy do formatu JSON.
 *
 * Tworzy obiekt JSON, który zawiera wszystkie istotne informacje o elipsie, takie jak typ, pozycja, promienie,
 * kolory oraz transformacje.
 *
 * @return Obiekt JSON zawierający dane elipsy.
 */
nlohmann::json Ellipse::ToJson() const {
    auto pos = GetPosition();  // Pobiera aktualną pozycję
    auto sc = GetScale();      // Pobiera aktualną skalę

    nlohmann::json j;
    j["type"] = "Ellipse";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["rx"] = rx;
    j["ry"] = ry;
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
