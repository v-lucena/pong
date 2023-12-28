#include "Game.h"
#include "ResourceManager.h"


Game::Game(const unsigned int width, const unsigned int height)
	: Mode(GAME_ACTIVE), Width(width), Height(height)
{
}

Game::~Game()
{
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", nullptr, "sprite");

	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
}

void Game::ProcessInput(float deltaTime)
{
}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
}

void Game::ResetPlayers()
{
}

void Game::DoCollisions()
{
}
