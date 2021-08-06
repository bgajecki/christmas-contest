#include "Scene.hpp"

namespace Game
{
	Scene::Scene(void* ptr)
		: Engine::ProcessWithPointer(ptr)
	{
		for (unsigned i = 0; i < this->textures.size(); i++)
			this->textures[i] = Engine::loadTextureBMP(constants::Scene::ANIMATION_TEXTURES[i]);
		this->animation = this->entityManagement.addEntity();
		this->animation->setRect(Engine::Position_t(-1.0, -1.0), Engine::Size_t(2.0, 2.0));
		this->AnimationId = 0;
		this->animation->setTexture(this->textures[this->AnimationId]);
		this->timmer = 0;
		this->isOnMusic = false;
	}
	void Scene::Display()
	{
		this->entityManagement.DrawsEntitys();
	}
	void Scene::Special(int key, int x, int y)
	{

	}
	void Scene::OnKeyDown(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case constants::Engine::SPACEBAR: // Spacebar
			this->Next();
			break;
		}
	}
	void Scene::OnMouseClick(int, int, int, int)
	{
	}
	void Scene::Time(int)
	{
		if (this->timmer >= constants::Scene::NEXT_ANIMATION)
			this->Next();
		this->entityManagement.Run();
		this->timmer++;
		if (!this->isOnMusic)
		{
			PlaySound(constants::Scene::GAME_MUSIC, NULL, SND_LOOP | SND_ASYNC);
			this->isOnMusic = true;
		}
	}

	void Scene::Next()
	{
		this->timmer = 0;
		if (this->AnimationId < constants::Scene::NUMBER_OF_ANIMATION_TEXTURES - 1u)
		{
			this->AnimationId++;
			this->animation->setTexture(this->textures[this->AnimationId]);
		}
		else
			this->processManagement->Next();
	}
}