#ifndef _BASICCHARACTER_H_
#define _BASICCHARACTER_H_

#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include "../common/Structure.h"
#include "../common/Surface.h"

class BasicCharacter: public Structure {
	b2Body* body;
	SDL_Surface* img;
public:
	BasicCharacter(float x, float y, b2World& world) {
		b2BodyDef* def;
		def->type = b2_dynamicBody;
		def->position.Set(x, y);
		body = world.CreateBody(def);
	}

	bool Init() {
		this->img = Surface::Load((char*) "../res.bmp");
		if (this->img == NULL)
			return false;
		return true;
		b2FixtureDef* def;
		this->body->CreateFixture(def);
	}

	void Render(SDL_Surface* Display) {
		Surface::Draw(Display, this->img, this->body->GetTransform().p.x,
				Display->h - this->body->GetTransform().p.y);
	}

	void Cleanup(b2World* world) {
		world->DestroyBody(this->body);
		SDL_FreeSurface(this->img);
	}

	SDL_Surface* getImg() {
		return this->img;
	}

	b2Body* getBody() {
		return this->body;
	}

	void jump() {
		// if (jumping <= 2) {
		body->ApplyLinearImpulse(b2Vec2(0, 50), b2Vec2(0, 0));
		// jumping++;
	}

	// }

	void moveRight() {
		body->ApplyForce(b2Vec2(5, 0), b2Vec2(0, 0));
	}

	void moveLeft() {
		body->ApplyForce(b2Vec2(-5, 0), b2Vec2(0, 0));
	}

	float getMass() {
		return body->GetMass();
	}

	void resetJump() {
		//jumping = 0;
	}
};

#endif
