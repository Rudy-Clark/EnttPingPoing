#pragma once

#include "raylib.h"
#include "entt\entt.hpp"

#include "CollisionHolder.hpp"
#include "Ball.hpp"
#include "Position.hpp"
#include "Sprite.hpp"


struct CollisionSystem {
	void update(const float deltaTime, CollisionHolder& holder) {

		Ball& ball = holder.registery->get<Ball>(holder.ball);
		const Position& ball_pos = holder.registery->get<Position>(holder.ball);
		const Sprite& ball_spr = holder.registery->get<Sprite>(holder.ball);

		const Position& player_pos = holder.registery->get<Position>(holder.player);
		const Sprite& player_spr = holder.registery->get<Sprite>(holder.player);

		const Position& ai_pos = holder.registery->get<Position>(holder.ai);
		const Sprite& ai_spr = holder.registery->get<Sprite>(holder.ai);

		Vector2 ballPos = { ball_pos.x, ball_pos.y };

		Rectangle playerRectColl = { player_pos.x, player_pos.y, player_spr.width, player_spr.height };
		if (CheckCollisionCircleRec(ballPos, ball_spr.radius, playerRectColl)) {
			ball.vel_x *= -1.f;
			return;
		}

		Rectangle aiRectColl = { ai_pos.x, ai_pos.y, ai_spr.width, ai_spr.height };
		if (CheckCollisionCircleRec(ballPos, ball_spr.radius, aiRectColl)) {
			ball.vel_x *= -1.f;
			return;
		}
	}
};