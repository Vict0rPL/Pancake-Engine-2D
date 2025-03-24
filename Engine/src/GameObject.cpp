#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const std::string& name)
    : name(name)
{
}

GameObject::~GameObject() {
}

void GameObject::Update(float deltaTime) {
    // Default update
}

void GameObject::Render(SDL_Renderer* /*renderer*/) {
    // Default render
}

