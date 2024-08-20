#pragma once
#include "raylib.h"

struct KeyDown final {
	KeyboardKey key{};

	inline KeyDown(KeyboardKey in_key)
		: key(in_key)
	{}

	KeyDown(KeyDown&& other) noexcept = default;

	KeyDown(const KeyDown&) = delete;
	KeyDown& operator=(const KeyDown&) = delete;
	KeyDown& operator=(KeyDown&& other) noexcept = default;
};
