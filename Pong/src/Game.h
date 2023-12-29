#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameObject.h"

enum GameMode {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_OVER
};

const glm::vec2 PLAYER_SIZE(20.0f, 100.0f);

const float PLAYER_VELOCITY(500.0f);

const float STAGE_OFFSET = 50.0f;


class Game
{
	

public:
	//state
	GameMode Mode;
	bool	 Keys[1024];
	bool	 ProcessedKeys[1024];
	unsigned int Width, Height;

	Game(const unsigned int width, const unsigned int height);
	~Game();

	void Init();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();

	void ResetPlayers();
	void DoCollisions();
};
