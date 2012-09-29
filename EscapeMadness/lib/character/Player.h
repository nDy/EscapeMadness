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
#include <iostream>

class Player {

private:

	b2Body* body;
	b2Body** bullets;
	SDL_Surface** img;
	SDL_Surface** imgLeft;
	SDL_Surface** walkImg;
	SDL_Surface** walkImgLeft;
	SDL_Surface* bullet;
	b2World* world;
	int life;
	int jumping;
	int standingFrame;
	int walkingFrame;
	int sec;
	bool moving;
	int movementOrientation;

public:

	Player(float x, float y, b2World*& world) {
		b2BodyDef* def;
		def = new b2BodyDef();
		def->type = b2_dynamicBody;
		def->position.Set(x, y);
		body = world->CreateBody(def);
		bullets = new b2Body*[50];

		this->world = world;
		this->img = new SDL_Surface*[4];
		this->imgLeft = new SDL_Surface*[4];
		this->walkImg = new SDL_Surface*[8];
		this->walkImgLeft = new SDL_Surface*[8];
		this->standingFrame = 0;
		this->walkingFrame = 0;
		this->sec = 1;
		this->movementOrientation = 0;
		this->moving = false;

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

		this->img[0] = Surface::Load((char*) "./res/Player/Standing/Stand1.png");
		this->img[1] = Surface::Load((char*) "./res/Player/Standing/Stand2.png");
		this->img[2] = Surface::Load((char*) "./res/Player/Standing/Stand3.png");
		this->img[3] = Surface::Load((char*) "./res/Player/Standing/Stand4.png");

		this->imgLeft[0] = Surface::Load((char*) "./res/Player/Standing/StandLeft1.png");
		this->imgLeft[1] = Surface::Load((char*) "./res/Player/Standing/StandLeft2.png");
		this->imgLeft[2] = Surface::Load((char*) "./res/Player/Standing/StandLeft3.png");
		this->imgLeft[3] = Surface::Load((char*) "./res/Player/Standing/StandLeft4.png");

		this->walkImg[0] = Surface::Load((char*) "./res/Player/Walking/Walk1.png");
		this->walkImg[1] = Surface::Load((char*) "./res/Player/Walking/Walk2.png");
		this->walkImg[2] = Surface::Load((char*) "./res/Player/Walking/Walk3.png");
		this->walkImg[3] = Surface::Load((char*) "./res/Player/Walking/Walk4.png");
		this->walkImg[4] = Surface::Load((char*) "./res/Player/Walking/Walk5.png");
		this->walkImg[5] = Surface::Load((char*) "./res/Player/Walking/Walk6.png");
		this->walkImg[6] = Surface::Load((char*) "./res/Player/Walking/Walk7.png");
		this->walkImg[7] = Surface::Load((char*) "./res/Player/Walking/Walk8.png");

		this->walkImgLeft[0] = Surface::Load((char*) "./res/Player/Walking/WalkLeft1.png");
		this->walkImgLeft[1] = Surface::Load((char*) "./res/Player/Walking/WalkLeft2.png");
		this->walkImgLeft[2] = Surface::Load((char*) "./res/Player/Walking/WalkLeft3.png");
		this->walkImgLeft[3] = Surface::Load((char*) "./res/Player/Walking/WalkLeft4.png");
		this->walkImgLeft[4] = Surface::Load((char*) "./res/Player/Walking/WalkLeft5.png");
		this->walkImgLeft[5] = Surface::Load((char*) "./res/Player/Walking/WalkLeft6.png");
		this->walkImgLeft[6] = Surface::Load((char*) "./res/Player/Walking/WalkLeft7.png");
		this->walkImgLeft[7] = Surface::Load((char*) "./res/Player/Walking/WalkLeft8.png");


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

		if (moving){

			if (movementOrientation == 0){

				Surface::Draw(Display, this->walkImg[walkingFrame],
							this->body->GetTransform().p.x - camera - this->walkImg[walkingFrame]->w/2,
							Display->h - this->body->GetTransform().p.y - this->walkImg[walkingFrame]->h/2);
			}

			if (movementOrientation == 1){

				Surface::Draw(Display, this->walkImgLeft[walkingFrame],
							this->body->GetTransform().p.x - camera - this->walkImgLeft[walkingFrame]->w/2,
							Display->h - this->body->GetTransform().p.y - this->walkImgLeft[walkingFrame]->h/2);
			}

		} else {

			if (movementOrientation == 0){

				Surface::Draw(Display, this->img[standingFrame],
						this->body->GetTransform().p.x - camera - this->img[standingFrame]->w/2,
						Display->h - this->body->GetTransform().p.y - this->img[standingFrame]->h/2);

			}

			if (movementOrientation == 1){

				Surface::Draw(Display, this->imgLeft[standingFrame],
						this->body->GetTransform().p.x - camera - this->imgLeft[standingFrame]->w/2,
						Display->h - this->body->GetTransform().p.y - this->imgLeft[standingFrame]->h/2);

			}
		}

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
		for (int i = 0; i < 8; i++)
			SDL_FreeSurface(this->walkImg[i]);

		for (int i = 0; i < 8; i++)
			SDL_FreeSurface(this->walkImgLeft[i]);

		for (int i = 0; i < 4; i++)
			SDL_FreeSurface(this->img[i]);

		for (int i = 0; i < 4; i++)
			SDL_FreeSurface(this->imgLeft[i]);

		this->body->SetActive(false);
		this->world->DestroyBody(this->body);
		this->body = NULL;
		delete this;
	}

	void Loop() {


		if (sec % 10 == 0){
			standingFrame++;
			if (standingFrame > 3){
				standingFrame = 0;
			}
		}

		if (sec % 10 == 0){
			walkingFrame++;
			if (walkingFrame > 7){
				walkingFrame = 0;
			}
		}

		sec++;

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
		return this->img[standingFrame];
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
		movementOrientation = 0;
		body->ApplyLinearImpulse(b2Vec2(300, body->GetLinearVelocity().y), b2Vec2(0, 0));
		moving = true;

	}

	void moveLeft() {
		//body->ApplyLinearImpulse(b2Vec2(-5, 0), b2Vec2(0, 0));
		movementOrientation = 1;
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
