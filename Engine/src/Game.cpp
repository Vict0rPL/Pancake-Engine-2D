#include "Game.h"
#include <iostream>

Game::Game() {
    std::cout << "Game constructed.\n";
}

Game::~Game() {
    // Destructor implementation
}

void Game::Load() {
    std::cout << "Game::Load() called. Initialize game objects here.\n";
}

void Game::Update(float deltaTime) {
    // Update game logic
}

void Game::Render(SDL_Renderer* renderer) {
    // Render game objects
}
