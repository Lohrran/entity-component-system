#include "Pool.h"

Pool::~Pool()
{
	while (!items.empty())
	{
		GameObject* obj = items.back();
		items.erase(std::remove(items.begin(), items.end(), obj), items.end());
		delete obj;
	}
}

void Pool::add(GameObject* obj)
{
	if (std::find(items.begin(), items.end(), obj) == items.end())
	{
		items.push_back(obj);
	}
}

void Pool::remove(GameObject* obj)
{
	if (std::find(items.begin(), items.end(), obj) != items.end())
	{
		items.erase(std::remove(items.begin(), items.end(), obj), items.end());
		delete obj;
	}
}

std::vector<GameObject*> Pool::getItems()
{
	return items;
}