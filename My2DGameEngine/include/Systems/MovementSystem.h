#pragma once

#include "Components/RigidBodyComponent.h"
#include "Components/TransformComponent.h"
#include <entt.hpp>
#include <algorithm>

class MovementSystem {
public:
	MovementSystem() = default;

	static void Update(std::unique_ptr<entt::registry>& registry, const float deltaTime) {
		auto view = registry->view<RigidBody, Transform>();

		for (auto entity : view) {
			auto& rigidbody = view.get<RigidBody>(entity);
			auto& transform = view.get<Transform>(entity);

			transform.position.x += rigidbody.velocity.x * deltaTime;
			transform.position.y += rigidbody.velocity.y * deltaTime;
		}
	}
};