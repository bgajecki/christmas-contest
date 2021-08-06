#include "Gameplay.hpp"

namespace Game
{
	Gameplay::Gameplay(void* ptr)
		: Engine::ProcessWithPointer(ptr)
	{
		Engine::Texture texture = Engine::loadTextureBMP(constants::Gameplay::BACKGROUND_TEXTURE);
		this->background = this->entityManagement.addEntity();
		this->background->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->background->setTexture(texture);

		texture = Engine::loadTexture(constants::Gameplay::CHOINKA_TEXTURE);
		this->choinka = this->entityManagement.addEntity();
		this->choinka->setRect(Engine::Position_t(-0.1, -0.3), Engine::Size_t(0.2, 0.6));
		this->choinka->setTexture(texture);
		for (unsigned i = 0; i < constants::Gameplay::NUMBER_OF_ENEMY_TEXTURES; i++)
			this->enemyTextures[i] = Engine::loadTexture(constants::Gameplay::ENEMY_TEXTURES[i]);
	
		this->enemyColision = [=](std::unique_ptr<Engine::Entity>& ptr, const Engine::EntityArray& arr, unsigned i)
		{
			Engine::Object_t obj = this->choinka->getObject();
			double betterPrecision = 0.03;
			obj.pos.x += betterPrecision;
			obj.pos.y += 2.0 * betterPrecision; // Christmas tree bough
			obj.size.width -= 2.0 * betterPrecision;
			obj.size.height -= 3.0 * betterPrecision;
			if (this->entityManagement.isColision(ptr->getObject(), obj))
				this->BadEnding();
		};

		for (auto& i : this->enemy)
			i = nullptr;

		this->enemySpawnTimmer = 5u;
		this->isFirstTime = true;
		this->endTimmer = 0u;
	}
	void Gameplay::Display()
	{
		this->entityManagement.DrawsEntitys();
	}
	void Gameplay::Special(int, int, int)
	{
	}
	void Gameplay::OnKeyDown(unsigned char key, int x, int y)
	{
	}
	void Gameplay::OnMouseClick(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			for (unsigned i = 0; i < this->enemy.size(); i++)
			{
				if (this->enemy[i])
				{
					
					if (this->isShotAccurately(x, y, this->enemy[i]))
					{
						
						this->enemy[i]->timmer = [](std::unique_ptr<Engine::Entity>& ptr)
						{
							ptr.reset();
						};
						this->enemy[i] = nullptr;
					}
				}
			}
		}
	}
	void Gameplay::Time(int)
	{
		this->entityManagement.Run();
		if(this->isFirstTime)
			glutSetCursor(GLUT_CURSOR_DESTROY); // Gun sight
		if (this->enemySpawnTimmer >= constants::Gameplay::ENEMY_SPAWN_TIME)
		{
			this->enemySpawnTimmer = 0;
			this->Spawn();
		}
		else
			this->enemySpawnTimmer++;
		if (this->endTimmer >= constants::Gameplay::GOOD_ENDING_TIME)
			this->GoodEnding();
		else
			this->endTimmer++;
	}

	Engine::Angel Gameplay::GetAngelFromPosition(const Engine::Position_t& e1, const Engine::Position_t& e2)
	{
		return atan2(e2.y - e1.y, e2.x - e1.x);
	}

	bool Gameplay::isShotAccurately(int x, int y, Engine::Entity* ptr)
	{
		double max_x = static_cast<double>(GetSystemMetrics(SM_CXSCREEN)) / 2.0,
			max_y = static_cast<double>(GetSystemMetrics(SM_CYSCREEN)) / 2.0;
		double double_x = (static_cast<double>(x) - max_x) / max_x,
			double_y = -((static_cast<double>(y) - max_y) / max_y);
		Engine::Object_t o1(Engine::Position_t(double_x, double_y), Engine::Size_t(0.0, 0.0)),
			o2 = ptr->getObject();
		if (o1.pos.x < o2.pos.x + o2.size.width && o1.pos.x + o1.size.width > o2.pos.x
			&& o1.pos.y < o2.pos.y + o2.size.height && o1.pos.y + o1.size.height > o2.pos.y)
			return true;
		else
			return false;
	}

	void Gameplay::Spawn()
	{
		for(auto& i : this->enemy)
		{
			if (i == nullptr)
			{
				int randomStart = rand() % 4;
				double randomPosition = (((static_cast<double>(rand() % 191)) - 95.0) / 100.0); // from -0.95 to 0.95

				i = this->entityManagement.addEntity();
				i->setTexture(this->enemyTextures[randomStart]);
				i->setSize(Engine::Size_t(0.10, 0.3));

				switch (randomStart)
				{
				case 0: // Góra
					i->setPosition(Engine::Position_t(randomPosition, 0.95));
					break;
				case 1: // Dó³
					i->setPosition(Engine::Position_t(randomPosition, -0.95));
					break;
				case 2: // Prawo
					i->setPosition(Engine::Position_t(0.95, randomPosition));
					break;
				case 3: // Lewo
					i->setPosition(Engine::Position_t(-0.95, randomPosition));
					break;
				}
				//double speed = static_cast<double>(rand() % constants::Gameplay::MAX_ENEMY_SPEED) / 100.0 + 0.01;
				//double acceleration = static_cast<double>(rand() % constants::Gameplay::MAX_ENEMY_ACCELERATION) / 100.0;
				i->addMotion(Engine::Motion_t(this->GetAngelFromPosition(i->getPosition(), Engine::Position_t(0.0, 0.0)), 0.01, 0.0));
				i->colision = this->enemyColision;
				break;
			}
		}
	}
	void Gameplay::BadEnding()
	{
		this->processManagement->Next();
	}
	void Gameplay::GoodEnding()
	{
		this->processManagement->Next();
		this->processManagement->Next();
	}
}