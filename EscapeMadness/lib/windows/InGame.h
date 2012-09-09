#ifndef INGAME_H_
#define INGAME_H_

#include "Event.h"
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>

#include "../common/Structure.h"
#include "../character/BasicCharacter.h"
#include "../platform/Platform.h"

class InGame: public Event{
private:
	b2World* world;
	Platform* plat;
public:
	InGame() {
		std::cout<<"plataforma"<<std::endl;
		plat = new Platform(1,2,this->world);
		std::cout<<"plataforma instanciada"<<std::endl;
	}

	bool Init() {
		b2Vec2 gravity(0.0f, -10.0f);
		this->world = new b2World(gravity);
		plat = new Platform(0,1,this->world);
		return true;
	}

	int Loop(int Current) {
		return Current;
	}

	void Render(SDL_Surface* Display) {

	}

	void Cleanup() {

	}

};

#endif /* INGAME_H_ */
