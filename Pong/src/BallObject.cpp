#include "BallObject.h"

BallObject::BallObject()
	: GameObject(), Radius(12.5f), Stuck(true)
{
}

BallObject::BallObject(glm::vec2 position, float radius, glm::vec2 velocity)
	: GameObject(position, glm::vec2(radius * 2.0f, radius * 2.0f), velocity), Radius(radius), Stuck(true)
{
}

glm::vec2 BallObject::Move(float deltaTime, unsigned int window_height)
{
	if (!this->Stuck)
	{
		this->Position += this->Velocity * deltaTime;

		if (this->Position.y + this->Size.y > window_height)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = window_height - this->Size.y;
		}
		else if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}

	return this->Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}
