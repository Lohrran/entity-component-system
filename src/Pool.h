#ifndef POOL_H
#define POOL_H

#include <vector>
#include <memory>
#include <algorithm>

#include "GameObject.h"

class Pool
{
	public:
		Pool() = default;

		Pool(const Pool&) = default;
		Pool& operator = (const Pool&) = default;
		Pool& operator = (Pool&&) = default;

		~Pool();
		
		void add(GameObject* obj);
		void remove(GameObject* obj);

		std::vector<GameObject*> getItems();

	private:
		std::vector<GameObject*> items;
};
#endif