#include "Polygon.h"
#include "Transform.h"
#include <numeric>

Polygon::Polygon(const std::vector<SDL_Point>& pts,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Polygon")
    , fillColor(fill)
    , outlineColor(outline)
{
    // 1) compute centroid...
    float cx = 0, cy = 0;
    for (auto& p : pts) { cx += p.x; cy += p.y; }
    cx /= pts.size(); cy /= pts.size();

    // 2) set Transform position
    SetPosition({ cx, cy });

    // 3) fill localPts (Vector2) relative to that centroid
    localPts.reserve(pts.size());
    for (auto& p : pts) {
        localPts.push_back({ p.x - cx, p.y - cy });
    }
}


void Polygon::Draw(PrimitiveRenderer& rdr) const {
    // build T·R·S
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    // transform local points into world
    std::vector<SDL_Point> world;
    world.reserve(localPts.size() + 1);
    for (auto& v : localPts) {
        Vector2 w = M * v;
        world.push_back({ int(w.x), int(w.y) });
    }
    // close the loop?
    if (!world.empty() && (world.front().x != world.back().x ||
        world.front().y != world.back().y)) {
        world.push_back(world.front());
    }

    // fill & outline
    rdr.FillPolygon(world, fillColor);
    rdr.DrawPolygon(world, outlineColor);
}

void Polygon::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

// transforms simply update the stored state in the base class:
void Polygon::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}
void Polygon::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}
void Polygon::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Polygon::ToJson() const {
    // compute final world-space vertices for JSON
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    nlohmann::json j;
    j["type"] = "Polygon";
    j["points"] = nlohmann::json::array();
    for (auto& v : localPts) {
        Vector2 w = M * v;
        j["points"].push_back({ {"x", int(w.x)}, {"y", int(w.y)} });
    }
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", GetPosition().x}, {"y", GetPosition().y} };
    j["rotation"] = GetRotation();
    auto sc = GetScale();
    j["scale"] = { {"x", sc.x}, {"y", sc.y} };
    return j;
}
