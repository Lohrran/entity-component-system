#include "Pool.h"

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
	}
}

void Pool::clear()
{
	items.clear();
}

std::vector<GameObject*> Pool::getItems()
{
	return items;
}