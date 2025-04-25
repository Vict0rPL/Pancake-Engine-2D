#ifndef LINE_H
#define LINE_H

#include "GameObject.h"
#include "Point2D.h"
#include "TransformableObject.h"
#include "PrimitiveRenderer.h"
#include <nlohmann/json.hpp>

class Line : public GameObject, public TransformableObject {
public:
    Line(const Point2D& start, const Point2D& end);
    virtual void Draw(PrimitiveRenderer& renderer) const;
    virtual void Render(SDL_Renderer* renderer) override;

    // TransformableObject:
    void Translate(float dx, float dy)          override;
    void Rotate(float angleRad)              override;
    void Scale(float sx, float sy)          override;


    virtual nlohmann::json ToJson() const override;

private:
    Point2D startPoint;
    Point2D endPoint;
    SDL_Color outlineColor;
};

#endif // LINE_H
