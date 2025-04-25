// Circle.h 
#pragma once 
#include "GameObject.h" 
#include "TransformableObject.h"
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Circle : public GameObject, public TransformableObject {
public: // (x, y) – srodek, radius – promien 
	Circle(int cx, int cy, int r, SDL_Color fill, SDL_Color outline);
	virtual void Draw(PrimitiveRenderer& renderer) const; 
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 

	// TransformableObject:
	void Translate(float dx, float dy)          override;
	void Rotate(float angleRad)              override;
	void Scale(float sx, float sy)          override;


	// center getter
	int GetX() const { return x; }
	int GetY() const { return y; }

private: 
	int x, y, radius; 
	SDL_Color fillColor, outlineColor;
};