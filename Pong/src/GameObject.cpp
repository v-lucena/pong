#include "GameObject.h"

GameObject::GameObject()
	: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Rotation(0.0f)
{
}

GameObject::GameObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity)
	: Position(position), Size(size), Velocity(velocity), Rotation(0.0f)
{
}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Position, this->Size, this->Rotation);
}
