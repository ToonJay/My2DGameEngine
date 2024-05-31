#pragma once

#include <entt.hpp>
#include <SDL.h>
#include <memory>

class Game {
private:
	bool isRunning;
	int screenWidth;
	int screenHeight;
	int virtualWidth;
	int virtualHeight;

	std::unique_ptr<entt::registry> registry;

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

public:
	Game();
	~Game();

	void Initialize();
	void ProcessInput();
	void Update();
	void Render();
	void Run();
	void Close();
};