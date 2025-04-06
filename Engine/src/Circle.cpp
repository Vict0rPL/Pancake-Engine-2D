#include "Circle.h"
#include "PrimitiveRenderer.h"

Circle::Circle(int x, int y, int radius)
    : GameObject("Circle"), x(x), y(y), radius(radius)
{
}

void Circle::Draw(PrimitiveRenderer& renderer) const {
    renderer.DrawCircle(x, y, radius);
}

void Circle::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Circle::ToJson() const {
    nlohmann::json j;
    j["type"] = "Circle";
    j["x"] = x;
    j["y"] = y;
    j["radius"] = radius;
    return j;
}
