#include "Resources.h"

Resources::Resources(Scene* scene) : scene{ scene } { }
Resources::~Resources() { }

void Resources::assign(std::type_index systemType)
{
	for (auto &obj : scene->getPool()->getItems())
	{
		subscribe(systemType, obj);
	}
}

void Resources::subscribe(std::type_index systemType, GameObject* obj)
{
	bool exist = true;

	for (auto componentType : systems[systemType]->requeriments)
	{
		if (obj->components.find(componentType) == obj->components.end())
		{
			exist = false;
			break;
		}
	}

	if (exist)
	{
		registered[systemType].push_back(obj);
	}
}

bool Resources::componentEnabled(std::type_index systemType, GameObject* obj)
{
	bool enabled = true;

	for (auto componentType : systems[systemType]->requeriments)
	{
		if (obj->components[componentType]->enabled == false)
		{
			enabled = false;
		}
	}
	return enabled;
}
