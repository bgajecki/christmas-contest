#include "Menu.hpp"



namespace Game
{
	Menu::Menu(void* ptr)
		: Engine::ProcessWithPointer(ptr)
	{
		Engine::Texture texture = Engine::loadTextureBMP(constants::Menu::BACKGROUND_TEXTURE);
		this->background = this->entityManagement.addEntity();
		this->background->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->background->setTexture(texture);

		texture = Engine::loadTexture(constants::Menu::CHOINKA_TEXTURE);
		this->choinka = this->entityManagement.addEntity();
		this->choinka->setRect(Engine::Position_t(-0.7, -0.8), Engine::Size_t(0.4, 1.2));
		this->choinka->setTexture(texture);

		texture = Engine::loadTexture(constants::Menu::TEXT_TEXTURE);
		this->text = this->entityManagement.addEntity();
		this->text->setRect(Engine::Position_t(-0.2, -0.4), Engine::Size_t(0.9, 0.3));
		this->text->setTexture(texture);
		this->isTextGrow = true;
		this->text->timmer = [=](std::unique_ptr<Engine::Entity>& ptr)
		{
			Engine::Size_t size = ptr->getSize();
			Engine::Position_t pos = ptr->getPosition();
			double difference = 0.005;

			if (this->isTextGrow)
			{
				size.height += difference;
				size.width += difference;
				pos.x -= difference / 2.0;
				pos.y -= difference / 2.0;

				if (size.width >= 1.0)
					this->isTextGrow = false;
			}
			else
			{
				size.height -= difference;
				size.width -= difference;
				pos.x += difference / 2.0;
				pos.y += difference / 2.0;

				if (size.width <= 0.9)
					this->isTextGrow = true;
			}
			ptr->setSize(size);
			ptr->setPosition(pos);
		};
		
		this->SnowTexture = Engine::loadTexture(constants::Menu::SNOW_TEXTURE);
		this->SnowFunction = [](std::unique_ptr<Engine::Entity>& ptr, const Engine::EntityArray& arr, unsigned i)
		{
			Engine::Motion_t* motion = dynamic_cast<Engine::Motion_t*>(ptr->getMotions()[i].get());
			Engine::Position_t pos = ptr->getPosition();

			if (motion->speed < 0.0)
			{
				motion->speed = 0.1;
				if (motion->direction == Engine::DegreesToRadians(280.0))
				{
					motion->direction = Engine::DegreesToRadians(260.0);
					motion->speed = 0.1;

				}
				else
				{
					motion->direction = Engine::DegreesToRadians(280.0);
					motion->speed = 0.1;
				}
			}
		};
		this->SnowPosition = Engine::Position_t(-1.17, 0.9);
		this->SnowSize = Engine::Size_t(0.04, 0.07);
		this->SnowStartMotion = Engine::Motion_t(Engine::DegreesToRadians(280.0), 0.1, -0.015);
		this->SnowTimmer = 5;
		this->SnowCounter = 1;
		this->SnowCreated = false;
		PlaySound(constants::Menu::MENU_MUSIC, NULL, SND_LOOP | SND_ASYNC);
	}

	void Menu::Display()
	{
		// Start painting
		this->entityManagement.DrawsEntitys();
		// End painting		
	}
	void Menu::Special(int, int, int)
	{
	}
	void Menu::OnKeyDown(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case constants::Engine::SPACEBAR: // Spacebar
			PlaySound(NULL, NULL, 0);
			processManagement->Next();
			break;
		}
	}
	void Menu::OnMouseClick(int, int, int, int)
	{
	}
	void Menu::Time(int)
	{
		this->entityManagement.Run();
		if (this->SnowTimmer > constants::Menu::SNOW_TIME)
		{
			this->SnowTimmer = 0;
			this->CreateSnow(this->SnowPosition);
		}
		else
			this->SnowTimmer++;
	}

	void Menu::CreateSnow(Engine::Position_t pos)
	{
		if (SnowCreated)
		{
			unsigned frame = this->SnowCounter * 10;
			for (unsigned i = frame; i < frame + 10; i++)
			{
				pos.x += 0.2;
				this->snow[i]->setPosition(pos);
				this->snow[i]->deleteMotion(0);
				this->snow[i]->addMotion(this->SnowStartMotion);
			}
		}
		else
		{
			unsigned frame = this->SnowCounter * 10;
			for (unsigned i = frame; i < frame + 10; i++)
			{
				this->snow[i] = this->entityManagement.addEntity();
				pos.x += 0.2;
				this->snow[i]->setRect(pos, this->SnowSize);
				this->snow[i]->addMotion(this->SnowStartMotion);
				this->snow[i]->setTexture(this->SnowTexture);
				this->snow[i]->addMotion(this->SnowStartMotion);
				this->snow[i]->colision = this->SnowFunction;
			}
			if (this->SnowCounter > 8)
				SnowCreated = true;
		}
		if (this->SnowCounter > 8)
			this->SnowCounter = 1;
		else
			this->SnowCounter++;
	}
}