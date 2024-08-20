#pragma once

#include <iostream>
#include "entt/entt.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "raylib.h"
#include "KeyDown.hpp"
#include "KeyUp.hpp"
#include "Sprite.hpp"
#include "Settings.hpp"
#include "raymath.h"

struct MoveSystem {
	Player::MoveDirection m_playerMovement{ Player::MoveDirection::STOPPED };

	void update(const float deltaTime, entt::registry& registry) {
		auto player_view = registry.view<Player, Position>();
		player_view.each([&](Player& plr, Position& pos) {
			plr.movementDir = m_playerMovement;
			if (m_playerMovement == Player::MoveDirection::NORTH)
			{
				pos.y = Clamp(pos.y - (300.f * deltaTime), 0.0f, (float)(GetScreenHeight() - Settings::paddingHeight));
			}
			else if (m_playerMovement == Player::MoveDirection::SOUTH)
			{
				pos.y = Clamp(pos.y + (300.f * deltaTime), 0.0f, (float)(GetScreenHeight() - Settings::paddingHeight));
			}
		});

		auto ball_view = registry.view<Ball, Position>();
		ball_view.each([&](Ball& ball, Position& pos) {
			pos.x += ball.vel_x * deltaTime;
			pos.y += ball.vel_y * deltaTime;

			if (pos.x < 0.0) 
			{
				pos.x = GetScreenWidth() / 2;
				pos.y = GetScreenHeight() / 2;
				ball.vel_x = RandomizeVelDir(ball.vel_x);
				ball.vel_y = RandomizeVelDir(ball.vel_y);
			}
			else if (pos.x > GetScreenWidth() - Settings::ballRadius) 
			{
				pos.x = GetScreenWidth() / 2;
				pos.y = GetScreenHeight() / 2;
				ball.vel_x = RandomizeVelDir(ball.vel_x);
				ball.vel_y = RandomizeVelDir(ball.vel_y);
			}

			if (pos.y < 0.f) 
			{
				pos.y = 0.f;
				ball.vel_y *= -1.f;
			}
			else if (pos.y > GetScreenHeight() - Settings::ballRadius)
			{
				pos.y = GetScreenHeight() - Settings::ballRadius;
				ball.vel_y *= -1.f;
			}
		});
	}

	void HandleUpEvent(const KeyUp& keyUp) {
		if (keyUp.key == KEY_W || keyUp.key == KEY_S) 
			m_playerMovement = Player::MoveDirection::STOPPED;
	}

	void HandleDownEvent(const KeyDown& keyDown) {
		switch (keyDown.key)
		{
		case KEY_W: {
			m_playerMovement = Player::MoveDirection::NORTH;
			break;
		}
		case KEY_S: {
			m_playerMovement = Player::MoveDirection::SOUTH;
			break;
		}
		default:
			break;
		}
	}

	float RandomizeVelDir(float vel) {
		int randomSelect = GetRandomValue(0, 1);

		switch (randomSelect) {
		case 0:
			return vel;
			break;
		case 1:
			return -vel;
			break;
		default:
			return vel;
		}
	}
};