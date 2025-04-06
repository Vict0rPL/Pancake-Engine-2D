#include "Square.h"
#include "PrimitiveRenderer.h"

Square::Square(int x, int y, int size)
    : GameObject("Square"), x(x), y(y), size(size)
{
}

void Square::Draw(PrimitiveRenderer& renderer) const {
    renderer.DrawSquare(x, y, size);
}

void Square::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Square::ToJson() const {
    nlohmann::json j;
    j["type"] = "Square";
    j["x"] = x;
    j["y"] = y;
    j["size"] = size;
    return j;
}
