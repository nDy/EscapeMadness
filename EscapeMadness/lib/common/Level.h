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

class Level {
private:
	b2World* world;
	BasicCharacter * player;
	SDL_Surface* Background;

public:

	Level(){

	}

	bool init() {
		Background = Surface::Load("./res/bg.bmp");

		if (Background == NULL) {
			return false;
		}

		world = new b2World(b2Vec2(0, -9.8));

		player = new BasicCharacter(0, 200, world);

		player->Init();

		return true;
	}

	int wasHit() {
		//return player contacts
		return 0;
	}

	void loop() {
		world->Step(1/60, 6, 2);
	}

	void render(SDL_Surface *Display) {
		Surface::Draw(Display, Background, 0, 0);

		player->Render(Display);
	}

	BasicCharacter * getPlayer(){
		return this->player;
	}

};

#endif /* LEVEL_H_ */
