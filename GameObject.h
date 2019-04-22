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
		GameObject() : entity{}, components{} {}
		~GameObject() {}

		template<typename COMPONENT, typename... Args>
		void addComponent(Args&&... args);

		template<typename COMPONENT>
		std::shared_ptr<COMPONENT> getComponent();

		template<typename COMPONENT>
		void setEnabled(bool enabled);

		template <typename COMPONENT>
		bool getEnabled();

	public:
		Entity* entity;
		std::map <std::type_index, std::shared_ptr<Component>> components;
};

//Implementation
template<typename COMPONENT, typename... Args>
inline void GameObject::addComponent(Args&&... args)
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));
	if (components[componentType] == nullptr)
	{
		components[componentType] = std::make_shared<COMPONENT>(args...);
	}
}

template<typename COMPONENT>
inline std::shared_ptr<COMPONENT> GameObject::getComponent()
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));

	if (components.find(componentType) != components.cend())
	{
		return std::dynamic_pointer_cast<COMPONENT>(components[componentType]);
	}
	else
	{
		std::shared_ptr<COMPONENT> nullSmartPtr(new COMPONENT);//Null ptr to help return NULL
		return nullSmartPtr;
	}
}

template<typename COMPONENT>
inline void GameObject::setEnabled(bool enabled)
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));

	if (components.find(componentType) != components.cend())
	{
		components[componentType]->enabled = enabled;
	}
}

template <typename COMPONENT>
inline bool GameObject::getEnabled()
{
	std::type_index componentType = std::type_index(typeid(COMPONENT));

	if (components.find(componentType) != components.cend())
	{
		return components[componentType]->enabled;
	}
	else
	{
		return false;
	}
}
#endif