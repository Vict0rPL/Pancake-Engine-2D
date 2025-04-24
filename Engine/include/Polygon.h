// Polygon.h 
#pragma once 
#include "GameObject.h" 
#include "PrimitiveRenderer.h" 
#include <vector> 
#include <SDL3/SDL.h> 
#include <nlohmann/json.hpp>

class Polygon : public GameObject {
public: // Konstruktor przyjmujacy zbiór punktów (wspólrzedne calkowite) 
	Polygon(const std::vector<SDL_Point>& points,
		SDL_Color fillColor = { 200,200,200,255 },
		SDL_Color outlineColor = { 0,0,0,255 });
	virtual void Draw(PrimitiveRenderer& renderer) const; 
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 
private: 
	std::vector<SDL_Point> points; 
	SDL_Color fillColor;
	SDL_Color outlineColor;
};