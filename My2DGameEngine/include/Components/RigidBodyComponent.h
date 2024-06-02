#pragma once

#include <glm.hpp>

struct RigidBodyComponent {
	float speed{0};
	glm::vec2 velocity{0.0f, 0.0f};

	RigidBodyComponent() = default;

	RigidBodyComponent(const float speed, const glm::vec2& velocity)
		: speed{speed}, velocity{velocity} {}
};
using RigidBody = RigidBodyComponent;