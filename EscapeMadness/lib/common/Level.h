/*
 * Level.h
 *
 *  Created on: Sep 16, 2012
 *      Author: ndy
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <Box2D/Box2D.h>
#include "../character/Player.h"
#include "../character/Enemy.h"
#include "../platform/Platform.h"

class Level {
private:
	b2World* world;
	Player * player;
	Enemy ** enemy;
	SDL_Surface* Background;
	Platform** platform;
	float camera;

public:

	Level() {
		this->enemy = new Enemy*[5];
	}

	bool Init() {
		Background = Surface::Load("./res/Fondos/Fondo1.png");

		if (Background == NULL) {
			return false;
		}

		this->camera = 0;

		world = new b2World(b2Vec2(0, -9.8));

		player = new Player(200, 205, world);

		enemy[0] = new Enemy(900, 205, world, 2);
		enemy[1] = new Enemy(1500, 205, world, 4);
		enemy[2] = new Enemy(2500, 205, world, 3);
		enemy[3] = new Enemy(4500, 205, world, 1);
		enemy[4] = new Enemy(8000, 205, world, 2);

		platform = new Platform*[50];

		for (int i = 0; i < 50; i++) {
			platform[i] = new Platform(150 + 300 * i, 100, world);
		}

		player->Init();

		enemy[0]->Init();
		enemy[1]->Init();
		enemy[2]->Init();
		enemy[3]->Init();
		enemy[4]->Init();

		for (int i = 0; i < 50; i++) {
			platform[i]->Init();
		}

		return true;
	}

	void Loop() {

		for (int i = 0; i < 50; i++) {
			platform[i]->Loop();
		}

		player->Loop();

		for (int i = 0; i < 5; i++) {
			if (enemy[i] != NULL)
				this->enemy[i]->Loop();
		}
		world->Step(1.0f / 60.0f, 24, 8);

		if (camera + 1024 - player->getBody()->GetTransform().p.x < 800)
			camera = player->getBody()->GetTransform().p.x - 1024 + 800;

	}

	void Render(SDL_Surface *Display) {

		Surface::Draw(Display, Background, -camera - Background->w, 0);
		Surface::Draw(Display, Background, -camera, 0);
		Surface::Draw(Display, Background, Background->w - camera, 0);

		player->Render(Display, camera);

		for (int i = 0; i < 5; i++) {
			if (enemy[i] != NULL)
				enemy[i]->Render(Display, camera);
		}

		for (int i = 0; i < 50; i++) {
			platform[i]->Render(Display, camera);
		}

	}

	Player * getPlayer() {
		return this->player;
	}

	void Cleanup() {
		SDL_FreeSurface(Background);

		for (int i = 0; i < 50; i++) {
			this->platform[i]->Cleanup(this->world);
		}

		this->player->Cleanup();
		for (int i = 0; i < 5; i++) {
			if (enemy[i] != NULL)
				this->enemy[i]->Cleanup();
		}
	}

	bool finished() {
		if (player->getBody()->GetTransform().p.x >= 10000)
			return true;
		return false;
	}

};

#endif /* LEVEL_H_ */
