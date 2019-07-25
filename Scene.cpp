#include "Scene.h"

Scene::Scene() : entity{ 0 } { }

Scene::~Scene()
{
	pool->clear();
}

GameObject* Scene::createGameObject()
{
	GameObject* obj = new GameObject{ next() };
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

uint32_t Scene::next()
{
	return entity++;
}