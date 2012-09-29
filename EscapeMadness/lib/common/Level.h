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
#include <cmath>

class Level {

	enum {
		PLATFORMS = 21, ENEMIES = 8
	};

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
		this->enemy = new Enemy*[ENEMIES];
	}

	bool Init() {
		shoot = 0;

		Background = Surface::Load("./res/Fondos/Fondo1.png");

		if (Background == NULL) {
			return false;
		}

		this->camera = 0;

		world = new b2World(b2Vec2(0, -70));

		player = new Player(200, 405, world);

		enemy[0] = new Enemy(1330, 305, world, 2);
		enemy[1] = new Enemy(2250, 505, world, 4);
		enemy[2] = new Enemy(2550, 605, world, 3);
		enemy[3] = new Enemy(4050, 605, world, 1);
		enemy[4] = new Enemy(5250, 705, world, 2);
		enemy[5] = new Enemy(5550, 705, world, 2);
		enemy[6] = new Enemy(7650, 605, world, 4);
		enemy[7] = new Enemy(7950, 605, world, 1);

		platform = new Platform*[PLATFORMS];

		platform[0] = new Platform(150, 200, world);
		platform[1] = new Platform(450, 200, world);
		platform[2] = new Platform(750, 200, world);
		platform[3] = new Platform(1050, 200, world);
		platform[4] = new Platform(1350, 200, world);
		platform[5] = new Platform(1950, 200, world);
		platform[6] = new Platform(2250, 350, world);
		platform[7] = new Platform(2550, 500, world);
		platform[8] = new Platform(2850, 500, world, 2);
		platform[9] = new Platform(3450, 500, world, 2);
		platform[10] = new Platform(4050, 500, world);
		platform[11] = new Platform(4350, 350, world);
		platform[12] = new Platform(4650, 550, world);
		platform[13] = new Platform(5250, 550, world);
		platform[14] = new Platform(5550, 550, world, 2);
		platform[15] = new Platform(6150, 350, world);
		platform[16] = new Platform(6450, 200, world);
		platform[17] = new Platform(6750, 200, world, 2);
		platform[18] = new Platform(7350, 350, world);
		platform[19] = new Platform(7650, 500, world);
		platform[20] = new Platform(7950, 500, world);
		platform[21] = new Platform(8250, 500, world);
		player->Init();

		for (int i = 0; i < ENEMIES; i++) {
			enemy[i]->Init();
		}

		for (int i = 0; i < PLATFORMS; i++) {
			platform[i]->Init();
		}

		return true;
	}

	void Loop() {

		for (int i = 0; i < PLATFORMS; i++) {
			platform[i]->Loop();
		}

		player->Loop();

		for (int i = 0; i < ENEMIES; i++) {

			if (this->enemy[i] != NULL) {
				this->enemy[i]->Loop();
			}
		}

		player->bulletLoop();

		for (int i = 0; i < ENEMIES; i++) {
			if (this->enemy[i] != NULL)
				enemy[i]->bulletLoop();
		}

		for (int i = 0; i < ENEMIES; i++) {
			if (this->enemy[i] != NULL) {
				if (this->enemy[i]->getLifes() == 0) {
					enemy[i]->Cleanup();
					enemy[i] = NULL;
				}
			}
		}

		if (player->lifes() > 0) {
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

		for (int i = 1; i <= 37; i++) {
			Surface::Draw(Display, Background, i * Background->w - camera, 0);
		}

		player->Render(Display, camera);

		for (int i = 0; i < ENEMIES; i++) {
			if (enemy[i] != NULL)
				enemy[i]->Render(Display, camera);
		}

		for (int i = 0; i < PLATFORMS; i++) {
			platform[i]->Render(Display, camera);
		}

	}

	Player * getPlayer() {
		return this->player;
	}

	float getCamera() {
		return this->camera;
	}

	void Cleanup() {
		SDL_FreeSurface(Background);

		for (int i = 0; i < PLATFORMS; i++) {
			this->platform[i]->Cleanup(this->world);
		}

		this->player->Cleanup();
		for (int i = 0; i < ENEMIES; i++) {
			if (enemy[i] != NULL)
				this->enemy[i]->Cleanup();
		}
	}
/*
	~Level() {
		delete[] platform;
		delete[] enemy;
		delete player;
		delete world;
	}
*/
	bool finished() {
		if (player->getBody()->GetTransform().p.x >= 8250)
			return true;
		return false;
	}
};

#endif /* LEVEL_H_ */
