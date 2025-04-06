#ifndef LINE_H
#define LINE_H

#include "GameObject.h"
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include <nlohmann/json.hpp>

class Line : public GameObject {
public:
    Line(const Point2D& start, const Point2D& end);
    virtual void Draw(PrimitiveRenderer& renderer) const;
    virtual void Render(SDL_Renderer* renderer) override;
    virtual nlohmann::json ToJson() const override;
private:
    Point2D startPoint;
    Point2D endPoint;
};

#endif // LINE_H
