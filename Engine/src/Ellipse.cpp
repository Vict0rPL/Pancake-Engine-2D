#include "Ellipse.h"
#include "PrimitiveRenderer.h"

Ellipse::Ellipse(int x, int y, int rx, int ry)
    : GameObject("Ellipse"), x(x), y(y), rx(rx), ry(ry)
{
}

void Ellipse::Draw(PrimitiveRenderer& renderer) const {
    renderer.DrawEllipse(x, y, rx, ry);
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
    return j;
}
