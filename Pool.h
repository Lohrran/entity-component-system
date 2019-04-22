#ifndef POOL_H
#define POOL_H

#include <vector>
#include <algorithm>

#include "GameObject.h"

class Pool
{
	public:
		void add(GameObject* obj);
		void remove(GameObject* obj);
		void clear();

		std::vector<GameObject*> getItems();
	protected:
		std::vector<GameObject*> items;
};
#endif