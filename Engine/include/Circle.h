// Circle.h 
#pragma once 
#include "GameObject.h" 
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Circle : public GameObject {
public: // (x, y) – srodek, radius – promien 
	Circle(int x, int y, int radius); 
	virtual void Draw(PrimitiveRenderer& renderer) const; 
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 
private: 
	int x, y, radius; 
};