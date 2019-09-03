#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <memory>
#include <typeindex>

#include "Entity.h"
#include "Component.h"

class GameObject
{
	public:
		Entity* entity;
		std::map <std::type_index, Component*> components;


		GameObject(uint32_t id);

		GameObject& operator = (const GameObject& clone) = default;
		GameObject& operator = (GameObject&&) = default;

		virtual ~GameObject();

		template<typename COMPONENT, typename... Args>
		void addComponent(Args&&... args);

		template<typename COMPONENT>
		COMPONENT* getComponent();	
};

//+++ Implementation +++//

template<typename COMPONENT, typename... Args>
inline void GameObject::addComponent(Args&&... args)
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));
	if (components[componentType] == nullptr)
	{
		components[componentType] = new COMPONENT{ args... };
	}
}

template<typename COMPONENT>
inline COMPONENT* GameObject::getComponent()
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));

	if (components.find(componentType) == components.cend())
	{
		return nullptr;
	}
	return dynamic_cast<COMPONENT*>(components[componentType]);
}
#endif