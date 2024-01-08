#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"


SpriteRenderer* Renderer;
GameObject* Player1;
GameObject* Player2;
BallObject* Ball;

bool pointWon = true;

Game::Game(const unsigned int width, const unsigned int height)
	: Mode(GAME_ACTIVE), Width(width), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player1;
	delete Player2;
    delete Ball;
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

    glm::vec2 ballPos = player1Pos + glm::vec2(PLAYER_SIZE.x + BALL_OFFSET, PLAYER_SIZE.y / 2.0f - BALL_RADIUS);

	Player1 = new GameObject(player1Pos, PLAYER_SIZE);
    Player2 = new GameObject(player2Pos, PLAYER_SIZE);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY);
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
                if (Ball->Stuck)
                    Ball->Position.y -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player1->Position.y <= this->Height - Player1->Size.y)
            {
                Player1->Position.y += velocity;
                if (Ball->Stuck)
                    Ball->Position.y += velocity;
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

        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;

    }
}

void Game::Update(float deltaTime)
{
    Ball->Move(deltaTime, this->Height);

    this->DoCollisions();

    if (Ball->Position.x >= this->Width)
        this->ResetPlayers();
}

void Game::Render()
{
    if (this->Mode == GAME_ACTIVE)
    {
        Player1->Draw(*Renderer);
        Player2->Draw(*Renderer);
        Ball->Draw(*Renderer);
    }
}

void Game::ResetPlayers()
{
    Player1->Position = glm::vec2(
        STAGE_OFFSET - PLAYER_SIZE.x,
        this->Height / 2.0f - PLAYER_SIZE.y
    );
    Player2->Position = glm::vec2(
        this->Width - STAGE_OFFSET,
        this->Height / 2.0f - PLAYER_SIZE.y
    );
    Ball->Reset(Player1->Position + glm::vec2(PLAYER_SIZE.x + BALL_OFFSET, PLAYER_SIZE.y / 2.0f - BALL_RADIUS), INITIAL_BALL_VELOCITY);
}

Collision CheckCollisions(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
    Collision collisionP2 = CheckCollisions(*Ball, *Player2);
    if (!Ball->Stuck && std::get<0>(collisionP2))
    {
        float centerBoard = Player2->Position.y + Player2->Size.y / 2.0f;
        float distance = (Ball->Position.y + Ball->Radius) - centerBoard;
        float percentage = distance / (Player2->Size.y / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.y = INITIAL_BALL_VELOCITY.y * percentage * strength;

        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);

        Ball->Velocity.x = -1.0f * abs(Ball->Velocity.x);
    }

    Collision collisionP1 = CheckCollisions(*Ball, *Player1);
    if (!Ball->Stuck && std::get<0>(collisionP1))
    {
        float centerBoard = Player1->Position.y + Player1->Size.y / 2.0f;
        float distance = (Ball->Position.y + Ball->Radius) - centerBoard;
        float percentage = distance / (Player1->Size.y / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.y = INITIAL_BALL_VELOCITY.y * percentage * strength;

        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);

        Ball->Velocity.x = 1.0f * abs(Ball->Velocity.x);
    }
}

Collision CheckCollisions(BallObject& one, GameObject& two)
{
    glm::vec2 center(one.Position + one.Radius);

    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);

    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

    glm::vec2 closest = aabb_center + clamped;

    difference = closest - center;

    if (glm::length(difference) < one.Radius)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f));
}

Direction VectorDirection(glm::vec2 closest)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f)
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(closest), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
