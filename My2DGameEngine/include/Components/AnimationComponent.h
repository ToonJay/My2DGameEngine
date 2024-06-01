#pragma once
#include <SDL.h>

struct AnimationComponent {
	int numFrames{1};
	int currentFrame{0};
	int animationSpeed{1};
	Uint32 startTime{SDL_GetTicks()};
	bool isLooping{true};
	
	AnimationComponent() = default;

	AnimationComponent(const int numFrames, const int animationSpeed, const bool isLooping) 
		: numFrames{numFrames}, animationSpeed{animationSpeed}, isLooping{isLooping} {}
};