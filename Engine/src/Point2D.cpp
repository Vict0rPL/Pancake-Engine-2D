#include "Point2D.h"

Point2D::Point2D(float x, float y)
    : GameObject("Point2D")
{
    // store the point’s world position in the base class
    SetPosition({ x, y });
    // rotation=0 and scale=(1,1) by default
}

void Point2D::Draw(PrimitiveRenderer& renderer) const {
    // just draw at the stored position
    auto p = GetPosition();
    SDL_Color color{ 0, 0, 0, 255 };
    renderer.DrawPoint(int(p.x), int(p.y), color);
}

void Point2D::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer r(renderer);
    Draw(r);
}

// these just record the transform but don't move the visual point beyond Translate:
void Point2D::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}
void Point2D::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}
void Point2D::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Point2D::ToJson() const {
    auto p = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Point2D";
    j["position"] = { { "x", p.x }, { "y", p.y } };
    j["rotation"] = GetRotation();
    j["scale"] = { { "x", sc.x }, { "y", sc.y } };
    return j;
}
