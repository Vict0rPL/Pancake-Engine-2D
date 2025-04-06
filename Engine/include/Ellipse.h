// Ellipse.h 
#pragma once 
#include "GameObject.h" 
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Ellipse : public GameObject {
public: // (x, y) – srodek, rx, ry – promienie w osi x i y 
	Ellipse(int x, int y, int rx, int ry); 
	virtual void Draw(PrimitiveRenderer& renderer) const; 
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 
private: 
	int x, y, rx, ry; 
};