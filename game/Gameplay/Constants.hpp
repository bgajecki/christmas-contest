#pragma once

namespace constants
{
	namespace Gameplay
	{
		constexpr uint8_t MAX_ENEMY = 100u;
		constexpr uint8_t NUMBER_OF_ENEMY_TEXTURES = 4u;
		constexpr uint8_t ENEMY_SPAWN_TIME = 10u;
		constexpr uint8_t MAX_ENEMY_SPEED = 10u;
		constexpr uint8_t MAX_ENEMY_ACCELERATION = 5u;
		constexpr uint16_t GOOD_ENDING_TIME = 600u; // One minute
		constexpr char BACKGROUND_TEXTURE[] = "graphics//white.bmp";
		constexpr char CHOINKA_TEXTURE[] = "graphics//choinka.png";
		constexpr char ENEMY_TEXTURES[NUMBER_OF_ENEMY_TEXTURES][21] = { "graphics//enemy1.png", "graphics//enemy2.png", "graphics//enemy3.png", "graphics//enemy4.png"};
	}
}

