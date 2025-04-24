#include "Ellipse.h"
#include "PrimitiveRenderer.h"

Ellipse::Ellipse(int cx, int cy, int rx, int ry,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Ellipse"),
    x(cx), y(cy), rx(rx), ry(ry),
    fillColor(fill), outlineColor(outline) {
}

void Ellipse::Draw(PrimitiveRenderer& renderer) const {
    renderer.FillEllipse(x, y, rx, ry, fillColor);
    renderer.DrawEllipse(x, y, rx, ry, outlineColor);
}

void Ellipse::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Ellipse::ToJson() const {
    nlohmann::json j;
    j["type"] = "Ellipse";
    j["x"] = x;
    j["y"] = y;
    j["rx"] = rx;
    j["ry"] = ry;
    j["fillColor"] = { {"r",fillColor.r},    {"g",fillColor.g},
                        {"b",fillColor.b},    {"a",fillColor.a} };
    j["outlineColor"] = { {"r",outlineColor.r}, {"g",outlineColor.g},
                         {"b",outlineColor.b}, {"a",outlineColor.a} };
    return j;
}
