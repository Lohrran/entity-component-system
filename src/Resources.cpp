#include "Resources.h"

Resources::Resources(Scene* scene) : scene{ scene } 
{ 
	eventChannel = new EventChannel{ }; 
}

Resources::~Resources()
{
	// Delete all systems created
	while (!systems.empty())
	{
		std::type_index systemType = systems.begin()->first;
		System* sys = systems.find(systemType)->second;

		systems.erase(systemType);

		delete sys;
	}

	delete eventChannel;
}

bool Resources::isComponentsEnabled(std::type_index systemType, GameObject* obj)
{
	// Check if components require are enabled
	for (auto componentType : systems[systemType]->getRequeriments())
	{
		if (obj->components[componentType]->enabled == false)
		{
			return false;
		}
	}
	return true;
}

bool Resources::requeriments(std::type_index systemType, GameObject* obj)
{
	// Count each component that match with the requeriments impose by the system
	int count = std::count_if(systems[systemType]->getRequeriments().cbegin(), systems[systemType]->getRequeriments().cend(), 
	[&](std::type_index component)
	{
		return obj->components.find(component) != std::end(obj->components);
	});

	return count < systems[systemType]->getRequeriments().size() ? false : true;
}

void Resources::configure()
{
	// Pass a reference to all the systems of Resource Event Channel and Scene
	for (auto system : systems)
	{
		system.second->configure(eventChannel, scene);
	}
}