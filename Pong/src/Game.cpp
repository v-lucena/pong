#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"


SpriteRenderer* Renderer;
GameObject* Player1;
GameObject* Player2;

Game::Game(const unsigned int width, const unsigned int height)
	: Mode(GAME_ACTIVE), Width(width), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player1;
	delete Player2;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", nullptr, "sprite");

	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	glm::vec2 player1Pos = glm::vec2(
		STAGE_OFFSET - PLAYER_SIZE.x,
		this->Height/2.0f - PLAYER_SIZE.y
	);

    glm::vec2 player2Pos = glm::vec2(
        this->Width - STAGE_OFFSET ,
        this->Height / 2.0f - PLAYER_SIZE.y
    );

	Player1 = new GameObject(player1Pos, PLAYER_SIZE);
    Player2 = new GameObject(player2Pos, PLAYER_SIZE);
}

void Game::ProcessInput(float deltaTime)
{
    if (this->Mode == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * deltaTime;
        
        // move player 1
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player1->Position.y  >= 0.0f)
            {
                Player1->Position.y -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player1->Position.y <= this->Height - Player1->Size.y)
            {
                Player1->Position.y += velocity;
            }
        }

        // move player 2
        if (this->Keys[GLFW_KEY_UP])
        {
            if (Player2->Position.y >= 0.0f)
            {
                Player2->Position.y -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_DOWN])
        {
            if (Player2->Position.y <= this->Height - Player1->Size.y)
            {
                Player2->Position.y += velocity;
            }
        }

    }
}

void Game::Update(float deltaTime)
{
}

void Game::Render()
{
    if (this->Mode == GAME_ACTIVE)
    {
        Player1->Draw(*Renderer);
        Player2->Draw(*Renderer);
    }
}

void Game::ResetPlayers()
{
}

void Game::DoCollisions()
{
}
