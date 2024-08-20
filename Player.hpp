#pragma once

struct Player {
	enum class MoveDirection {
		STOPPED,
		NORTH,
		SOUTH,
	};
	MoveDirection movementDir{ MoveDirection::STOPPED };
};