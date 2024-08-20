#pragma once

#include "entt/fwd.hpp"

struct CollisionHolder {
	entt::entity player;
	entt::entity ai;
	entt::entity ball;
	entt::registry* registery;
};