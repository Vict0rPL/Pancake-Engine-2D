#include "PrimitiveRenderer.h"
#include <cmath>

// Konstruktor
PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer* renderer)
    : renderer(renderer)
{
}

void PrimitiveRenderer::DrawPoint(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, x, y);
}

// Rysowanie linii metodą przyrostową
void PrimitiveRenderer::DrawLine(int x0, int y0, int x1, int y1, SDL_Color color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    // Jeśli nachylenie m ≤ 1, iterujemy po x
    if (dx >= dy) {
        float m = (dx != 0) ? static_cast<float>(y1 - y0) / dx : 0;
        float y = y0;
        for (int x = x0; x != x1; x += sx) {
            DrawPoint(x, static_cast<int>(round(y)), color);
            y += m * sx;
        }
    }
    // Dla nachylenia m > 1, iterujemy po y
    else {
        float m = (dy != 0) ? static_cast<float>(x1 - x0) / dy : 0;
        float x = x0;
        for (int y = y0; y != y1; y += sy) {
            DrawPoint(static_cast<int>(round(x)), y, color);
            x += m * sy;
        }
    }
    // Narysuj ostatni punkt
    DrawPoint(x1, y1, color);
}

// Rysowanie kwadratu (przyjmujemy, że (x,y) to lewy górny róg)
void PrimitiveRenderer::DrawSquare(int x, int y, int size, SDL_Color color) {
    // Rysujemy cztery boki jako linie
    DrawLine(x, y, x + size, y, color);           // góra
    DrawLine(x + size, y, x + size, y + size, color); // prawa strona
    DrawLine(x + size, y + size, x, y + size, color); // dół
    DrawLine(x, y + size, x, y, color);             // lewa strona
}

// Rysowanie koła przy użyciu ośmiokrotnej symetrii
void PrimitiveRenderer::DrawCircle(int x0, int y0, int radius, SDL_Color color) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;

    while (x <= y) {
        // Rysowanie punktów w ośmiu ćwiartkach
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);
        DrawPoint(x0 + y, y0 + x, color);
        DrawPoint(x0 - y, y0 + x, color);
        DrawPoint(x0 + y, y0 - x, color);
        DrawPoint(x0 - y, y0 - x, color);

        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// Rysowanie elipsy z wykorzystaniem symetrii
void PrimitiveRenderer::DrawEllipse(int x0, int y0, int rx, int ry, SDL_Color color) {
    int x = 0;
    int y = ry;
    // Decyzja dla regionu 1
    long rxSq = static_cast<long>(rx * rx);
    long rySq = static_cast<long>(ry * ry);
    long d1 = rySq - rxSq * ry + 0.25 * rxSq;
    long dx = 2 * rySq * x;
    long dy = 2 * rxSq * y;

    while (dx < dy) {
        // Rysowanie symetrycznych punktów
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);

        if (d1 < 0) {
            x++;
            dx += 2 * rySq;
            d1 += dx + rySq;
        }
        else {
            x++;
            y--;
            dx += 2 * rySq;
            dy -= 2 * rxSq;
            d1 += dx - dy + rySq;
        }
    }

    // Region 2
    long d2 = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;
    while (y >= 0) {
        DrawPoint(x0 + x, y0 + y, color);
        DrawPoint(x0 - x, y0 + y, color);
        DrawPoint(x0 + x, y0 - y, color);
        DrawPoint(x0 - x, y0 - y, color);

        if (d2 > 0) {
            y--;
            dy -= 2 * rxSq;
            d2 += rxSq - dy;
        }
        else {
            y--;
            x++;
            dx += 2 * rySq;
            dy -= 2 * rxSq;
            d2 += dx - dy + rxSq;
        }
    }
}

void PrimitiveRenderer::DrawPolygon(const std::vector<SDL_Point>& points, SDL_Color color) {
    if (points.size() < 2) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Rysuj linie pomiędzy wszystkimi punktami
    for (size_t i = 0; i < points.size() - 1; ++i) {
        SDL_RenderLine(renderer, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }

    // Zamknij polygon (ostanti punkt do pierwszego punktu)
    SDL_RenderLine(renderer, points.back().x, points.back().y, points.front().x, points.front().y);
}

