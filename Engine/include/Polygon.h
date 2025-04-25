// Polygon.h
#pragma once
#include "GameObject.h"
#include "PrimitiveRenderer.h"
#include "TransformableObject.h"
#include "Transform.h"            // for Vector2
#include <vector>
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

class Polygon : public GameObject, public TransformableObject {
public:
    // ctor takes world‐space integer points...
    Polygon(const std::vector<SDL_Point>& pts,
        SDL_Color fillColor = { 200,200,200,255 },
        SDL_Color outlineColor = { 0,0,0,255 });

    void Draw(PrimitiveRenderer& renderer) const;
    void Render(SDL_Renderer* renderer)    override;
    nlohmann::json ToJson()                const override;

    // exactly match the base class
    void Translate(float dx, float dy)     override;
    void Rotate(float angleRad)         override;
    void Scale(float sx, float sy)     override;

private:
    // these are the **local** (centroid‐relative) vertices your .cpp expects:
    std::vector<Vector2> localPts;

    // colors
    SDL_Color fillColor;
    SDL_Color outlineColor;
};
