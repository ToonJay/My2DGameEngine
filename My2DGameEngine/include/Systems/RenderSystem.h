#pragma once

#include "AssetManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include <entt.hpp>
#include <SDL_image.h>

class RenderSystem {
public:
	RenderSystem() = default;

	static void Update(SDL_Renderer* renderer, std::unique_ptr<entt::registry>& registry, std::unique_ptr<AssetManager>& assetManager) {
		auto view = registry->view<TransformComponent, SpriteComponent>();

		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& sprite = view.get<SpriteComponent>(entity);

			SDL_Rect srcRect = sprite.srcRect;

			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};

			SDL_RenderCopyEx(
				renderer,
				assetManager->GetTexture(sprite.assetId),
				&srcRect,
				&dstRect,
				0,
				NULL,
				sprite.flip
			);
		}
	}
};