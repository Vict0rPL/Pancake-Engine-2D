/**
 * @file PrimitiveRenderer.cpp
 * @brief Implementacja klasy `PrimitiveRenderer` odpowiedzialnej za rysowanie podstawowych prymitywów geometrycznych w SDL.
 *
 * Klasa `PrimitiveRenderer` dostarcza metody do rysowania punktów, linii, prostokątów, okręgów, elips oraz wielokątów. Obejmuje również wypełnianie tych prymitywów odpowiednimi kolorami.
 */

#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>

 /**
  * @brief Konstruktor klasy `PrimitiveRenderer`.
  *
  * Inicjalizuje obiekt `PrimitiveRenderer`, który będzie używany do rysowania prymitywów geometrycznych przy pomocy obiektu `SDL_Renderer`.
  *
  * @param renderer Wskaźnik na renderer SDL, który będzie używany do rysowania.
  */
PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer* renderer)
    : renderer(renderer)
{
}

/**
 * @brief Rysuje pojedynczy punkt na ekranie.
 *
 * Metoda ustawia kolor rysowania i rysuje punkt w zadanej pozycji.
 *
 * @param x Współrzędna X punktu.
 * @param y Współrzędna Y punktu.
 * @param color Kolor punktu.
 */
void PrimitiveRenderer::DrawPoint(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, x, y);
}

/**
 * @brief Rysuje linię między dwoma punktami.
 *
 * Metoda używa algorytmu przyrostowego do narysowania linii pomiędzy punktami (x0, y0) a (x1, y1).
 *
 * @param x0 Współrzędna X pierwszego punktu.
 * @param y0 Współrzędna Y pierwszego punktu.
 * @param x1 Współrzędna X drugiego punktu.
 * @param y1 Współrzędna Y drugiego punktu.
 * @param color Kolor linii.
 */
void PrimitiveRenderer::DrawLine(int x0, int y0, int x1, int y1, SDL_Color color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    if (dx >= dy) {
        float m = (dx != 0) ? static_cast<float>(y1 - y0) / dx : 0;
        float y = (float)y0;
        for (int x = x0; x != x1; x += sx) {
            DrawPoint(x, static_cast<int>(round(y)), color);
            y += m * sx;
        }
    }
    else {
        float m = (dy != 0) ? static_cast<float>(x1 - x0) / dy : 0;
        float x = (float)x0;
        for (int y = y0; y != y1; y += sy) {
            DrawPoint(static_cast<int>(round(x)), y, color);
            x += m * sy;
        }
    }
    DrawPoint(x1, y1, color);
}

/**
 * @brief Wypełnia kwadrat w zadanej pozycji i rozmiarze.
 *
 * Metoda wypełnia kwadrat o zadanym rozmiarze i kolorze, rysując poziome linie.
 *
 * @param x Współrzędna X lewego górnego rogu kwadratu.
 * @param y Współrzędna Y lewego górnego rogu kwadratu.
 * @param size Rozmiar kwadratu.
 * @param color Kolor wypełnienia kwadratu.
 */
void PrimitiveRenderer::FillSquare(int x, int y, int size, SDL_Color color) {
    for (int dy = 0; dy < size; ++dy) {
        DrawLine(x, y + dy, x + size - 1, y + dy, color);
    }
}

/**
 * @brief Rysuje kontur kwadratu w zadanej pozycji i rozmiarze.
 *
 * Metoda rysuje kwadrat, traktując (x, y) jako lewy górny róg, rysując cztery linie.
 *
 * @param x Współrzędna X lewego górnego rogu kwadratu.
 * @param y Współrzędna Y lewego górnego rogu kwadratu.
 * @param size Rozmiar kwadratu.
 * @param color Kolor konturu kwadratu.
 */
void PrimitiveRenderer::DrawSquare(int x, int y, int size, SDL_Color color) {
    // Rysowanie czterech boków kwadratu
    DrawLine(x, y, x + size, y, color);           // góra
    DrawLine(x + size, y, x + size, y + size, color); // prawa strona
    DrawLine(x + size, y + size, x, y + size, color); // dół
    DrawLine(x, y + size, x, y, color);             // lewa strona
}

/**
 * @brief Wypełnia okrąg w zadanej pozycji i promieniu.
 *
 * Metoda rysuje okrąg wypełniony w zadanej pozycji (x0, y0) oraz promieniu.
 *
 * @param x0 Współrzędna X środka okręgu.
 * @param y0 Współrzędna Y środka okręgu.
 * @param radius Promień okręgu.
 * @param color Kolor wypełnienia okręgu.
 */
void PrimitiveRenderer::FillCircle(int x0, int y0, int radius, SDL_Color color) {
    for (int dy = -radius; dy <= radius; ++dy) {
        int dx = static_cast<int>(std::floor(std::sqrt(radius * radius - dy * dy)));
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(renderer,
            x0 - dx, y0 + dy,
            x0 + dx, y0 + dy);
    }
}

