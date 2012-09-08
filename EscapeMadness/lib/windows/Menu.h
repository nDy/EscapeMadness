#ifndef MENU_H_
#define MENU_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"

class Menu {
private:

public:
	Menu() {

	}

	bool Init() {

		//Inicializacion de SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			return false;
		}

		return true;
	}

	void Event(SDL_Event* Event) {

	}

	int Loop(int Current) {
		return Current;
	}

	void Render() const {

	}

	void Cleanup() const {

	}

};

#endif /* MENU_H_ */
