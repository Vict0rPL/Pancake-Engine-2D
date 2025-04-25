// Ellipse.h 
#pragma once 
#include "GameObject.h" 
#include "TransformableObject.h"
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Ellipse : public GameObject, public TransformableObject {
public: // (x, y) – srodek, rx, ry – promienie w osi x i y 
	Ellipse(int cx, int cy, int rx, int ry,
		SDL_Color fill, SDL_Color outline);
	virtual void Draw(PrimitiveRenderer& renderer) const; 
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 

	void Translate(float dx, float dy)          override;
	void Rotate(float angleRad)              override;
	void Scale(float sx, float sy)          override;


	int GetX()  const { return x; }
	int GetY()  const { return y; }

private: 
	int x, y, rx, ry; 
	SDL_Color fillColor, outlineColor;
};