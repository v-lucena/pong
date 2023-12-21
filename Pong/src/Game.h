#pragma once

enum GameMode {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_OVER
};

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
