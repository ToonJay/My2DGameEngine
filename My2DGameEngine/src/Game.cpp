#include "Game.h"
#include <iostream>

void Game::Initialize() {
	// Add initialization code here
	std::cout << "Game initialized" << std::endl;
}

void Game::Run() {
	// Add game loop code here
	std::cout << "Running game loop" << std::endl;
}

void Game::Destroy() {
	// Add cleanup code here
	std::cout << "Game destroyed" << std::endl;
}