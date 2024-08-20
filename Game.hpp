#pragma once

#include "raylib.h"
#include "entt/entt.hpp"
#include "AI.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"
#include "KeyDown.hpp"
#include "KeyUp.hpp"
#include "AISystem.hpp"
#include "CollisionSystem.hpp"
#include "CollisionHolder.hpp"

class Game final
{
public:
	Game(int width, int height, const char* title, int targetFPS = 75);
	
	// delete default constructor
	Game() = delete;
	
	// copy assign and list initialization constructors deleted
	Game& operator=(Game&& otherGame) = delete;
	Game(Game&& otherGame) = delete;
	Game& operator=(const Game& otherGame) = delete;
	Game(const Game& otherGame) = delete;

	~Game() noexcept;

	void Run();

private:
	inline bool GetShouldWindowClose() const { return WindowShouldClose(); };

	entt::registry m_registry;
	entt::dispatcher m_dispatcher;

	// systems
	RenderSystem m_renderSystem{};
	MoveSystem m_moveSystem{};
	AISystem m_aiSystem{};
	CollisionSystem m_collisionSystem{};
	
	// collision
	CollisionHolder m_holder;

	void Tick(const float deltaTime);

	void Events();

	void Update(const float deltaTime);
	void Draw();
};

