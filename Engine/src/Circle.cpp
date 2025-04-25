#include "Circle.h"
#include "PrimitiveRenderer.h"

Circle::Circle(int x, int y, int r,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Circle")
    , radius(r)
    , fillColor(fill)
    , outlineColor(outline)
{
    // initialize the stored position:
    SetPosition({ float(x), float(y) });
    // rotation starts at 0, scale at (1,1) by default
}

void Circle::Draw(PrimitiveRenderer& rdr) const {
    // 1) pull transform state:
    auto pos = GetPosition();
    auto sc = GetScale();
    auto rot = GetRotation();  // for a solid circle this does nothing,
    // but you might animate a texture later

// 2) compute a uniform, “average” radius
    int drawR = int(radius * ((sc.x + sc.y) * 0.5f));

    // 3) draw at the transformed center:
    rdr.FillCircle(int(pos.x), int(pos.y), drawR, fillColor);
    rdr.DrawCircle(int(pos.x), int(pos.y), drawR, outlineColor);
}

void Circle::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

// --- Transform overrides just call the base so we store the state:

void Circle::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

void Circle::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

void Circle::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Circle::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Circle";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["radius"] = radius;
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
