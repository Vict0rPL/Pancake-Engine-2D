// TransformableObject.h
#pragma once
#include "GameObject.h"

class TransformableObject {
public:
    virtual ~TransformableObject() = default;

    // Transform API — note the uppercase to match your overrides:
    virtual void Translate(float dx, float dy) {
        position += Vector2{ dx,dy };
    }
    virtual void Rotate(float angleRad) {
        rotation += angleRad;
    }
    virtual void Scale(float sx, float sy) {
        scale_ = Vector2{ scale_.x * sx, scale_.y * sy };
    }

    // Accessors
    const Vector2& GetPosition() const { return position; }
    float           GetRotation() const { return rotation; }
    const Vector2& GetScale() const { return scale_; }

    // Setters (for JSON loading)
    void SetPosition(const Vector2& p) { position = p; }
    void SetRotation(float r) { rotation = r; }
    void SetScale(const Vector2& s) { scale_ = s; }

protected:
    Vector2 position{ 0,0 };
    float   rotation{ 0 };
    Vector2 scale_{ 1,1 };
};
