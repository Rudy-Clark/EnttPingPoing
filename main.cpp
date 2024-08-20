#include <iostream>
#include <entt\entt.hpp>
#include "Game.hpp"

int main() {
	Game game{ 720, 720, "Hello World" };
	
	game.Run();

	return 0;
}