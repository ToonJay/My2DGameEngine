#pragma once

#include <glm/glm.hpp>

struct RigidBodyComponent {
	glm::vec2 velocity{0.0f, 0.0f};

	RigidBodyComponent() = default;

	RigidBodyComponent(const glm::vec2& velocity) : velocity{velocity} {}
};