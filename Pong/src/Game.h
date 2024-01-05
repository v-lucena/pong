#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>

#include "BallObject.h"

#include <tuple>

enum GameMode {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_OVER
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

const glm::vec2 PLAYER_SIZE(20.0f, 100.0f);

const float PLAYER_VELOCITY(500.0f);

const glm::vec2 INITIAL_BALL_VELOCITY = glm::vec2(350.0f, 100.0f);

const float BALL_RADIUS = 6.25f;

const float STAGE_OFFSET = 50.0f;

const float BALL_OFFSET = 5.0f;


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
