// Square.h
#pragma once
#include "GameObject.h" 
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Square : public GameObject {
public: // (x, y) – lewy górny róg, size – długość boku 
	Square(int x, int y, int size, SDL_Color fill, SDL_Color outline);
	virtual void Draw(PrimitiveRenderer& renderer) const;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 
private: 
	int x, y, size; 
	SDL_Color fillColor, outlineColor;
};