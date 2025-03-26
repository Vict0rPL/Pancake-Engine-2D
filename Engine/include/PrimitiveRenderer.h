#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <SDL3/SDL.h>

class PrimitiveRenderer {
public:
    // Constructor
    PrimitiveRenderer(SDL_Renderer* renderer);

    // Draws a single point at (x, y) using the specified color (black)
    void DrawPoint(int x, int y, SDL_Color color = { 0, 0, 0, 255 });

private:
    SDL_Renderer* renderer;
};

#endif // PRIMITIVERENDERER_H
