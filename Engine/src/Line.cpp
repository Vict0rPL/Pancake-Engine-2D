#include "Line.h"
#include "Transform.h"          // for Mat3
#include <algorithm>            // for std::min/std::max if needed

Line::Line(const Point2D& s, const Point2D& e)
    : GameObject("Line")
    , startPoint(s)
    , endPoint(e)
{
    // pick up any color you want; could also pass it in ctor
    outlineColor = { 0, 0, 0, 255 };
    // position, rotation, scale are defaulted in TransformableObject
}

void Line::Draw(PrimitiveRenderer& rdr) const {
    // 1) local endpoints
    Vector2 p1{ startPoint.GetX(), startPoint.GetY() };
    Vector2 p2{ endPoint.GetX(),   endPoint.GetY() };

    // 2) build T·R·S around this object’s stored position
    Mat3 T = Mat3::Translate(GetPosition().x, GetPosition().y);
    Mat3 R = Mat3::Rotate(GetRotation());
    Mat3 S = Mat3::Scale(GetScale().x, GetScale().y);
    Mat3 M = T * R * S;

    // 3) transform endpoints
    Vector2 w1 = M * p1;
    Vector2 w2 = M * p2;

    // 4) draw the transformed line
    rdr.DrawLine(int(w1.x), int(w1.y),
        int(w2.x), int(w2.y),
        outlineColor);
}

void Line::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

// --- transform overrides simply store the state:

void Line::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

void Line::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

void Line::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Line::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Line";
    j["start"] = { {"x", startPoint.GetX()}, {"y", startPoint.GetY()} };
    j["end"] = { {"x", endPoint.GetX()},   {"y", endPoint.GetY()} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
