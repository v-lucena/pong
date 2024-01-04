#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "GameObject.h"

class BallObject : public GameObject 
{
public:
	float Radius;

	bool Stuck;

	BallObject();
	BallObject(glm::vec2 position, float radius, glm::vec2 velocity);

	glm::vec2 Move(float deltaTime, unsigned int window_height);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};