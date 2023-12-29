#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "SpriteRenderer.h"

class GameObject
{
public:
	glm::vec2 Position, Size, Velocity;
	float Rotation;

	GameObject();
	GameObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity = glm::vec3(0.0f));

	void Draw(SpriteRenderer& renderer);
};