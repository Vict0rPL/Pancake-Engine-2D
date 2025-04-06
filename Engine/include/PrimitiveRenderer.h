#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <SDL3/SDL.h>
#include <vector>

class PrimitiveRenderer {
public:
    // Konstruktor
    PrimitiveRenderer(SDL_Renderer* renderer);

    // Rysowanie pojedynczego punktu
    void DrawPoint(int x, int y, SDL_Color color = { 0, 0, 0, 255 });

    // Nowe metody do rysowania prymitywów:
    void DrawLine(int x0, int y0, int x1, int y1, SDL_Color color = { 0, 0, 0, 255 });
    void DrawSquare(int x, int y, int size, SDL_Color color = { 0, 0, 0, 255 });
    void DrawCircle(int x0, int y0, int radius, SDL_Color color = { 0, 0, 0, 255 });
    void DrawEllipse(int x0, int y0, int rx, int ry, SDL_Color color = { 0, 0, 0, 255 });
    void DrawPolygon(const std::vector<SDL_Point>& points, SDL_Color color = { 0, 0, 0, 255 });

private:
    SDL_Renderer* renderer;
};

#endif // PRIMITIVERENDERER_H
