/*
 * Level.h
 *
 *  Created on: Sep 16, 2012
 *      Author: ndy
 */

#ifndef BOSSLEVEL_H_
#define BOSSLEVEL_H_

#include <Box2D/Box2D.h>
#include "../character/BasicCharacter.h"
#include "../platform/Platform.h"

class BossLevel {
private:
	b2World* world;
	BasicCharacter * player;
	SDL_Surface* Background;
	Platform** platform;
	float camera;

public:

	BossLevel() {

	}

	bool Init() {
		Background = Surface::Load("./res/Fondos/Fondo1.png");

		if (Background == NULL) {
			return false;
		}

		this->camera = 0;

		world = new b2World(b2Vec2(0, -9.8));

		player = new BasicCharacter(250, 300, world);

		platform = new Platform*[10];

		for (int i = 0; i < 10; i++) {
			platform[i] = new Platform(150 + 300 * i, 100, world);
		}

		player->Init();

		for (int i = 0; i < 10; i++) {
			platform[i]->Init();
		}

		return true;
	}

	int wasHit() {
		//return player contacts
		return 0;
	}

	void Loop() {

		for (int i = 0; i < 10; i++) {
			platform[i]->Loop();
		}

		world->Step(1.0f / 60.0f, 6, 2);

		//fix camera

		if (player->getBody()->GetTransform().p.x - camera < 200)
			camera = player->getBody()->GetTransform().p.x - 200;
		if (camera + 768 - player->getBody()->GetTransform().p.x < 200)
			camera = player->getBody()->GetTransform().p.x - 768 + 200;

	}

	void Render(SDL_Surface *Display) {

		Surface::Draw(Display, Background, -camera, 0);
		Surface::Draw(Display, Background, Background->w - camera, 0);

		player->Render(Display, camera);

		for (int i = 0; i < 10; i++) {
			platform[i]->Render(Display, camera);
		}

	}

	BasicCharacter * getPlayer() {
		return this->player;
	}

	void Cleanup() {
		SDL_FreeSurface(Background);

		for (int i = 0; i < 10; i++) {
			this->platform[i]->Cleanup(this->world);
		}

		this->player->Cleanup();

	}

	bool finished() {
		if (player->getBody()->GetTransform().p.x >= 3000)
			return true;
		return false;
	}

};

#endif /* BOSSLEVEL_H_ */
