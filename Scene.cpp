#include "Scene.h"

Scene::Scene() { }

Scene::~Scene()
{
	pool->clear();
}

GameObject* Scene::createGameObject()
{
	GameObject* obj = new GameObject{};
	pool->add(obj);
	return obj;
}

void Scene::destroyGameObject(GameObject* obj)
{
	pool->remove(obj);
	delete obj;
}

Pool* Scene::getPool()
{
	return pool;
}
