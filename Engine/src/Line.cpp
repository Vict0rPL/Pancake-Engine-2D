#include "Line.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include <cmath>

Line::Line(const Point2D& start, const Point2D& end)
    : GameObject("Line"), startPoint(start), endPoint(end)
{
}

void Line::Draw(PrimitiveRenderer& renderer) const {
    renderer.DrawLine(
        static_cast<int>(startPoint.GetX()),
        static_cast<int>(startPoint.GetY()),
        static_cast<int>(endPoint.GetX()),
        static_cast<int>(endPoint.GetY())
    );
}

void Line::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer pr(renderer);
    Draw(pr);
}

nlohmann::json Line::ToJson() const {
    nlohmann::json j;
    j["type"] = "Line";
    j["start"] = { {"x", startPoint.GetX()}, {"y", startPoint.GetY()} };
    j["end"] = { {"x", endPoint.GetX()}, {"y", endPoint.GetY()} };
    return j;
}
