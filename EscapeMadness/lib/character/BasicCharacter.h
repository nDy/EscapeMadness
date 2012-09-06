#ifndef _BASICCHARACTER_H_
#define _BASICCHARACTER_H_

#include <SDL/SDL.h>

class BasicCharacter {
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

	void drawAt(SDL_Surface& g) {
		//g.drawAnimation(animation, body.getPosition().x - initialImage.getWidth() / 2,body.getPosition().y - initialImage.getHeight() / 2);
	}



	void resetJump() {
		//jumping = 0;
	}
};

#endif
