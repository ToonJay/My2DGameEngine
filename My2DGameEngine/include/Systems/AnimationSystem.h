#pragma once

#include "Components/AnimationComponent.h"
#include "Components/SpriteComponent.h"
#include <entt.hpp>
#include <SDL.h>

class AnimationSystem {
public:
	AnimationSystem() = default;

	static void Update(std::unique_ptr<entt::registry>& registry) {
		auto view = registry->view<Animation, Sprite>();

		for (auto entity : view) {
			auto& animation = view.get<Animation>(entity);
			auto& sprite = view.get<Sprite>(entity);

			animation.currentFrame = (SDL_GetTicks() - animation.startTime) * animation.animationSpeed / 1000 % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};