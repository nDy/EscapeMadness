#ifndef _BASICCHARACTER_H_
#define _BASICCHARACTER_H_

#include <SDL/SDL.h>
#include "../common/Structure.h"

class BasicCharacter: public Structure{
	SDL_Surface* img;
public:
	BasicCharacter() {
	}

	SDL_Surface* getImg() {
		return this->img;
	}

	void getBody() {
		//TODO: return body;
	}

	void jump() {
		// if (jumping <= 2) {
		//body.applyLinearImpulse(new Vec2(0, -50), new Vec2(0, 0));
		// jumping++;
	}

	// }

	void moveRight() {
		//body.applyForce(new Vec2(5, 0), new Vec2(0, 0));
	}

	void moveLeft() {
		//body.applyForce(new Vec2(-5, 0), new Vec2(0, 0));
	}

	float getMass() {
		//return body.m_mass;
		return 0.5; //test value
	}

	void setMass(float mass) {
		//body.m_mass = mass;
	}

	void Render(SDL_Surface* Display) {

	}

	void resetJump() {
		//jumping = 0;
	}
};

#endif
