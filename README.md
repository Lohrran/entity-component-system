# Entity-Component-System
> A tiny ECS C++ framework


## Why?
After I read the book **[Game Programming Patterns by Robert Nystrom](https://gameprogrammingpatterns.com)**, I could not stop think in ways to apply the different designs on the book, however of all them ECS call more my atention. So here is my attempt of implement it and learn more C++

## Introduction
The framework was based on different articles (references below) from cross internet and the book Game Programming Patterns, it's simple to understand and easy to use.
For the communication between the *systems* was implement **[Publisher / Subscribe Pattern](https://en.wikipedia.org/wiki/Publish–subscribe_pattern)**.

So the framework have some issues handling memory allocation, and on my concept I thought that having an Object Pooling for create and delete Game Object should be a *system* instead, although implement a Object Pooling in the current framework should be easy.

## What it Looks Like?
The below implementation was made using the SDL2 library:

```c++

#define FRAMES_PER_SECOND 60
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

//Standard Library
#include <iostream>

//SDL2 Library
#include <SDL.h>

//ECS
#include "Scene.h"
#include "Resources.h"

//Components
#include "ScreenComponent.h"
#include "SpriteComponent.h"
#include "PositionComponent.h"
#include "TagComponent.h"

//Systems
#include "ScreenSystem.h"
#include "SpriteSystem.h"
#include "MovementSystem.h"

int main(int argc, char *argv[])
{
	//Temporary helper to Loop the Game
	bool quit = false;
	SDL_Event event;

	/* --- SCENE ---*/
	
	Scene* scene = new Scene{ };
	Resources* resources = new Resources{ scene };

	//Game Screen
	GameObject* screen = scene->createGameObject();
	screen->addComponent<ScreenComponent>("Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	/* --- GAMEOBJECTS ---*/
	
	GameObject* player = scene->createGameObject();
	player->addComponent<SpriteComponent>("C:\\Users\\claud\\Desktop\\player_34x34.bmp", 34, 34);
	player->addComponent<PositionComponent>(50, 50);
	player->addComponent<TagComponent>("Player");

	GameObject* enemy = scene->createGameObject();
	enemy->addComponent<SpriteComponent>("C:\\Users\\claud\\Desktop\\enemy_34x34.bmp", 34, 34);
	enemy->addComponent<PositionComponent>(300, 100);
	enemy->addComponent<TagComponent>("Enemy");


	/* --- SYSTEMS --- */

	resources->add<ScreenSystem>();
	resources->add<SpriteSystem>();
	resources->add<MovementSystem>();


	/* --- INITIALIZING THE GAME --- */

	//Start
	resources->init<ScreenSystem>();
	resources->init<SpriteSystem>();
	resources->init<MovementSystem>();

	//Update
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			//User requests quit
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		resources->update<SpriteSystem>();
		resources->update<MovementSystem>();
		resources->update<ScreenSystem>();

		SDL_Delay(1000 / FRAMES_PER_SECOND);
	}

	//Clean
	resources->free<SpriteSystem>();
	resources->free<MovementSystem>();
	resources->free<ScreenSystem>();

	std::cout << "\n\n\n";
	system("pause");
	return 0;
}

```


## How to

Import the files for your project.


###### Create Scene and Resource

```c++

int main(int argc, char *argv[])
{
	Scene* scene = new Scene{ };
	Resources* resources = new Resources{ scene };
}
```

###### Create Scene and Resource

```c++

int main(int argc, char *argv[])
{
	GameObject* player = scene->createGameObject();
}
```


###### Create Component

```c++
#include "Component.h"

struct PositionComponent : public Component
{
	PositionComponent(int x = 0, int y = 0) : x{ x }, y{ y } { }

	int x, y;
};
```


###### Create Event

```c++
//Entity Component System
#include "Event.h"
#include "GameObject.h"

struct StateEvent : public Event
{
	StateEvent(GameObject* obj, std::string state) : obj{ obj }, state{ state } { }

	GameObject* obj;
	std::string state;
};
```

###### Create System

.h File:

```c++
//Entity Component System
#include "Requeriment.h"

//Components
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DirectionComponent.h"

//Event
#include "StateEvent.h"

class MovementSystem : public Requeriment <PositionComponent, VelocityComponent, DirectionComponent>
{
	public:
		MovementSystem();

		void init(GameObject* obj) override;
		void update(GameObject* obj)override;
		void free(GameObject* obj) override;
};
```

.cpp File:
```C++
#include "MovementSystem.h"

MovementSystem::MovementSystem() { }

void MovementSystem::init(GameObject* obj)
{
	obj->getComponent<PositionComponent>()->x = obj->getComponent<PositionComponent>()->x;
	obj->getComponent<PositionComponent>()->y = obj->getComponent<PositionComponent>()->y;
}

void MovementSystem::update(GameObject* obj)
{
	switch (obj->getComponent<DirectionComponent>()->direction)
	{
		case Direction::UP:
			obj->getComponent<PositionComponent>()->y -= obj->getComponent<VelocityComponent>()->y;
			eventChannel->publish(new StateEvent(obj, "WALK UP"));
			break;
		
		case Direction::DOWN:
			obj->getComponent<PositionComponent>()->y += obj->getComponent<VelocityComponent>()->y;
			eventChannel->publish(new StateEvent(obj, "WALK DOWN"));
			break;

		case Direction::RIGHT:
			obj->getComponent<PositionComponent>()->x += obj->getComponent<VelocityComponent>()->x;
			eventChannel->publish(new StateEvent(obj, "WALK RIGHT"));
			break;
		
		case Direction::LEFT:
			obj->getComponent<PositionComponent>()->x -= obj->getComponent<VelocityComponent>()->x;
			eventChannel->publish(new StateEvent(obj, "WALK LEFT"));
			break;

		default:
			obj->getComponent<PositionComponent>()->x = obj->getComponent<PositionComponent>()->x;
			obj->getComponent<PositionComponent>()->y = obj->getComponent<PositionComponent>()->y;
			break;
	}
}
 
void MovementSystem::free(GameObject* obj) { }
```

## Observation

The Component class by default have an boolean variable (enabled), the Resource class will just update or initialize an object if all the component are
enabled:

```c++
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
```
For disabled or enabled a GameObject it's simple:

```c++

	player->getComponent<PositionComponent>()->enabled = false;

```
## References:
Some references used while developing the framework

- [Game Programming Patterns by Robert Nystrom] (https://gameprogrammingpatterns.com)
- [Aframe Entity-Component-System] (https://aframe.io/docs/0.9.0/introduction/entity-component-system.html)
- [Ts Projects Entity-Component-System] (https://tsprojectsblog.wordpress.com/portfolio/entity-component-system/)
- [Understanding Component-Entity-Systems] (https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/)
