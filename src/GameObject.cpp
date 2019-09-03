#include "GameObject.h"

GameObject::GameObject(uint32_t id) : entity{ new Entity { } }, components{ }
{
	entity->id = id;
}

GameObject::~GameObject()
{
	// Delete all components created
	while (!components.empty())
	{
		std::type_index systemType = components.begin()->first;
		Component* comp = components.find(systemType)->second;

		components.erase(systemType);

		delete comp;
	}

	delete entity;
}