#include <iostream>
#include <string>

#include "Component.h"
#include "Scene.h"
#include "Resources.h"
#include "Requeriment.h"

struct NameComponent : public Component
{
	NameComponent(std::string name = "") : name{ name } { }

	std::string name;
};

class UpdateCharacterClassSystem : public Requeriment<NameComponent>
{
	public:
		void init(GameObject* obj) override
		{
			if (obj->getComponent<NameComponent>()->name == "Player")
			{
				obj->getComponent<NameComponent>()->name = "Knight";
			}

			else
			{
				obj->getComponent<NameComponent>()->name = "Orc";
			}
		}

		void update(GameObject* obj) override { }
		void free(GameObject* obj) override { }
};


int main(int argc, char *argv[])
{
	Scene scene;
	Resources resources{ &scene };

	GameObject* player = scene.createGameObject();
	GameObject* enemy = scene.createGameObject();

	player->addComponent<NameComponent>("Player");
	enemy->addComponent<NameComponent>("Enemy");

	resources.add<UpdateCharacterClassSystem>();
	resources.configure();

	std::cout << "Name: " << player->getComponent<NameComponent>()->name << std::endl;
	std::cout << "Name: " << enemy->getComponent<NameComponent>()->name << std::endl;

	resources.init<UpdateCharacterClassSystem>();


	std::cout << "\n\n-----Updated Class-----\n\n" << std::endl;


	std::cout << "Name: " << player->getComponent<NameComponent>()->name << std::endl;
	std::cout << "Name: " << enemy->getComponent<NameComponent>()->name << std::endl;

	std::cout << "\n\n\n";
	system("pause");
	return 0;
}