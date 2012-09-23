/*
 * Level.h
 *
 *  Created on: Sep 16, 2012
 *      Author: ndy
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <Box2D/Box2D.h>
#include "../character/BasicCharacter.h"
#include "../platform/Platform.h"

class Level {
private:
	b2World* world;
	BasicCharacter * player;
	SDL_Surface* Background;
	Platform** platform;

public:

	Level() {
	}

	bool init() {
		Background = Surface::Load("./res/bg.bmp");

		if (Background == NULL) {
			return false;
		}

		world = new b2World(b2Vec2(0, -9.8));

		player = new BasicCharacter(50, 200, world);

		platform = new Platform*[10];

		for (int i = 0; i < 10; i++){
			platform[i] = new Platform(300 * i, 100, world);
		}

		player->Init();

		for (int i = 0; i < 10; i++){
			platform[0]->Init();
		}

		return true;
	}

	int wasHit() {
		//return player contacts
		return 0;
	}

	void loop() {

		for (int i = 0; i < 10; i++) {
			platform[i]->Loop();
		}

		world->Step(1.0f / 60.0f, 6, 2);

	}
//04247114492
	void render(SDL_Surface *Display) {
		Surface::Draw(Display, Background, -player->getBody()->getTransform().x, 0);

		player->Render(Display);

		for (int i = 0; i < 10; i++) {
			platform[i]->Render(Display);
		}

	}

	BasicCharacter * getPlayer() {
		return this->player;
	}

};

#endif /* LEVEL_H_ */
