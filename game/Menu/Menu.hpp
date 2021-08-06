#pragma once

#include <Engine.hpp>
#include "Constants.hpp"

namespace Game
{
	typedef std::array<Engine::Entity*, constants::Menu::MAX_SNOW> SnowArray;

	class Menu final : public Engine::ProcessWithPointer
	{
	public:
		Menu(void* ptr);
		~Menu() = default;

		void Display() override;
		void Special(int, int, int) override;
		void OnKeyDown(unsigned char, int, int) override;
		void OnMouseClick(int, int, int, int) override;
		void Time(int) override;
		
	private:
		void CreateSnow(Engine::Position_t);

		Engine::Entity* background, * choinka, * text;
		SnowArray snow;
		
		Engine::ColisionFunction SnowFunction;
		Engine::Texture SnowTexture;
		Engine::Position_t SnowPosition;
		Engine::Size_t SnowSize;
		Engine::Motion_t SnowStartMotion;
		uint8_t SnowTimmer, SnowCounter;
		bool SnowCreated, isTextGrow;
	};
}