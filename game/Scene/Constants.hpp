#pragma once

namespace constants
{
	namespace Scene
	{
		constexpr uint16_t NEXT_ANIMATION = 80u;
		constexpr uint8_t NUMBER_OF_ANIMATION_TEXTURES = 5u;
		constexpr char GAME_MUSIC[] = "music//wham_last_christmas.wav";
		constexpr char ANIMATION_TEXTURES[NUMBER_OF_ANIMATION_TEXTURES][25] = { "graphics//animation1.bmp",
			"graphics//animation2.bmp",
			"graphics//animation3.bmp",
			"graphics//animation4.bmp",
			"graphics//animation5.bmp" };
	}
}