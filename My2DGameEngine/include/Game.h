#pragma once

#include "AssetManager.h"
#include <entt.hpp>
#include <SDL.h>
#include <spdlog.h>
#include <memory>

class Game {
private:
	bool isRunning{true};
	int screenWidth{0};
	int screenHeight{0};
	int virtualWidth{384};
	int virtualHeight{216};

	std::unique_ptr<entt::registry> registry{std::make_unique<entt::registry>()};
	std::unique_ptr<AssetManager> assetManager{std::make_unique<AssetManager>()};

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};

public:
	Game() {
		spdlog::info("Game constructor called!");
	}
	~Game() {
		spdlog::info("Game destructor called!");
	}

	void Initialize();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Run();
	void Close();
};