/**
 * @brief Rysuje kontur okręgu w zadanej pozycji i promieniu.
 *
 * Metoda rysuje kontur okręgu w zadanej pozycji (x0, y0) oraz promieniu, używając algorytmu rysowania okręgu.
 *
 * @param x0 Współrzędna X środka okręgu.
 * @param y0 Współrzędna Y środka okręgu.
 * @param radius Promień okręgu.
 * @param color Kolor konturu okręgu.
 */
void PrimitiveRenderer::DrawCircle(int x0, int y0, int radius, SDL_Color color) {
    int x = 0, y = radius;
    int d = 1 - radius;
    while (x <= y) {
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);
        DrawPoint(x0 + y, y0 + x, color);
        DrawPoint(x0 - y, y0 + x, color);
        DrawPoint(x0 + y, y0 - x, color);
        DrawPoint(x0 - y, y0 - x, color);
        if (d < 0) d += 2 * x + 3;
        else { d += 2 * (x - y) + 5; y--; }
        x++;
    }
}

/**
 * @brief Wypełnia elipsę w zadanej pozycji i rozmiarach.
 *
 * Metoda wypełnia elipsę w zadanej pozycji (x0, y0) oraz promieniach rx i ry.
 *
 * @param x0 Współrzędna X środka elipsy.
 * @param y0 Współrzędna Y środka elipsy.
 * @param rx Promień elipsy w osi X.
 * @param ry Promień elipsy w osi Y.
 * @param color Kolor wypełnienia elipsy.
 */
void PrimitiveRenderer::FillEllipse(int x0, int y0, int rx, int ry, SDL_Color color) {
    for (int dy = -ry; dy <= ry; ++dy) {
        float frac = 1.0f - float(dy * dy) / (ry * ry);
        int dx = static_cast<int>(std::floor(rx * std::sqrt(frac)));
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderLine(renderer,
            x0 - dx, y0 + dy,
            x0 + dx, y0 + dy);
    }
}

/**
 * @brief Rysuje kontur elipsy w zadanej pozycji i rozmiarach.
 *
 * Metoda rysuje kontur elipsy w zadanej pozycji (x0, y0) oraz promieniach rx i ry.
 *
 * @param x0 Współrzędna X środka elipsy.
 * @param y0 Współrzędna Y środka elipsy.
 * @param rx Promień elipsy w osi X.
 * @param ry Promień elipsy w osi Y.
 * @param color Kolor konturu elipsy.
 */
void PrimitiveRenderer::DrawEllipse(int x0, int y0, int rx, int ry, SDL_Color color) {
    int x = 0, y = ry;
    long rxSq = long(rx) * rx, rySq = long(ry) * ry;
    long d1 = rySq - rxSq * ry + rxSq / 4;
    long dx = 2 * rySq * x, dy = 2 * rxSq * y;
    // region 1
    while (dx < dy) {
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);
        if (d1 < 0) { x++; dx += 2 * rySq; d1 += dx + rySq; }
        else { x++; y--; dx += 2 * rySq; dy -= 2 * rxSq; d1 += dx - dy + rySq; }
    }
    // region 2
    long d2 = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;
    while (y >= 0) {
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);
        if (d2 > 0) { y--; dy -= 2 * rxSq; d2 += rxSq - dy; }
        else { y--; x++; dx += 2 * rySq; dy -= 2 * rxSq; d2 += dx - dy + rxSq; }
    }
}

/**
 * @brief Wypełnia wielokąt w zadanej pozycji z kolorami.
 *
 * Metoda wypełnia wielokąt z zadanymi punktami i kolorem za pomocą algorytmu linii skanowania.
 *
 * @param pts Wektor punktów wierzchołków wielokąta.
 * @param color Kolor wypełnienia.
 */
void PrimitiveRenderer::FillPolygon(const std::vector<SDL_Point>& pts, SDL_Color color) {
    if (pts.size() < 3) return;
    int minY = pts[0].y, maxY = pts[0].y;
    for (auto& p : pts) { minY = std::min(minY, p.y); maxY = std::max(maxY, p.y); }
    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> xints;
        for (size_t i = 0, j = pts.size() - 1; i < pts.size(); j = i++) {
            auto& p1 = pts[i], & p2 = pts[j];
            if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
                float x = p1.x + float(y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                xints.push_back(int(std::floor(x)));
            }
        }
        if (xints.empty()) continue;
        std::sort(xints.begin(), xints.end());
        for (size_t k = 0; k + 1 < xints.size(); k += 2) {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderLine(renderer, xints[k], y, xints[k + 1], y);
        }
    }
}

/**
 * @brief Rysuje kontur wielokąta.
 *
 * Metoda rysuje kontur wielokąta, łącząc kolejne punkty linii.
 *
 * @param pts Wektor punktów wierzchołków wielokąta.
 * @param color Kolor konturu.
 */
void PrimitiveRenderer::DrawPolygon(const std::vector<SDL_Point>& pts, SDL_Color color) {
    if (pts.size() < 2) return;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (size_t i = 0; i + 1 < pts.size(); ++i)
        SDL_RenderLine(renderer, pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
}
