#include "Square.h"
#include "PrimitiveRenderer.h"

Square::Square(int x, int y, int size,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Square"), x(x), y(y), size(size),
    fillColor(fill), outlineColor(outline) {
}

void Square::Draw(PrimitiveRenderer& rdr) const {
    rdr.FillSquare(x, y, size, fillColor);
    rdr.DrawSquare(x, y, size, outlineColor);
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
    j["fillColor"] = { {"r",fillColor.r},    {"g",fillColor.g},
                          {"b",fillColor.b},    {"a",fillColor.a} };
    j["outlineColor"] = { {"r",outlineColor.r}, {"g",outlineColor.g},
                          {"b",outlineColor.b}, {"a",outlineColor.a} };
    return j;
}
