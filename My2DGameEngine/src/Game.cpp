#include "Game.h"
#include "Components.h"
#include "Systems.h"
#include <iostream>

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

void Game::Setup() {
	assetManager->AddTexture(renderer.get(), "pixel-line-platformer", "./assets/tilemaps/tilemap_packed.png");

	const auto entity = registry->create();
	registry->emplace<TransformComponent>(entity, glm::vec2(virtualWidth/2, virtualHeight/2), glm::vec2(1.0, 1.0));
	registry->emplace<SpriteComponent>(entity, "pixel-line-platformer", 16, 16, SDL_FLIP_NONE, 0, false, 0, 64);
	registry->emplace<AnimationComponent>(entity, 2, 10, true);
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
	AnimationSystem::Update(registry);
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());

	RenderSystem::Update(renderer.get(), registry, assetManager);

	SDL_RenderPresent(renderer.get());
}

void Game::Run() {
	Setup();
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