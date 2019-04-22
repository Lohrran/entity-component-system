#ifndef SCENE_H
#define SCENE_H

#include "Pool.h"
#include "GameObject.h"

class Scene
{
	public:
		Scene();
		~Scene();

		GameObject* createGameObject();
		void destroyGameObject(GameObject* obj);

		Pool* getPool();

	protected:
		Pool* pool = new Pool{ };
};
#endif
