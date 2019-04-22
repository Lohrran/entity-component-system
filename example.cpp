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