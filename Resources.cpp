#include "Resources.h"

Resources::Resources(Scene* scene) : scene{ scene } { }
Resources::~Resources() { }

void Resources::assign(std::type_index systemType, std::vector<GameObject*> pool)
{
	for (auto &obj : pool)
	{
		subscribe(systemType, obj);
	}
}

void Resources::subscribe(std::type_index systemType, GameObject* obj)
{
	bool exist = true;

	// Check if all the Components Required to make the System Work exist
	for (auto componentType : systems[systemType]->getRequeriments())
	{
		if (obj->components.find(componentType) == obj->components.end())
		{
			exist = false;
			break;
		}
	}

	// Register Game Object that fit System Requerimetns
	if (exist)
	{
		registered[systemType].push_back(obj);
	}
}

bool Resources::componentEnabled(std::type_index systemType, GameObject* obj)
{
	bool enabled = true;

	for (auto componentType : systems[systemType]->getRequeriments())
	{
		if (obj->components[componentType]->enabled == false)
		{
			enabled = false;
		}
	}
	return enabled;
}

void Resources::configure()
{
	// Pass an reference to all the systems of Resource Event Channel and Scene
	for (auto system : systems)
	{
		system.second->configure(eventChannel, scene);
	}

	//Copy all Game Objects already created
	copies.clear();
	copies = scene->getPool()->getItems();
}


void Resources::registering()
{
	if (copies.size() < scene->getPool()->getItems().size()) // Verify for new Game Objects added
	{
		std::vector<GameObject*> newObjs = difference(scene->getPool()->getItems(), copies);

		for (auto system : systems)
		{
			assign(system.first, newObjs);

			for (auto obj : newObjs)
			{
				if (std::find(registered[system.first].begin(), registered[system.first].end(), obj) != registered[system.first].end())
				{
					if (componentEnabled(system.first, obj))
					{
						systems[system.first]->init(obj);
					}
				}
			}
		}

		// Copy the currents Game Objects in the Pool to the
		copies.clear();
		copies = scene->getPool()->getItems();
	}
}

std::vector<GameObject*> Resources::difference(const std::vector<GameObject*>& primary, const std::vector<GameObject*>& secondary)
{
	std::set<GameObject*> p(primary.begin(), primary.end());
	std::set<GameObject*> s(secondary.begin(), secondary.end());
	std::vector<GameObject*> result;

	std::set_difference( p.begin(), p.end(), s.begin(), s.end(), std::back_inserter(result) );

	return result;
}