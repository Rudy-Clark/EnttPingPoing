#include "Game.hpp"
#include <assert.h>
#include "Settings.hpp"

#define DARK_GREEN	Color{4, 167, 111, 255}
#define LIGHT_GREEN Color{49, 197, 146, 255}
#define LIGHT_GRAY Color{194, 226, 215, 128}


Game::Game(int width, int height, const char* title, int targetFPS)
{
	assert(!IsWindowReady());
	//SetTargetFPS(targetFPS);
	InitWindow(width, height, title);

	auto player_paddle = m_registry.create();
	auto ai_paddle = m_registry.create();
	auto ball = m_registry.create();

	m_registry.emplace<Position>(player_paddle, 10, (height / 2) - 60);
	m_registry.emplace<Sprite>(player_paddle, Settings::paddingWidth, Settings::paddingHeight, GREEN);
	m_registry.emplace<Player>(player_paddle);

	m_registry.emplace<Position>(ai_paddle, width - 30, (height / 2) - 60);
	m_registry.emplace<Sprite>(ai_paddle, Settings::paddingWidth, Settings::paddingHeight, RED);
	m_registry.emplace<AI>(ai_paddle);

	m_registry.emplace<Position>(ball, width / 2, height / 2);
	m_registry.emplace<Sprite>(ball, Settings::ballRadius, YELLOW);
	m_registry.emplace<Ball>(ball, Settings::ballVelocityX, Settings::ballVelocitY);

	m_dispatcher.sink<KeyUp>().connect<&MoveSystem::HandleUpEvent>(m_moveSystem);
	m_dispatcher.sink<KeyDown>().connect<&MoveSystem::HandleDownEvent>(m_moveSystem);

	m_holder.ai = ai_paddle;
	m_holder.player = player_paddle;
	m_holder.ball = ball;
	m_holder.registery = &m_registry;
}

Game::~Game() noexcept
{
	assert(GetWindowHandle());
	CloseWindow();
}

void Game::Tick(const float deltaTime)
{
	BeginDrawing();
	Update(deltaTime);
	Draw();
	EndDrawing();
}

void Game::Events()
{
	// keyboard W
	if (IsKeyDown(KEY_W)) 
	{
		//std::cout << KEY_W;
		m_dispatcher.trigger(KeyDown{KEY_W});
	}
	// keyboard S
	else if (IsKeyDown(KEY_S)) 
	{
		m_dispatcher.trigger(KeyDown{ KEY_S });
	}
	else if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S))
	{
		m_dispatcher.trigger(IsKeyReleased(KEY_W) ? KeyUp{KEY_W} : KeyUp{KEY_S});
	}
}

void Game::Run()
{
	while (!GetShouldWindowClose()) {
		Events();
		Tick(GetFrameTime());
	}
}

void Game::Update(const float deltaTime)
{
	m_moveSystem.update(deltaTime, m_registry);
	m_aiSystem.update(deltaTime, m_registry);
	m_collisionSystem.update(deltaTime, m_holder);
}

void Game::Draw()
{
	ClearBackground(DARK_GREEN);

	DrawRectangle(0, 0, Settings::screenWidth / 2, Settings::screenHeight, LIGHT_GREEN);
	DrawCircle(Settings::screenWidth / 2, Settings::screenHeight / 2, (Settings::screenHeight / 2) - 120, LIGHT_GRAY);
	//Draw center line
	DrawLine(Settings::screenWidth / 2, 0, Settings::screenWidth / 2, Settings::screenHeight, WHITE);
	
	m_renderSystem.Render(m_registry);
	DrawFPS(20, 20);
	//DrawText("Hello World", 720 / 2, 720 / 2, 32, WHITE);
}
