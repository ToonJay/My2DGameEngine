#pragma once

#include "Components/PlayerTagComponent.h"
#include "Components/RigidBodyComponent.h"
#include "EventBus/EventBus.h"
#include "Events/KeyPressEvent.h"
#include <entt.hpp>
#include <SDL.h>

class PlayerControllerSystem {
private:
	float deltaTime{0.0};

public:
	PlayerControllerSystem() = default;

	static void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressEvent>(OnKeyPress);
	}

	static void OnKeyPress(std::unique_ptr<entt::registry>& registry, KeyPressEvent& event) {
		auto view = registry->view<PlayerTag, RigidBody>();

		for (auto entity : view) {
			auto& rigidbody = view.get<RigidBody>(entity);

			switch (event.symbol) {
				case SDLK_RIGHT:
					rigidbody.velocity.x = rigidbody.speed;
					break;
				case SDLK_LEFT:
					rigidbody.velocity.x = -rigidbody.speed;
					break;
				case SDLK_DOWN:
					rigidbody.velocity.x = 0.0;
					break;
			}
		}
	}
};