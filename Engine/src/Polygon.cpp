#include "Polygon.h"
#include "PrimitiveRenderer.h"

Polygon::Polygon(const std::vector<SDL_Point>& points)
    : GameObject("Polygon"), points(points)
{
}

void Polygon::Draw(PrimitiveRenderer& renderer) const {
    std::vector<SDL_Point> closedPoints = points;
    if (!points.empty() && !(points.front().x == points.back().x && points.front().y == points.back().y)) {
        closedPoints.push_back(points.front()); // Close the polygon
    }
    renderer.DrawPolygon(closedPoints);
}

void Polygon::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Polygon::ToJson() const {
    nlohmann::json j;
    j["type"] = "Polygon";
    j["points"] = nlohmann::json::array();
    for (const auto& p : points) {
        j["points"].push_back({ {"x", p.x}, {"y", p.y} });
    }
    return j;
}
