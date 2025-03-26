#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer(SDL_Renderer* renderer)
    : renderer(renderer)
{
}

void PrimitiveRenderer::DrawPoint(int x, int y, SDL_Color color) {
    // Set the drawing color and then draw the point
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, x, y);
}
