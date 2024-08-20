#pragma once
#include "entt/entt.hpp"
#include "AI.hpp"
#include "Position.hpp"
#include "Ball.hpp"
#include "Settings.hpp"
#include "raylib.h"
#include "raymath.h"

struct AISystem {
	void update(const float deltaTime, entt::registry& registry) {
		auto ai_view = registry.view<AI, Position>();
		auto ball_view = registry.view<Ball, Position>();
		
		ai_view.each([&](AI& ai, Position& ai_pos) {
			ai.x = ai_pos.x;
			ai.y = ai_pos.y;
			ball_view.each([&](Ball& ball, Position& ball_pos) {
				if (ball_pos.y > (ai_pos.y + (Settings::paddingHeight / 2))) 
				{
				/*	ai_pos.y += 250 * deltaTime;*/
					ai_pos.y = Clamp(ai_pos.y + (250.f * deltaTime), 0.0f, (float)(GetScreenHeight() - Settings::paddingHeight));
				} 
				else if (ball_pos.y < (ai_pos.y + (Settings::paddingHeight / 2)))
				{
					ai_pos.y = Clamp(ai_pos.y - (250.f * deltaTime), 0.0f, (float)(GetScreenHeight() - Settings::paddingHeight));
				}
			});
		});
	}
};