#pragma once

#include <Engine.hpp>
#include <ctime>
#include <iostream>
#include "Constants.hpp"

namespace Game
{
	typedef std::array<Engine::Entity*, constants::Gameplay::MAX_ENEMY> EnemyArray;
	typedef std::array<Engine::Texture, constants::Gameplay::NUMBER_OF_ENEMY_TEXTURES> EnemyTextures;

	class Gameplay final : public Engine::ProcessWithPointer
	{
	public:
		Gameplay(void* ptr);
		~Gameplay() = default;

		void Display() override;
		void Special(int, int, int) override;
		void OnKeyDown(unsigned char, int, int) override;
		void OnMouseClick(int, int, int, int) override;
		void Time(int) override;



	private:
		Engine::Angel GetAngelFromPosition(const Engine::Position_t& e1, const Engine::Position_t& e2);
		bool isShotAccurately(int, int, Engine::Entity*);
		void Spawn();
		void BadEnding();
		void GoodEnding();

		Engine::Entity* choinka, * background, * endText;
		EnemyArray enemy;
		Engine::ColisionFunction enemyColision;
		
		EnemyTextures enemyTextures;
		uint16_t endTimmer;
		uint8_t enemySpawnTimmer;
		bool isFirstTime;

	};
}