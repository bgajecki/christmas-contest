#include "Intro.hpp"

namespace Game
{
	Intro::Intro(void* ptr)
		: Engine::ProcessWithPointer(ptr)
	{
		Engine::Texture texture = Engine::loadTexture(constants::Intro::INTRO_TEXTURE);
		this->intro = this->entityManagement.addEntity();
		this->intro->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->intro->setTexture(texture);

		texture = Engine::loadTextureBMP(constants::Intro::BACKGROUND_TEXTURE);
		this->background = this->entityManagement.addEntity();
		this->background->setTexture(texture);

		texture = Engine::loadTextureBMP(constants::Intro::TITLE_TEXTURE);
		this->title = this->entityManagement.addEntity();
		this->title->setTexture(texture);

		texture = Engine::loadTextureBMP(constants::Intro::CRAWL_TEXTURE);
		this->crawl = this->entityManagement.addEntity();
		this->crawl->setTexture(texture);

		texture = Engine::loadTextureBMP(constants::Intro::BACKGROUND_TEXTURE);
		this->black = this->entityManagement.addEntity();
		this->black->setTexture(texture);

		this->isTitleEnd = false;
		this->crawlTimmer = 0;
		this->timmer = 0;
	}
	void Intro::Display()
	{
		this->entityManagement.DrawsEntitys();
	}
	void Intro::Special(int, int, int)
	{
	}
	void Intro::OnKeyDown(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case constants::Engine::SPACEBAR: // Spacebar
			PlaySound(NULL, NULL, 0);
			this->processManagement->Next();
			break;
		}
	}
	void Intro::OnMouseClick(int, int, int, int)
	{
	}
	void Intro::Time(int)
	{
		this->entityManagement.Run();
		this->Play();
		this->timmer++;
	}

	void Intro::Play()
	{
		if (this->timmer > constants::Intro::TITLE_START_TIME)
		{
			if (this->intro != nullptr)
			{
				PlaySound(constants::Intro::STAR_WARS_THEME, NULL, SND_ASYNC);
				this->intro->timmer = [](std::unique_ptr<Engine::Entity>& ptr)
				{
					ptr.reset();
				};
				this->intro = nullptr;
				this->background->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
				this->title->setRect(Engine::Position_t(-1.1, -1.1), Engine::Size_t(2.2, 2.2));
				this->title->timmer = [=](std::unique_ptr<Engine::Entity>& ptr)
				{
					Engine::Position_t pos = ptr->getPosition();
					Engine::Size_t size = ptr->getSize();
					double difference = 0.025;
					pos.x += difference / 2.0;
					pos.y += difference / 2.0;
					size.width -= difference;
					size.height -= difference;
					ptr->setRect(pos, size);
					
					if (size.width <= 0.0 || size.height <= 0.0) // End
					{
						this->title = nullptr;
						ptr.reset();
					}
					else if (size.width <= 0.5 || size.height <= 0.5) // Subtitle start
					{
						this->isTitleEnd = true;
					}
				};
			}
			else if(this->isTitleEnd)
			{
				this->crawl->setRect(Engine::Position_t(-1.0, -2.0), Engine::Size_t(2.0, 1.0));
				this->black->setRect(Engine::Position_t(-1.0, 0.65), Engine::Size_t(2.0, 0.35));
				this->crawl->addMotion(Engine::Motion_t(Engine::DegreesToRadians(90.0), 0.001, 0.0));
				this->crawl->timmer = [=](std::unique_ptr<Engine::Entity>& ptr)
				{
					Engine::Position_t pos = ptr->getPosition();
					Engine::Size_t size = ptr->getSize();
					double difference = 0.002;
					pos.x += difference / 2.0;
					size.width -= difference;
					size.height -= difference / 2.0;
	
					ptr->setRect(pos, size);
					if (pos.y >= 0.65)
					{
						PlaySound(NULL, NULL, 0);
						this->processManagement->Next();
					}

				};
				this->isTitleEnd = false;
			}
			
		}
	}
}