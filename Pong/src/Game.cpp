#include "Game.h"

Game::Game(const unsigned int width, const unsigned int height)
	: Mode(GAME_ACTIVE), Width(width), Height(height)
{
}

Game::~Game()
{
}

void Game::Init()
{
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
