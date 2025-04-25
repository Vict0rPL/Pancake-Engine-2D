// Square.h
#pragma once
#include "GameObject.h" 
#include "TransformableObject.h"
#include "PrimitiveRenderer.h" 
#include <nlohmann/json.hpp>

class Square : public GameObject, public TransformableObject {
public: // (x, y) – lewy górny róg, size – długość boku 
	Square(int x, int y, int size, SDL_Color fill, SDL_Color outline);
	virtual void Draw(PrimitiveRenderer& renderer) const;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual nlohmann::json ToJson() const override; 

	void Translate(float dx, float dy)          override;
	void Rotate(float angleRad)              override;
	void Scale(float sx, float sy)          override;


	int GetX()    const { return x; }
	int GetY()    const { return y; }
	int GetSize() const { return size; }

	SDL_FRect GetRect() const {
		return {
			GetPosition().x,
			GetPosition().y,
			static_cast<float>(size),
			static_cast<float>(size)
		};
	}



private: 
	int x, y, size; 
	SDL_Color fillColor, outlineColor;
};