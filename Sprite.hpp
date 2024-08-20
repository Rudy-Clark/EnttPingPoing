#pragma once
#include "raylib.h"

struct Sprite {
	float radius{};
	float width{};
	float height{};
	Color color{};

	Sprite(float in_width, float in_height, Color in_color)
		: width(in_width)
		, height(in_height)
		, color(in_color)
	{}

	Sprite(float in_radius, Color in_color)
		: radius{ in_radius }
		, color{ in_color }
	{}

};