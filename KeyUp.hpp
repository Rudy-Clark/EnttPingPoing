#pragma once
#include "raylib.h"

struct KeyUp final {
	KeyboardKey key{};

	inline KeyUp(KeyboardKey in_key)
		: key(in_key)
	{}

	KeyUp(KeyUp&& other) noexcept = default;

	KeyUp(const KeyUp&) = delete;
	KeyUp& operator=(const KeyUp&) = delete;
	KeyUp& operator=(KeyUp&& other) noexcept = default;
};
