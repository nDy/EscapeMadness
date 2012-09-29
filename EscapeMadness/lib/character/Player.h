/*
 * Player.h
 *
 *  Created on: Sep 23, 2012
 *      Author: ndy
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include "../common/Structure.h"
#include "../common/Surface.h"

class Player {

private:

	b2Body* body;
	b2Body** bullets;
	SDL_Surface* img;
	SDL_Surface* bullet;
	b2World* world;
	int life;
	int jumping;
	bool moving;

public:

	Player(float x, float y, b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		bullets = new b2Body*[50];
		this->world = world;
	}

	int lifes() {
		return this->life;
	}

	int wasHit() {

		for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next) {

			b2Contact* c = ce->contact;

			if (c->GetFixtureB()->GetBody()->IsBullet()
					&& c->GetFixtureB()->GetFilterData().groupIndex != 2) {
				return 1;
			} else if (c->GetFixtureB()->GetFilterData().groupIndex == 3
					&& c->GetFixtureB()->GetFilterData().categoryBits != 1) {
				return 2;
			} else if (c->GetFixtureB()->GetFilterData().groupIndex == 1) {
				return 0;
			}
		}

		return -1;
	}

	void bulletLoop() {

		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL) {
				this->bullets[i]->ApplyForceToCenter(b2Vec2(0, 70));
				for (b2ContactEdge* ce = this->bullets[i]->GetContactList(); ce;
						ce = ce->next) {
					{
						this->bullets[i]->SetActive(false);
						this->world->DestroyBody(this->bullets[i]);
						this->bullets[i] = NULL;
					}

				}

			}
		}

	}

	bool Init() {
		this->img = Surface::Load((char*) "./res/Player/Standing/Stand1.png");
		this->bullet = Surface::Load((char*) "./res/Fireball.png");
		b2FixtureDef* def;
		def = new b2FixtureDef();
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(50.0f, 100.0f);
		def->shape = &dynamicBox;
		def->filter.groupIndex = 2;
		def->filter.categoryBits = 0x0002;
		this->body->CreateFixture(def);
		life = 20;
		this->jumping = 0;
		return true;
	}

	void Render(SDL_Surface* Display, float camera) {
		Surface::Draw(Display, this->img,
				this->body->GetTransform().p.x - camera - this->img->w / 2,
				Display->h - this->body->GetTransform().p.y - this->img->h / 2);

		for (int i = 0; i < 50; i++) {
			if (this->bullets[i] != NULL)
				Surface::Draw(Display, this->bullet,
						this->bullets[i]->GetTransform().p.x - camera
								- this->bullet->w / 2,
						Display->h - this->bullets[i]->GetTransform().p.y
								- this->bullet->h / 2);
		}
	}

	void Cleanup() {
		SDL_FreeSurface(this->img);
		this->body->SetActive(false);
		this->world->DestroyBody(this->body);
		this->body = NULL;
		delete this;
	}

	void Loop() {

		switch (wasHit()) {

		case 0:
			this->resetJump();
			break;

		case 1:
			life--;
			break;

		case 2:
			life -= 4;
			break;

		}

	}

	SDL_Surface * getImg() {
		return this->img;
	}

	b2Body * getBody() {
		return this->body;
	}

	void jump() {
		if (jumping < 1) {

			body->ApplyLinearImpulse(b2Vec2(0, 1200), b2Vec2(0, 0));

			jumping++;
		}
	}

	void moveRight() {
		body->ApplyLinearImpulse(b2Vec2(300, body->GetLinearVelocity().y), b2Vec2(0, 0));
		moving = true;
	}

	void moveLeft() {
		//body->ApplyLinearImpulse(b2Vec2(-5, 0), b2Vec2(0, 0));

		body->ApplyLinearImpulse(b2Vec2(-300, body->GetLinearVelocity().y), b2Vec2(0, 0));
		moving = true;
	}

	void StopX() {
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		moving = false;
	}
	void Shoot(int x, int y) {
		int i = 0;
		while (!(this->bullets[i] == NULL)) {
			if (i < 50)
				i++;
			else
				i = 0;
		}

		float X =
				(x - this->body->GetTransform().p.x)
						/ sqrt(
								pow(x - this->body->GetTransform().p.x, 2)
										+ pow(
												(768 - y)
														- this->body->GetTransform().p.y,
												2));

		float Y =
				((768 - y) - this->body->GetTransform().p.y)
						/ sqrt(
								pow(x - this->body->GetTransform().p.x, 2)
										+ pow(
												(768 - y)
														- this->body->GetTransform().p.y,
												2));

		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->bullet = true;
		def->position.Set(150 * X + this->body->GetTransform().p.x,
				150 * Y + this->body->GetTransform().p.y);
		b2CircleShape bulletShape;
		bulletShape.m_radius = 1;
		this->bullets[i] = world->CreateBody(def);
		b2FixtureDef * fixture;
		fixture = new b2FixtureDef();
		fixture->shape = &bulletShape;
		fixture->filter.groupIndex = 2;
		fixture->filter.categoryBits = 0x0002;
		fixture->filter.maskBits = 0x0004;
		fixture->userData = this->bullet;
		this->bullets[i]->CreateFixture(fixture);
		this->bullets[i]->SetLinearVelocity(b2Vec2(600 * X, 600 * Y));
	}

	float getMass() {
		return body->GetMass();
	}

	void resetJump() {
		jumping = 0;
	}

}
;

#endif /* PLAYER_H_ */
