#include "Ellipse.h"
#include "PrimitiveRenderer.h"

Ellipse::Ellipse(int x, int y, int radiusX, int radiusY,
    SDL_Color fill, SDL_Color outline)
    : GameObject("Ellipse")
    , rx(radiusX)
    , ry(radiusY)
    , fillColor(fill)
    , outlineColor(outline)
{
    // initialize the stored position
    SetPosition({ float(x), float(y) });
    // rotation starts at 0, scale at (1,1)
}

void Ellipse::Draw(PrimitiveRenderer& rdr) const {
    // 1) grab transform state
    auto pos = GetPosition();
    auto sc = GetScale();
    // rotation is stored but FillEllipse is axis-aligned

    // 2) compute scaled radii
    int drawRx = int(rx * sc.x);
    int drawRy = int(ry * sc.y);

    // 3) draw at the transformed center
    rdr.FillEllipse(int(pos.x), int(pos.y), drawRx, drawRy, fillColor);
    rdr.DrawEllipse(int(pos.x), int(pos.y), drawRx, drawRy, outlineColor);
}

void Ellipse::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

// --- Transform overrides just call the base:

void Ellipse::Translate(float dx, float dy) {
    TransformableObject::Translate(dx, dy);
}

void Ellipse::Rotate(float angleRad) {
    TransformableObject::Rotate(angleRad);
}

void Ellipse::Scale(float sx, float sy) {
    TransformableObject::Scale(sx, sy);
}

nlohmann::json Ellipse::ToJson() const {
    auto pos = GetPosition();
    auto sc = GetScale();

    nlohmann::json j;
    j["type"] = "Ellipse";
    j["x"] = int(pos.x);
    j["y"] = int(pos.y);
    j["rx"] = rx;
    j["ry"] = ry;
    j["fillColor"] = { {"r", fillColor.r},    {"g", fillColor.g},
                         {"b", fillColor.b},    {"a", fillColor.a} };
    j["outlineColor"] = { {"r", outlineColor.r}, {"g", outlineColor.g},
                         {"b", outlineColor.b}, {"a", outlineColor.a} };
    j["position"] = { {"x", pos.x}, {"y", pos.y} };
    j["rotation"] = GetRotation();
    j["scale"] = { {"x", sc.x},  {"y", sc.y} };
    return j;
}
