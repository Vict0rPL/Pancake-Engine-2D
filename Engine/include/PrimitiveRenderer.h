#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <SDL3/SDL.h>
#include <vector>

class PrimitiveRenderer {
public:
    PrimitiveRenderer(SDL_Renderer* renderer);

    // Podstawowe prymitywy
    void DrawPoint(int x, int y, SDL_Color color = { 0,0,0,255 });
    void DrawLine(int x0, int y0, int x1, int y1, SDL_Color color = { 0,0,0,255 });

    // Kwadraty
    void DrawSquare(int x, int y, int size, SDL_Color color = { 0,0,0,255 });
    void FillSquare(int x, int y, int size, SDL_Color color = { 0,0,0,255 });

    // Okręgi
    void DrawCircle(int x0, int y0, int radius, SDL_Color color = { 0,0,0,255 });
    void FillCircle(int x0, int y0, int radius, SDL_Color color = { 0,0,0,255 });

    // Elipsy
    void DrawEllipse(int x0, int y0, int rx, int ry, SDL_Color color = { 0,0,0,255 });
    void FillEllipse(int x0, int y0, int rx, int ry, SDL_Color color = { 0,0,0,255 });

    // Wielokąty
    void DrawPolygon(const std::vector<SDL_Point>& pts, SDL_Color color = { 0,0,0,255 });
    void FillPolygon(const std::vector<SDL_Point>& pts, SDL_Color color = { 0,0,0,255 });

private:
    SDL_Renderer* renderer;
};

#endif // PRIMITIVERENDERER_H
