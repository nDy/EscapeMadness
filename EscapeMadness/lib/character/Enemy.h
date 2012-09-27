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
#include <cmath>

class Enemy {
private:
	b2Body* body;
	b2Body** bullets;
	SDL_Surface* img;
	SDL_Surface* bullet;
	b2Body* hittingBullet;
	b2World* world;
	int life;
	int shoot;

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
		this->shoot = 0;
	}

	void bulletLoop() {
		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL) {

				for (b2ContactEdge* ce = this->bullets[i]->GetContactList(); ce;
						ce = ce->next)

						{

					b2Contact* c = ce->contact;

					if (c->GetFixtureA()->GetFilterData().groupIndex == 2
							|| c->GetFixtureA()->GetFilterData().groupIndex
									== 1) {
						this->bullets[i]->SetActive(false);
						this->world->DestroyBody(this->bullets[i]);
						this->bullets[i] = NULL;
					}
				}
				if (this->bullets[i] != NULL)
					this->bullets[i]->ApplyForceToCenter(b2Vec2(0, 9.8));
			}
		}
	}

	int wasHit() {

		shoot++;

		for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next)

		{
			b2Contact* c = ce->contact;
			b2Fixture* fixa = NULL;
			b2Fixture* fixb = NULL;
			if (c->GetFixtureA()->GetFilterData().groupIndex == 2) {
				fixa = c->GetFixtureA();
				fixb = c->GetFixtureB();
			} else if (c->GetFixtureB()->GetFilterData().groupIndex == 2) {
				fixa = c->GetFixtureB();
				fixb = c->GetFixtureA();
			}

			if (fixa != NULL && fixb != NULL) {

				if (fixb->IsSensor()) {

					if (!fixa->GetBody()->IsBullet()) {
						if (shoot % 60 == 0)
							this->Shoot(fixa->GetBody()->GetTransform().p.x,
									fixa->GetBody()->GetTransform().p.y);
					}
					//else
					//dodge the bullet
				} else {
					if (fixa->GetBody()->IsBullet()) {
						return 1;
					} else if (fixa->GetFilterData().groupIndex == 1) {
						return 0;
					} else if (fixa->GetFilterData().groupIndex == 2) {
						return 2;
					}
				}
			}
		}

		return -1;
	}

	bool Init() {
		this->img = Surface::Load((char*) "./res/Player/Standing/Stand1.png");
		this->bullet = Surface::Load((char*) "./res/bullet.png");
		b2FixtureDef* def;
		b2FixtureDef* sensor;
		def = new b2FixtureDef();
		sensor = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		b2CircleShape sensorShape;
		dynamicBox.SetAsBox(50.0f, 100.0f);
		sensorShape.m_radius = 200;
		sensor->shape = &sensorShape;
		sensor->isSensor = true;
		def->shape = &dynamicBox;
		def->filter.categoryBits = 0x0004;
		this->body->CreateFixture(def);
		this->body->CreateFixture(sensor);

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
		SDL_FreeSurface(this->bullet);
		this->body->SetActive(false);
		this->world->DestroyBody(this->body);
		this->body = NULL;

		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL) {
				this->bullets[i]->SetActive(false);
				this->world->DestroyBody(this->bullets[i]);
				this->bullets[i] = NULL;
			}
		}

		delete this;
	}

	void Loop() {

		switch (wasHit()){
			case 0:
				break;

			case 1:
				life--;
				break;

			case 2:
				life = 0;
				break;
		}

		if (shoot == 60)
			shoot = 0;

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

	void Shoot(int x, int y) {
		int i = 0;
		while (!(this->bullets[i] == NULL)) {
			if (i < 50)
				i++;
			else
				i = 0;
		}

		float X = (x - this->body->GetTransform().p.x)
				/ sqrt(
						pow(x - this->body->GetTransform().p.x, 2)
								+ pow(y - this->body->GetTransform().p.y, 2));

		float Y = (y - this->body->GetTransform().p.y)
				/ sqrt(
						pow(x - this->body->GetTransform().p.x, 2)
								+ pow(y - this->body->GetTransform().p.y, 2));

		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->bullet = true;
		def->position.Set(50 * X + this->body->GetTransform().p.x,
				50 * Y + this->body->GetTransform().p.y);
		b2CircleShape bulletShape;
		bulletShape.m_radius = 1;
		this->bullets[i] = world->CreateBody(def);
		b2FixtureDef * fixture;
		fixture = new b2FixtureDef();
		fixture->shape = &bulletShape;
		fixture->filter.maskBits = 0x0002;
		fixture->userData = this->bullet;
		this->bullets[i]->CreateFixture(fixture);
		this->bullets[i]->SetLinearVelocity(b2Vec2(60 * X, 60 * Y));
	}

	float getMass() {
		return body->GetMass();
	}

	int getLifes(){
		return this->life;
	}

	void resetJump() {

	}

	virtual ~Enemy() {
	}
};

#endif /* ENEMY_H_ */
