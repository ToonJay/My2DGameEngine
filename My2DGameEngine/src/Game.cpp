#include "Game.h"
#include <spdlog.h>
#include <iostream>

Game::Game() 
	: isRunning{true}, screenWidth{0}, screenHeight{0}, virtualWidth{384}, virtualHeight{216},
	registry{std::make_unique<entt::registry>()},
	window{nullptr, SDL_DestroyWindow},
	renderer{nullptr, SDL_DestroyRenderer} {
	spdlog::info("Game constructor called!");
}

Game::~Game() {
	spdlog::info("Game destructor called!");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		spdlog::error("Error initializing SDL.");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	screenWidth = displayMode.w / 2;
	screenHeight = displayMode.h / 2;
	window.reset(SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN));
	if (!window) {
		spdlog::error("Error creating SDL window.");
		return;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
	if (!renderer) {
		spdlog::error("Error creating SDL renderer.");
		return;
	}
	SDL_RenderSetLogicalSize(renderer.get(), virtualWidth, virtualHeight);

	spdlog::info("Game initialized");
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		}
	}
}

void Game::Update() {

}

void Game::Render() {

}

void Game::Run() {
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Close() {
	SDL_Quit();
	spdlog::info("Game closed");
}