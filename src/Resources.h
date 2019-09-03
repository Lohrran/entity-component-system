#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <memory>
#include <typeindex>
#include <set>

#include "Scene.h"
#include "System.h"

class Resources
{
	public:
		Resources(Scene* scene);

		Resources& operator = (const Resources&) = delete;
		Resources& operator = (Resources&&) = delete;

		virtual ~Resources();


		template<typename SYSTEM>
		void add();

		template<typename SYSTEM>
		void init();

		template<typename SYSTEM>
		void update();

		template<typename SYSTEM>
		void free();

		void configure();

	protected:
		Scene* scene;
		EventChannel* eventChannel;

		std::map<std::type_index, System*> systems;
	private:
		bool isComponentsEnabled(std::type_index systemType, GameObject* obj);
		bool requeriments(std::type_index systemType, GameObject* obj);
};


//+++ Implementation +++//

template<typename SYSTEM>
inline void Resources::add()
{
	// Add new Systems to the Resource pool
	std::type_index systemType = std::type_index(typeid(SYSTEM));

	if (systems[systemType] == nullptr)
	{
		systems[systemType] = new SYSTEM { };
	}
}

template<typename SYSTEM>
inline void Resources::init()
{
	// Initialize all obj that fit the requeriments of the system
	std::type_index systemType = std::type_index(typeid(SYSTEM));

	if (systems[systemType] != nullptr)
	{
		for (auto obj : scene->gameObjects())
		{
			if (requeriments(systemType, obj))
			{
				systems[systemType]->init(obj);
			}
		}
	}
}

template<typename SYSTEM>
inline void Resources::update()
{
	// Update all obj that fit the requeriments of the system
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	
	if (systems[systemType] != nullptr)
	{
		for (auto obj : scene->gameObjects())
		{
			if (requeriments(systemType, obj) && isComponentsEnabled(systemType, obj))
			{
				systems[systemType]->update(obj);
			}
		}
	}
}

template<typename SYSTEM>
inline void Resources::free()
{
	// Free all obj that fit the requeriments of the system
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] != nullptr)
	{
		for (auto obj : scene->gameObjects())
		{
			if (requeriments(systemType, obj))
			{
				systems[systemType]->free(obj);
			}
		}
	}
}
#endif