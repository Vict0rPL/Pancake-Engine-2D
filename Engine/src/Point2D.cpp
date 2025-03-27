// Point2D.cpp
#include "Point2D.h"

Point2D::Point2D(float x, float y)
    : GameObject("Point2D"), x(x), y(y)
{
}

float Point2D::GetX() const {
    return x;
}

float Point2D::GetY() const {
    return y;
}

void Point2D::SetX(float newX) {
    x = newX;
}

void Point2D::SetY(float newY) {
    y = newY;
}

void Point2D::SetCoordinates(float newX, float newY) {
    x = newX;
    y = newY;
}

void Point2D::Draw(PrimitiveRenderer& renderer) const {
    SDL_Color color = { 0, 0, 0, 255 };
    renderer.DrawPoint(static_cast<int>(x), static_cast<int>(y), color);
}

void Point2D::Render(SDL_Renderer* renderer) {
    PrimitiveRenderer primitiveRenderer(renderer);
    Draw(primitiveRenderer);
}

nlohmann::json Point2D::ToJson() const {
    nlohmann::json j;
    j["type"] = "Point2D";
    j["x"] = x;
    j["y"] = y;
    return j;
}
