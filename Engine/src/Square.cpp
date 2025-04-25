// Square.cpp
#include "Square.h"
#include "Transform.h"   // Mat3
#include <array>

Square::Square(int x, int y, int size,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Square")
    , size(size)
    , fillColor(fill)
    , outlineColor(outline)
{
    // store the top-left in the base transform
    SetPosition({ float(x), float(y) });
}

void Square::Draw(PrimitiveRenderer& rdr) const {
    // half-side
    float hs = size * 0.5f;

    // local corners centered at (0,0)
    std::array<Vector2, 4> local = {
      Vector2{-hs, -hs},
      Vector2{ hs, -hs},
      Vector2{ hs,  hs},
      Vector2{-hs,  hs}
    };

    // build T·R·S: scale, then rotate, then translate to (x+hs,y+hs)
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 T = Mat3::Translate(
        GetPosition().x + hs,
        GetPosition().y + hs
    );
    Mat3 M = T * R * S;

    // transform & collect into SDL_Points
    std::vector<SDL_Point> pts;
    pts.reserve(local.size());
    for (auto& v : local) {
        Vector2 w = M * v;               // needs Mat3 × Vector2 overload
        pts.push_back({ int(w.x), int(w.y) });
    }

    // fill & outline
    rdr.FillPolygon(pts, fillColor);
    rdr.DrawPolygon(pts, outlineColor);
}

void Square::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

// Transform overrides just update the base state:
void Square::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}
void Square::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}
void Square::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Square::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Square";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["size"] = size;  // original side length
    j["fillColor"] = {
        {"r", fillColor.r}, {"g", fillColor.g},
        {"b", fillColor.b}, {"a", fillColor.a}
    };
    j["outlineColor"] = {
        {"r", outlineColor.r}, {"g", outlineColor.g},
        {"b", outlineColor.b}, {"a", outlineColor.a}
    };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},   {"y", sc.y} };
    return j;
}
