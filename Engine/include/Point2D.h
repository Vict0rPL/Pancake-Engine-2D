#ifndef POINT2D_H
#define POINT2D_H

#include "GameObject.h"
#include "PrimitiveRenderer.h"

class Point2D : public GameObject {
public:
    // Constructor
    Point2D(float x = 0.0f, float y = 0.0f);

    // Methods to read coordinates
    float GetX() const;
    float GetY() const;

    // Methods to modify coordinates
    void SetX(float newX);
    void SetY(float newY);
    void SetCoordinates(float newX, float newY);

    // Draw the point using the provided PrimitiveRenderer instance
    void Draw(PrimitiveRenderer& renderer) const;

private:
    float x;
    float y;
};

#endif // POINT2D_H
