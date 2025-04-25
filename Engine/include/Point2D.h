// Point2D.h
#ifndef POINT2D_H
#define POINT2D_H

#include "GameObject.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"
    
class Point2D : public GameObject, public TransformableObject {
public:
    Point2D(float x, float y);
    float GetX() const { return TransformableObject::position.x; }
    float GetY() const { return TransformableObject::position.y; }
    void  SetX(float nx) { TransformableObject::position.x = nx; }
    void  SetY(float ny) { TransformableObject::position.y = ny; }
    void  SetCoordinates(float nx, float ny) {
        TransformableObject::position.x = nx;
        TransformableObject::position.y = ny;
    }


    void Draw(PrimitiveRenderer& renderer) const;

    virtual void Update(float deltaTime) override {}
    virtual void Render(SDL_Renderer* renderer) override;

    // TransformableObject:
    void Translate(float dx, float dy)          override;
    void Rotate(float angleRad)              override;
    void Scale(float sx, float sy)          override;


    virtual nlohmann::json ToJson() const override;

};

#endif // POINT2D_H
