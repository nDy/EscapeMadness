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
#include <iostream>

enum {
	STATIC, VERTICAL, HORIZONTAL, MIXED, LENGTH = 300
};

class Platform {

private:
	b2Body* body;
	SDL_Surface* img;
	short type;
	float movementlength;
	int x, y;

public:
	Platform(int x, int y, b2World*& world) {
		b2BodyDef* bodyDef;
		bodyDef = new b2BodyDef();
		bodyDef->type = b2_kinematicBody;
		bodyDef->position.Set(x, y);

		this->body = world->CreateBody(bodyDef);

		type = STATIC;
		this->movementlength = 2 * LENGTH;
		this->x = x;
		this->y = y;
	}

	Platform(int x, int y, b2World*& world, int orientation) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		type = orientation;
		this->movementlength = 2 * LENGTH;
		this->x = x;
		this->y = y;
	}

	Platform(int x, int y, float angle, b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		def->angle = angle;
		body = world->CreateBody(def);
		type = STATIC;
		this->movementlength = 2 * LENGTH;
		this->x = x;
		this->y = y;
	}

	Platform(int x, int y, float movementlength, short orientation,
			b2World world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
		type = orientation;
		this->movementlength = movementlength;
	}

	Platform(int x, int y, float angle, float movementlength, b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		type = MIXED;
		this->movementlength = movementlength;
	}

	Platform(int x, int y, float angle, float movementlength, short orientation,
			b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_kinematicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		type = orientation;
		this->movementlength = movementlength;
	}

	bool Init() {
		this->img = Surface::Load((char*) "./res/platform.png");
		b2FixtureDef* def;
		def = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(LENGTH / 2, 12.0f);
		def->shape = &dynamicBox;
		def->filter.groupIndex = 1;
		this->body->CreateFixture(def);

		return true;
	}

	void Loop() {
		bool up;
		switch (type) {

		case STATIC:
			break;

		case VERTICAL:
			if (body->GetTransform().p.y >= this->y + movementlength)
				up = false;

			else if (body->GetTransform().p.y <= this->y)
				up = true;

			if (up)
				body->SetLinearVelocity(b2Vec2(0, -4));
			else
				body->SetLinearVelocity(b2Vec2(0, 8));

			break;

		case HORIZONTAL:
			/*	if (body.getPosition().x
			 >= initPos.x + this.length
			 - Width * Math.cos(angle * Math.PI / 180))
			 up = false;

			 else if (body.getPosition().x <= initPos.x)
			 up = true;

			 if (up)
			 body.m_linearVelocity.x = 8;

			 if (!up)
			 body.m_linearVelocity.x = -8;

			 body.m_linearVelocity.y = 0;
			 */
			break;

		default:
			break;
		}

	}

	void Render(SDL_Surface* Display, float PlayerPos) {
		Surface::Draw(Display, this->img,
				this->body->GetTransform().p.x - PlayerPos - 150,
				Display->h - this->body->GetTransform().p.y - 12);
	}

	void Cleanup(b2World* world) {
		world->DestroyBody(this->body);
		SDL_FreeSurface(this->img);
	}

};

#endif /* PLATFORM_H_ */
