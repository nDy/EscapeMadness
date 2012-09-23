#ifndef _BASICCHARACTER_H_
#define _BASICCHARACTER_H_

#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include <iostream>
#include "../common/Structure.h"
#include "../common/Surface.h"
#include <cmath>

class BasicCharacter: public Structure {

	b2Body* body;
	b2Body** bullets;
	SDL_Surface* img;
	SDL_Surface* bullet;
	b2World* world;

public:

	BasicCharacter(float x, float y, b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		bullets = new b2Body*[50];
		this->world = world;
	}

	bool Init() {
		this->img = Surface::Load((char*) "./res/Player/Standing/Stand1.png");
		this->bullet = Surface::Load((char*) "./res/bullet.png");
		b2FixtureDef* def;
		def = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(50.0f, 100.0f);
		def->shape = &dynamicBox;
		//def->density = 1.0;
		this->body->CreateFixture(def);

		return true;
	}

	void Render(SDL_Surface* Display, float camera) {
		Surface::Draw(Display, this->img,
				this->body->GetTransform().p.x - camera - 50,
				Display->h - this->body->GetTransform().p.y - 89);

		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL)
				Surface::Draw(Display, this->bullet,
						this->bullets[i]->GetTransform().p.x - camera - 50,
						Display->h - this->bullets[i]->GetTransform().p.y - 89);
		}
	}
	void Cleanup() const {
		SDL_FreeSurface(this->img);
	}

	int Loop() {
		return 0;
	}

	SDL_Surface * getImg() {
		return this->img;
	}

	b2Body * getBody() {
		return this->body;
	}

	void jump() {
		// if (jumping <= 2) {
		body->ApplyLinearImpulse(b2Vec2(0, 40), b2Vec2(0, 0));
		// jumping++;
	}

	int wasHit() {
		//return player contacts
		return 0;
	}

	void moveRight() {
		//body->ApplyLinearImpulse(b2Vec2(5, 0), b2Vec2(0, 0));
		body->ApplyForceToCenter(b2Vec2(20, 0));
	}

	void moveLeft() {
		//body->ApplyLinearImpulse(b2Vec2(-5, 0), b2Vec2(0, 0));
		body->ApplyForceToCenter(b2Vec2(-20, 0));
	}

	void Stop() {
		body->SetLinearVelocity(b2Vec2_zero);
	}

	void Shoot(int x, int y) {
		int i = 0;
		while (!(this->bullets[i] == NULL)) {
			if (i < 50)
				i++;
			else
				i = 0;
		}
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->bullet = true;
		def->position.Set(this->body->GetTransform().p.x+55, this->body->GetTransform().p.y);
		b2CircleShape bulletShape;
		bulletShape.m_radius = 1;
		this->bullets[i] = world->CreateBody(def);
		b2FixtureDef * fixture;
		fixture = new b2FixtureDef();
		fixture->shape = &bulletShape;
		this->bullets[i]->CreateFixture(fixture);
		this->bullets[i]->SetLinearVelocity(b2Vec2((40*fabsf(x-this->body->GetTransform().p.x)),(40*fabsf(y-this->body->GetTransform().p.y))));
	}

	float getMass() {
		return body->GetMass();
	}

	void resetJump() {

	}
};

#endif
