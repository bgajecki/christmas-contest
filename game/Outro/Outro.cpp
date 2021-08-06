#include "Outro.hpp"

namespace Game
{
	Outro::Outro(void* ptr)
		: Engine::ProcessWithPointer(ptr)
	{
	}
	void Outro::Display()
	{
		this->entityManagement.DrawsEntitys();
	}
	void Outro::Special(int, int, int)
	{
	}
	void Outro::OnKeyDown(unsigned char key, int x, int y)
	{
	}
	void Outro::OnMouseClick(int, int, int, int)
	{
	}
	void Outro::Time(int)
	{
		if (this->endTimmer >= constants::Outro::END_TIME)
			this->End();
		else
			this->endTimmer++;
	}
	void Outro::End()
	{
		this->processManagement->resetProcess();
	}
	BadEnding::BadEnding(void* ptr)
		: Outro(ptr)
	{
		Engine::Texture texture = Engine::loadTextureBMP(constants::Outro::BADENDING_TEXTURE);
		this->endText = this->entityManagement.addEntity();
		this->endText->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->endText->setTexture(texture);
		this->endTimmer = 0u;
	}
	GoodEnding::GoodEnding(void* ptr)
		: Outro(ptr)
	{
		Engine::Texture texture = Engine::loadTextureBMP(constants::Outro::GOODENDING_TEXTURE);
		this->endText = this->entityManagement.addEntity();
		this->endText->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->endText->setTexture(texture);
		this->endTimmer = 0u;
	}
}