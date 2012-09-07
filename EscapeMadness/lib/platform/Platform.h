/*
 * Platform.h
 *
 *  Created on: Sep 6, 2012
 *      Author: root
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include "../common/Structure.h"
#include "../common/Surface.h"

enum {
	STATIC, VERTICAL, HORIZONTAL, MIXED, LENGTH = 300
};

class Platform: public Structure {

private:
	b2Body* body;
	SDL_Surface* img;
	short type;
	float movementlength;

public:
	Platform(int x, int y, b2World world) {
		b2BodyDef* def;
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = STATIC;
		this->movementlength = 2 * LENGTH;
	}

	Platform(int x, int y, float movementlength, short orientation,
			b2World world) {
		b2BodyDef* def;
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = orientation;
		this->movementlength = movementlength;
	}

	Platform(int x, int y, float angle, b2World world) {
		b2BodyDef* def;
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = STATIC;
		this->movementlength = 2 * LENGTH;
	}

	Platform(int x, int y, float angle, float movementlength, b2World world) {
		b2BodyDef* def;
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = MIXED;
		this->movementlength = movementlength;
	}

	Platform(int x, int y, float angle, float movementlength, short orientation,
			b2World world) {
		b2BodyDef* def;
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = orientation;
		this->movementlength = movementlength;
	}

	void Render(SDL_Surface* Display) {
		Surface::Draw(Display, this->img, this->body->GetTransform().p.x,
				Display->h - this->body->GetTransform().p.y);
	}
};

#endif /* PLATFORM_H_ */
