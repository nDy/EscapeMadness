/*
 * Enemy.h
 *
 *  Created on: Sep 23, 2012
 *      Author: ndy
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include "../common/Structure.h"
#include "../common/Surface.h"
#include <iostream>

class Enemy {
private:
	b2Body* body;
	b2Body** bullets;
	SDL_Surface* img;
	SDL_Surface* bullet;
	b2Body* hittingBullet;
	b2World* world;
	int life;

public:
	Enemy(float x, float y, b2World*& world, int lifes) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		bullets = new b2Body*[50];
		this->world = world;
		this->life = lifes;
	}

	bool wasHit() {



		if (life < 1)
			return false;

		for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next)

		{

			b2Contact* c = ce->contact;

			if (c->GetFixtureB()->GetBody()->IsBullet()) {
				c->GetFixtureB()->GetBody()->SetActive(false);
					world->DestroyBody(c->GetFixtureB()->GetBody());
				return true;
			}
		}
		return false;
	}

	bool Init() {
		this->img = Surface::Load((char*) "./res/Player/Standing/Stand1.png");
		this->bullet = Surface::Load((char*) "./res/bullet.png");
		b2FixtureDef* def;
		def = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(50.0f, 100.0f);
		def->shape = &dynamicBox;
		def->filter.groupIndex = 3;
		this->body->CreateFixture(def);

		return true;
	}

	void Render(SDL_Surface* Display, float camera) {
		if (this->life == 0)
			return;
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

	void Cleanup() {
		SDL_FreeSurface(this->img);
		world->DestroyBody(body);
		body = NULL;
		delete this;
	}

	int Loop() {

		if (this->wasHit()) {
			life--;
		}



		if (this->life <= 0)
			body->ApplyLinearImpulse(b2Vec2(0, 65000 * 10), b2Vec2_zero);

		if (body->GetLinearVelocity().x < 40)
			body->ApplyLinearImpulse(b2Vec2(0, 0), b2Vec2_zero);

		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL)
				this->bullets[i]->ApplyLinearImpulse(b2Vec2(-65000, 0),
						b2Vec2_zero);
		}

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
		body->ApplyLinearImpulse(b2Vec2(0, 70), b2Vec2(0, 0));
		// jumping++;
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

	void Shoot() {
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
		def->position.Set(this->body->GetTransform().p.x - 55,
				this->body->GetTransform().p.y);
		b2CircleShape bulletShape;
		bulletShape.m_radius = 1;
		this->bullets[i] = world->CreateBody(def);
		b2FixtureDef * fixture;
		fixture = new b2FixtureDef();
		fixture->shape = &bulletShape;
		fixture->filter.groupIndex =2;
		fixture->filter.categoryBits = 1;
		fixture->userData = this->bullet;
		this->bullets[i]->CreateFixture(fixture);
		this->bullets[i]->SetLinearVelocity(
				b2Vec2(99 * this->body->GetLinearVelocity().x, 0));
	}

	float getMass() {
		return body->GetMass();
	}

	void resetJump() {

	}

	virtual ~Enemy() {
	}
};

#endif /* ENEMY_H_ */
