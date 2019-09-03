#include "Scene.h"

Scene::Scene() : entity{ 0 } { }

Scene::~Scene()
{
	delete pool;
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
}

std::vector<GameObject*> Scene::gameObjects()
{
	return pool->getItems();
}

uint32_t Scene::next()
{
	return entity++;
}