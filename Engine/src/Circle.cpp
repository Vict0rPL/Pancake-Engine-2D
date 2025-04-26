/**
 * @file Circle.cpp
 * @brief Implementacja klasy `Circle`, reprezentującej okrąg w grze lub aplikacji graficznej.
 *
 * Klasa ta rozszerza `GameObject` i implementuje logikę renderowania okręgów oraz ich transformacji
 * (przemieszczanie, obracanie, skalowanie). Obejmuje również konwersję obiektów do formatu JSON,
 * umożliwiając łatwe przechowywanie i ładowanie obiektów w aplikacji.
 */

#include "Circle.h"
#include "PrimitiveRenderer.h"

 /**
  * @brief Konstruktor klasy Circle.
  *
  * Tworzy obiekt typu `Circle`, inicjalizując jego pozycję, promień, kolor wypełnienia oraz kolor obramowania.
  * Pozycja jest inicjowana w lewym górnym rogu, a początkowy kąt obrotu oraz skala są ustawiane na wartości domyślne (0 i (1,1)).
  *
  * @param x Współrzędna x pozycji okręgu.
  * @param y Współrzędna y pozycji okręgu.
  * @param r Promień okręgu.
  * @param fill Kolor wypełnienia okręgu.
  * @param outline Kolor obramowania okręgu.
  */
Circle::Circle(int x, int y, int r,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Circle")
    , radius(r)
    , fillColor(fill)
    , outlineColor(outline)
{
    // inicjalizacja pozycji obiektu:
    SetPosition({ float(x), float(y) });
    // rotacja na początek to 0, skala to (1,1) domyślnie
}

/**
 * @brief Rysuje okrąg za pomocą PrimitiveRenderer.
 *
 * Funkcja ta wykonuje następujące kroki:
 * 1) Pobiera aktualny stan transformacji (pozycja, skala, rotacja).
 * 2) Oblicza średni promień okręgu na podstawie transformacji skali.
 * 3) Rysuje wypełniony okrąg oraz jego obramowanie w odpowiednich kolorach.
 *
 * @param rdr Obiekt klasy `PrimitiveRenderer`, który używany jest do renderowania okręgu.
 */
void Circle::Draw(PrimitiveRenderer& rdr) const {
    // 1) Pobieranie stanu transformacji:
    auto pos = GetPosition();
    auto sc = GetScale();
    auto rot = GetRotation();  // Dla pełnego okręgu rotacja nie wpływa na wynik, ale może w przyszłości służyć do animacji tekstury.

    // 2) Obliczanie średniego promienia:
    int drawR = int(radius * ((sc.x + sc.y) * 0.5f));

    // 3) Rysowanie okręgu w wyliczonej pozycji:
    rdr.FillCircle(int(pos.x), int(pos.y), drawR, fillColor);  // Rysowanie wypełnionego okręgu
    rdr.DrawCircle(int(pos.x), int(pos.y), drawR, outlineColor);  // Rysowanie obramowania okręgu
}

/**
 * @brief Renderuje okrąg za pomocą `SDL_Renderer` oraz `PrimitiveRenderer`.
 *
 * Funkcja ta tworzy obiekt `PrimitiveRenderer` i wywołuje metodę `Draw`, aby wykonać rendering okręgu.
 *
 * @param renderer Wskaźnik do renderera SDL, który jest używany do rysowania obiektów.
 */
void Circle::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

/**
 * @brief Przesuwa okrąg o zadane wartości.
 *
 * Funkcja ta wywołuje metodę `Translate` z klasy bazowej, aby zaktualizować pozycję okręgu.
 *
 * @param dx Przemieszczenie w osi x.
 * @param dy Przemieszczenie w osi y.
 */
void Circle::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

/**
 * @brief Obraca okrąg o zadany kąt.
 *
 * Funkcja ta wywołuje metodę `Rotate` z klasy bazowej, aby zaktualizować kąt obrotu okręgu.
 *
 * @param angleRad Kąt obrotu w radianach.
 */
void Circle::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

/**
 * @brief Skaluje okrąg o zadane współczynniki.
 *
 * Funkcja ta wywołuje metodę `Scale` z klasy bazowej, aby zaktualizować skalę okręgu.
 *
 * @param sx Skalowanie w osi x.
 * @param sy Skalowanie w osi y.
 */
void Circle::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

/**
 * @brief Konwertuje okrąg do formatu JSON.
 *
 * Funkcja ta konwertuje wszystkie właściwości obiektu `Circle` do formatu JSON, umożliwiając jego zapis do pliku
 * lub przesyłanie w innych częściach aplikacji. Obejmuje pozycję, rotację, skalę, promień oraz kolory wypełnienia i obramowania.
 *
 * @return Obiekt JSON zawierający właściwości okręgu.
 */
nlohmann::json Circle::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Circle";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["radius"] = radius;
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
