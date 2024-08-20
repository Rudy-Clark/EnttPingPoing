#pragma once

#include "entt/entt.hpp"
#include "Sprite.hpp"
#include "Position.hpp"
#include "raylib.h"

struct RenderSystem {
	void Render(entt::registry& registry) {
		auto view = registry.view<Sprite, Position>();
		view.each([&](Sprite& spr, Position& pos) {
			if (spr.radius != 0) {
				DrawCircle((int)pos.x, (int)pos.y, spr.radius, spr.color);
			}
			else
			{
				DrawRectangleRounded({pos.x, pos.y, spr.width, spr.height}, 0.8f, 0, spr.color);
			}
		});
	}
};