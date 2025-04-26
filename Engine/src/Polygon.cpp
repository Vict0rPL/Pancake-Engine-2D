/**
 * @file Polygon.cpp
 * @brief Implementacja klasy `Polygon` reprezentującej wielokąt w przestrzeni 2D.
 *
 * Klasa `Polygon` umożliwia tworzenie, renderowanie oraz transformowanie wielokąta w przestrzeni 2D. Obsługuje rysowanie wypełnionego i obrysowanego wielokąta, a także umożliwia transformacje takie jak translacja, rotacja i skalowanie.
 */

#include "Polygon.h"
#include "Transform.h"
#include <numeric>

 /**
  * @brief Konstruktor klasy `Polygon`.
  *
  * Tworzy obiekt `Polygon`, który reprezentuje wielokąt w przestrzeni 2D. Konstruktor oblicza środek ciężkości (centroid) wielokąta i przesuwa go do tego punktu.
  *
  * @param pts Wektor punktów, które tworzą wierzchołki wielokąta.
  * @param fill Kolor wypełnienia wielokąta.
  * @param outline Kolor obrysu wielokąta.
  */
Polygon::Polygon(const std::vector<SDL_Point>& pts,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Polygon")
    , fillColor(fill)
    , outlineColor(outline)
{
    // 1) obliczanie środka ciężkości...
    float cx = 0, cy = 0;
    for (auto& p : pts) { cx += p.x; cy += p.y; }
    cx /= pts.size(); cy /= pts.size();

    // 2) ustawienie pozycji Transform
    SetPosition({ cx, cy });

    // 3) zapisanie punktów lokalnych (Vector2) w odniesieniu do środka
    localPts.reserve(pts.size());
    for (auto& p : pts) {
        localPts.push_back({ p.x - cx, p.y - cy });
    }
}

/**
 * @brief Rysuje wielokąt przy użyciu renderer'a.
 *
 * Metoda ta oblicza końcową pozycję, rotację i skalę w przestrzeni świata, a następnie rysuje wypełniony i obrysowany wielokąt.
 *
 * @param rdr Obiekt `PrimitiveRenderer` używany do rysowania wielokąta.
 */
void Polygon::Draw(PrimitiveRenderer& rdr) const {
    // budowanie macierzy T·R·S
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    // transformacja punktów lokalnych do współrzędnych świata
    std::vector<SDL_Point> world;
    world.reserve(localPts.size() + 1);
    for (auto& v : localPts) {
        Vector2 w = M * v;
        world.push_back({ int(w.x), int(w.y) });
    }
    // zamknięcie pętli (jeśli ostatni punkt nie jest równy pierwszemu)
    if (!world.empty() && (world.front().x != world.back().x ||
        world.front().y != world.back().y)) {
        world.push_back(world.front());
    }

    // rysowanie wypełnienia i obrysu
    rdr.FillPolygon(world, fillColor);
    rdr.DrawPolygon(world, outlineColor);
}

/**
 * @brief Renderuje wielokąt przy użyciu SDL_Renderer.
 *
 * Metoda ta wywołuje funkcję `Draw` przy użyciu obiektu `PrimitiveRenderer`.
 *
 * @param renderer Renderer SDL3 do renderowania wielokąta.
 */
void Polygon::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

/**
 * @brief Translacja wielokąta w przestrzeni 2D.
 *
 * Ta metoda przesuwa wielokąt o określony wektor przesunięcia (dx, dy). Transformacje takie jak translacja są zapisywane w obiekcie, ale nie wpływają na wizualną reprezentację.
 *
 * @param dx Przemieszczenie wielokąta w osi X.
 * @param dy Przemieszczenie wielokąta w osi Y.
 */
void Polygon::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Rotacja wielokąta w przestrzeni 2D.
 *
 * Ta metoda ustawia rotację wielokąta, ale nie wpływa na wizualną reprezentację.
 *
 * @param angleRad Kąt rotacji w radianach.
 */
void Polygon::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skalowanie wielokąta w przestrzeni 2D.
 *
 * Ta metoda ustawia skalę wielokąta, ale nie wpływa na wizualną reprezentację.
 *
 * @param sx Skala wielokąta w osi X.
 * @param sy Skala wielokąta w osi Y.
 */
void Polygon::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Zwraca reprezentację wielokąta w formacie JSON.
 *
 * Ta metoda generuje dane JSON, które zawierają informacje o wierzchołkach, kolorach, pozycji, rotacji i skali wielokąta.
 *
 * @return Obiekt JSON zawierający dane o wielokącie (punkty, kolory, pozycja, rotacja, skala).
 */
nlohmann::json Polygon::ToJson() const {
    // obliczenie finalnych wierzchołków w przestrzeni świata dla JSON
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    nlohmann::json j;
    j["type"] = "Polygon";
    j["points"] = nlohmann::json::array();
    for (auto& v : localPts) {
        Vector2 w = M * v;
        j["points"].push_back({ {"x", int(w.x)}, {"y", int(w.y)} });
    }
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", GetPosition().x}, {"y", GetPosition().y} };
    j["rotation"] = GetRotation();
    auto sc = GetScale();
    j["scale"] = { {"x", sc.x}, {"y", sc.y} };
    return j;
}
