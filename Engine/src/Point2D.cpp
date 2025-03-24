#include "Point2D.h"

Point2D::Point2D(float x, float y)
    : GameObject("Point2D"),
    x(x),
    y(y)
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
    // Cast the float coordinates to int if needed
    renderer.DrawPoint(static_cast<int>(x), static_cast<int>(y));
}
