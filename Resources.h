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
		~Resources();

		template<typename SYSTEM>
		void add(); // Add Systems to the Resource Pool

		template<typename SYSTEM>
		void init();// Initialize all Game Objects of all the Systems in the Resource Pool

		template<typename SYSTEM>
		void update();// Update all Game Objects of all the Systems in the Resource Pool

		template<typename SYSTEM>
		void free();// Free all Game Objects of all the Systems in the Resource Pool

		void configure();// Configure Event Scene to the all System in the Resource Pool 

		void registering(); // Verify for new Game Objects to Assign Systems to them 

	private:
		void assign(std::type_index systemType, std::vector<GameObject*> pool); // Assign System to Subscribes GameObjects
		void subscribe(std::type_index systemType, GameObject* obj); // Subscribe GameObject to System
		bool componentEnabled(std::type_index systemType, GameObject* obj); // Verify if Component is Enabled

		std::vector<GameObject*> difference(const std::vector<GameObject*>& primary, const std::vector<GameObject*>& secondary);
	
	protected:
		Scene* scene;
		EventChannel* eventChannel = new EventChannel{ };
		std::map<std::type_index, std::shared_ptr<System>> systems;
		std::map<std::type_index, std::vector<GameObject*>> registered;

	private:
		std::vector<GameObject*> copies; //Game Object Copies from Scene
};

//Implementation
template<typename SYSTEM>
inline void Resources::add()
{
	std::type_index systemType = std::type_index(typeid(SYSTEM));
	if (systems[systemType] == nullptr)
	{
		systems[systemType] = std::make_shared<SYSTEM>();
		assign(systemType, scene->getPool()->getItems());//Assign System to get subscribes
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
			if (componentEnabled(systemType, obj))// Check if all component are enabled to current System be able to work
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