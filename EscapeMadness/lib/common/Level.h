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
	int shoot;

public:

	Level() {
		this->enemy = new Enemy*[15];
	}

	bool Init() {
		shoot = 0;

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
		enemy[4] = new Enemy(9500, 205, world, 2);
		enemy[5] = new Enemy(12000, 205, world, 2);
		enemy[6] = new Enemy(13000, 205, world, 4);
		enemy[7] = new Enemy(14500, 205, world, 1);
		enemy[8] = new Enemy(16000, 205, world, 4);
		enemy[9] = new Enemy(17000, 205, world, 2);
		enemy[10] = new Enemy(19000, 205, world, 2);
		enemy[11] = new Enemy(20500, 205, world, 2);
		enemy[12] = new Enemy(22000, 205, world, 3);
		enemy[13] = new Enemy(23500, 205, world, 1);
		enemy[14] = new Enemy(24000, 205, world, 1);

		platform = new Platform*[50];

		for (int i = 0; i < 50; i++) {
			platform[i] = new Platform(150 + 300 * i, 100, world);
		}

		player->Init();

		for (int i = 0; i < 15; i++) {
			enemy[i]->Init();
		}

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

		for (int i = 0; i < 15; i++) {

			if (this->enemy[i] != NULL) {
				this->enemy[i]->Loop();
			}
		}

		player->bulletLoop();

		for(int i = 0; i < 15; i++){
			if (this->enemy[i] != NULL)
			enemy[i]->bulletLoop();
		}

		for(int i = 0; i < 15; i++){
			if (this->enemy[i] != NULL){
				if (this->enemy[i]->getLifes() == 0){
					enemy[i]->Cleanup();
					enemy[i] = NULL;
				}
			}
		}

		if (player->lifes() > 0){
			world->Step(1.0f / 60.0f, 24, 8);
		}

		if (camera + 1024 - player->getBody()->GetTransform().p.x < 400)
			camera = player->getBody()->GetTransform().p.x - 1024 + 400;

		if (player->getBody()->GetTransform().p.x - camera < 400)
			camera = player->getBody()->GetTransform().p.x - 400;

		shoot++;

	}

	void Render(SDL_Surface *Display) {

		Surface::Draw(Display, Background, -camera - Background->w, 0);
		Surface::Draw(Display, Background, -camera, 0);
		Surface::Draw(Display, Background, Background->w - camera, 0);
		Surface::Draw(Display, Background, 2 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 3 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 4 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 5 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 6 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 7 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 8 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 9 * Background->w - camera, 0);
		Surface::Draw(Display, Background, 10 * Background->w - camera, 0);

		player->Render(Display, camera);

		for (int i = 0; i < 15; i++) {
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
		for (int i = 0; i < 15; i++) {
			if (enemy[i] != NULL)
				this->enemy[i]->Cleanup();
		}
	}

	/*	bool finished() {
	 if (player->getBody()->GetTransform().p.x >= 10000)
	 return true;
	 return false;
	 }
	 */
};

#endif /* LEVEL_H_ */
