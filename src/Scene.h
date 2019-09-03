#ifndef SCENE_H
#define SCENE_H

#include "Pool.h"
#include "GameObject.h"

class Scene
{
	public:
		Scene();
		~Scene();

		Scene(const Scene&) = default;
		Scene& operator = (const Scene&) = delete;
		Scene& operator = (Scene&&) = delete;


		GameObject* createGameObject();
		void destroyGameObject(GameObject* obj);

		std::vector<GameObject*> gameObjects();

	protected:
		Pool* pool = new Pool { };

	private:
		uint32_t entity;
		uint32_t next();
};
#endif