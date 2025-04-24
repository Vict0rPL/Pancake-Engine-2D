#include "Circle.h"
#include "PrimitiveRenderer.h"

Circle::Circle(int cx, int cy, int r,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Circle"), x(cx), y(cy), radius(r),
    fillColor(fill), outlineColor(outline) {
}

void Circle::Draw(PrimitiveRenderer& renderer) const {
    renderer.FillCircle(x, y, radius, fillColor);
    renderer.DrawCircle(x, y, radius, outlineColor);
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
    j["fillColor"] = { {"r",fillColor.r},    {"g",fillColor.g},
                         {"b",fillColor.b},    {"a",fillColor.a} };
    j["outlineColor"] = { {"r",outlineColor.r}, {"g",outlineColor.g},
                         {"b",outlineColor.b}, {"a",outlineColor.a} };
    return j;
}
