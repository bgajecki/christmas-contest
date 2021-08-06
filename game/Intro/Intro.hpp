#pragma once

#include <Engine.hpp>
#include "Constants.hpp"

namespace Game
{

	class Intro final : public Engine::ProcessWithPointer
	{
	public:
		Intro(void* ptr);
		~Intro() = default;

		void Display() override;
		void Special(int, int, int) override;
		void OnKeyDown(unsigned char, int, int) override;
		void OnMouseClick(int, int, int, int) override;
		void Time(int) override;

	private:
		void Play();

		Engine::Entity* intro, * background, * title, * crawl, * black;
		uint8_t timmer, crawlTimmer;
		bool isTitleEnd;
	};
}