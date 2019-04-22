#ifndef SYSTEM_H
#define SYSTEM_H

#include "GameObject.h"

#include <vector>
#include <typeindex>

class System
{
	public:
		System(std::vector<std::type_index> req) : requeriments{ req } { }

		virtual void init(GameObject* obj) = 0;
		virtual void update(GameObject* obj) = 0;
		virtual void free(GameObject* obj) = 0;

	public:
		std::vector<std::type_index> requeriments;
};
#endif