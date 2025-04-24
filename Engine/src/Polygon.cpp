#include "Polygon.h"
#include "PrimitiveRenderer.h"

Polygon::Polygon(const std::vector<SDL_Point>& pts, SDL_Color f, SDL_Color o)
    : GameObject("Polygon"), points(pts), fillColor(f), outlineColor(o) {
}

void Polygon::Draw(PrimitiveRenderer& rdr) const {
    // 1) wypełnienie
    rdr.FillPolygon(points, fillColor);
    // 2) obrys
    std::vector<SDL_Point> closed = points;
    if (closed.front().x != closed.back().x || closed.front().y != closed.back().y)
        closed.push_back(closed.front());
    rdr.DrawPolygon(closed, outlineColor);
}

void Polygon::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Polygon::ToJson() const {
    nlohmann::json j;
    j["type"] = "Polygon";

    // punkty
    j["points"] = nlohmann::json::array();
    for (const auto& p : points) {
        j["points"].push_back({ {"x", p.x}, {"y", p.y} });
    }

    // kolor wypełnienia
    j["fillColor"] = {
        {"r", fillColor.r},
        {"g", fillColor.g},
        {"b", fillColor.b},
        {"a", fillColor.a}
    };

    // kolor obrysu
    j["outlineColor"] = {
        {"r", outlineColor.r},
        {"g", outlineColor.g},
        {"b", outlineColor.b},
        {"a", outlineColor.a}
    };

    return j;
}

