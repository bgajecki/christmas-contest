#pragma once

#include <Engine.hpp>
#include "Constants.hpp"

namespace Game
{
	typedef std::array<Engine::Texture, constants::Scene::NUMBER_OF_ANIMATION_TEXTURES> AnimationTextures;
	class Scene final : public Engine::ProcessWithPointer
	{
	public:
		Scene(void* ptr);
		~Scene() = default;

		void Display() override;
		void Special(int, int, int) override;
		void OnKeyDown(unsigned char, int, int) override;
		void OnMouseClick(int, int, int, int) override;
		void Time(int) override;

	private:
		void Next();

		Engine::Entity* animation;
		AnimationTextures textures;
		uint8_t AnimationId;
		uint8_t timmer;
		bool isOnMusic;
	};
}