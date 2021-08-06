#pragma once

#include <Engine.hpp>
#include "Constants.hpp"

namespace Game
{
	class Outro : public Engine::ProcessWithPointer
	{
	public:
		Outro(void*);
		void Display() override;
		void Special(int, int, int) override;
		void OnKeyDown(unsigned char, int, int) override;
		void OnMouseClick(int, int, int, int) override;
		void Time(int) override;
	protected:
		void End();
		Engine::Entity* endText;
		uint8_t endTimmer;
	};

	class BadEnding final : public Outro
	{
	public:
		BadEnding(void* ptr);
		~BadEnding() = default;
	};

	class GoodEnding final : public Outro
	{
	public:
		GoodEnding(void* ptr);
		~GoodEnding() = default;
	};
}