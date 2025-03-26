// Point2D.h
#ifndef POINT2D_H
#define POINT2D_H

#include "GameObject.h"
#include "PrimitiveRenderer.h"

class Point2D : public GameObject {
public:
    Point2D(float x, float y);
    float GetX() const;
    float GetY() const;
    void SetX(float newX);
    void SetY(float newY);
    void SetCoordinates(float newX, float newY);
    void Draw(PrimitiveRenderer& renderer) const;

    virtual void Update(float deltaTime) override {}
    virtual void Render(SDL_Renderer* renderer) override;
    virtual nlohmann::json ToJson() const override;

private:
    float x, y;
};

#endif // POINT2D_H
