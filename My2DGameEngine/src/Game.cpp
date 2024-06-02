#include "Game.h"
#include "Components.h"
#include "Systems.h"
#include "Events/KeyPressEvent.h"
#include <iostream>

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		spdlog::error("Error initializing SDL.");
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	
	if (screenWidth > displayMode.w || screenHeight > displayMode.h) {
		screenWidth /= 2;
		screenHeight /= 2;

	}

	window.reset(SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS));
	if (!window) {
		spdlog::error("Error creating SDL window.");
		return;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (!renderer) {
		spdlog::error("Error creating SDL renderer.");
		return;
	}
	SDL_RenderSetLogicalSize(renderer.get(), virtualWidth, virtualHeight);

	spdlog::info("Game initialized");
}

void Game::Setup() {
	assetManager->AddTexture(renderer.get(), "bunny-image", "./assets/images/bunny.png");

	const entt::entity entity = registry->create();
	registry->emplace<Transform>(entity, glm::vec2(10, virtualHeight/2), glm::vec2(2.0, 2.0));
	registry->emplace<RigidBody>(entity, 100.0, glm::vec2(0.0, 0.0));
	registry->emplace<Sprite>(entity, "bunny-image", 16, 16, SDL_FLIP_NONE, 0, false, 0, 0);
	registry->emplace<Animation>(entity, 2, 10, true);
	registry->emplace<BoxCollider>(entity, 16, 16, glm::vec2(0, 0));
	registry->emplace<PlayerTag>(entity);
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
			if (sdlEvent.key.keysym.sym == SDLK_d) {
				isDebug = !isDebug;
			}
			eventBus->EmitEvent<KeyPressEvent>(registry, sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			break;
		}
	}
}

void Game::Update() {
	deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0;
	previousFrameTime = SDL_GetTicks();

	eventBus->Reset();

	PlayerControllerSystem::SubscribeToEvents(eventBus);

	AnimationSystem::Update(registry);
	MovementSystem::Update(registry, deltaTime);
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(renderer.get());

	RenderSystem::Update(renderer.get(), registry, assetManager);

	if (isDebug) {
		RenderColliderSystem::Update(renderer.get(), registry);
	}

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