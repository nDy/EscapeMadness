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
	SDL_Surface* bgImg;
	short type;
	float movementlength;
	int x, y;
	bool up;

public:
	Platform(int x, int y, b2World*& world) {
		b2BodyDef* bodyDef;
		bodyDef = new b2BodyDef();
		bodyDef->type = b2_kinematicBody;
		bodyDef->position.Set(x, y / 2);

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
		//up true inicia el movimiento de la plataforma hacia arriba
		//o hacia la derecha dependiendo de la orientacion asignada
		this->up = true;
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
		this->img = Surface::Load((char*) "./res/Platform/TopPlatform.png");
		this->bgImg = Surface::Load((char*) "./res/Platform/BgPlatform.png");
		b2FixtureDef* def;
		def = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		if (this->type == STATIC){
			dynamicBox.SetAsBox(LENGTH / 2, this->body->GetTransform().p.y);
		} else {
			dynamicBox.SetAsBox(LENGTH / 2, 12.0f);
		}
		def->shape = &dynamicBox;
		def->filter.groupIndex = 1;
		this->body->CreateFixture(def);

		return true;
	}

	void Loop() {
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
			if (body->GetTransform().p.x >= x + LENGTH)
				up = false;

			else if (body->GetTransform().p.x <= x)
				up = true;

			if (up)
				body->SetLinearVelocity(b2Vec2(8, 0));

			if (!up)
				body->SetLinearVelocity(b2Vec2(-8, 0));

			break;

		default:
			break;
		}

	}

	void Render(SDL_Surface* Display, float PlayerPos) {
		int i = this->body->GetTransform().p.y;\

		if (this->type == STATIC)
			i*=2;

		Surface::Draw(Display, this->img,
				this->body->GetTransform().p.x - PlayerPos - this->img->w / 2,
				Display->h - i - this->img->h / 2);

		if (this->type == STATIC) {

			//reemplazar this img con la imagen del relleno

			do {
				i -= this->bgImg->h;
				Surface::Draw(Display, this->bgImg,
						this->body->GetTransform().p.x - PlayerPos
								- this->bgImg->w / 2,
						Display->h - i - this->bgImg->h / 2);
			} while (i > 0);
		}
	}

	void Cleanup(b2World* world) {
		world->DestroyBody(this->body);
		SDL_FreeSurface(this->img);
	}

};

#endif /* PLATFORM_H_ */
