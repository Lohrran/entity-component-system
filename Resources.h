#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <memory>
#include <typeindex>

#include "Scene.h"
#include "System.h"

class Resources
{
	public:
		Resources(Scene* scene);
		~Resources();

		template<typename SYSTEM>
		void add();

		template<typename SYSTEM>
		void init();

		template<typename SYSTEM>
		void update();

		template<typename SYSTEM>
		void free();

	private:
		void assign(std::type_index systemType); //Assign System to Get Subscribes GameObjects
		void subscribe(std::type_index systemType, GameObject* obj); //Subscribe GameObject to System
		bool componentEnabled(std::type_index systemType, GameObject* obj); //Verify if Component is Enabled

	protected:
		Scene* scene;
		std::map <std::type_index, std::shared_ptr<System>> systems;
		std::map<std::type_index, std::vector<GameObject*>> registered;
};

//Implementation
template<typename SYSTEM>
inline void Resources::add()
{
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] == nullptr)
	{
		systems[systemType] = std::make_shared<SYSTEM>();
		assign(systemType);
	}
}

template<typename SYSTEM>
inline void Resources::init()
{
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] != nullptr)
	{
		for (auto obj : registered[systemType])
		{
			if (componentEnabled(systemType, obj))
			{
				systems[systemType]->init(obj);//pass later deltatime
			}
		}
	}
}

template<typename SYSTEM>
inline void Resources::update()
{
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] != nullptr)
	{
		for (auto obj : registered[systemType])
		{
			if (componentEnabled(systemType, obj))
			{
				systems[systemType]->update(obj);//pass later deltatime
			}
		}
	}
}

template<typename SYSTEM>
inline void Resources::free()
{
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] != nullptr)
	{
		for (auto obj : registered[systemType])
		{
			if (componentEnabled(systemType, obj))
			{
				systems[systemType]->free(obj);
			}
		}
	}
}
#endif