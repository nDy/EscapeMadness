#ifndef MENU_H_
#define MENU_H_

#include "Event.h"
#include "../common/Structure.h"

class Menu {
private:

public:
	Menu() {

	}

	bool Init() {
		Current = MENU;

		//Inicializacion de SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			return false;
		}
		//Inicializacion de ventana
		if ((Display = SDL_SetVideoMode(640, 480, 32,
				SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
			return false;
		}

		if( TTF_Init() == -1 ){
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
