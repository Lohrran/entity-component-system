#ifndef SYSTEM_H
#define SYSTEM_H

#include "Scene.h"
#include "GameObject.h"
#include "EventChannel.h"

#include <vector>
#include <typeindex>

class System
{
	public:
		System(std::vector<std::type_index> req);

		virtual void init(GameObject* obj) = 0;
		virtual void update(GameObject* obj) = 0;
		virtual void free(GameObject* obj) = 0;

		std::vector<std::type_index> getRequeriments();
		void configure(EventChannel* evt, Scene* scn);

	protected:
		std::vector<std::type_index> requeriments;
		EventChannel* eventChannel;
		Scene* scene;
};
#endif