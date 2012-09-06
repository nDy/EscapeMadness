//============================================================================
// Name        : EscapeMadness.cpp
// Author      : nDy
// Version     : 1.0
// Description : Escape Madness: The Game
//============================================================================

#include "SDL/SDL.h"

#include "../lib/windows/Help.h"
#include "../lib/windows/Menu.h"
#include "../lib/windows/InGame.h"
#include "../lib/common/Structure.h"
enum {
	MENU, INGAME, HELP
};



class EscapeMadness: public Structure{

private:

	bool Running;
	int Current;
	SDL_Surface* Display;


public:

	EscapeMadness() {
		Display = NULL;
		Running = true;
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

		return true;
	}

	void Event(SDL_Event* Event) {
		if (Event->type == SDL_QUIT) {
			Running = false;
		}
		switch (Current) {
		case MENU:

			break;

		case INGAME:

			break;

		case HELP:

			break;
		}
	}

	void Loop() const {
		switch (Current) {
		case MENU:

			break;

		case INGAME:

			break;

		case HELP:

			break;
		}
	}

	void Render(SDL_Surface* display) {
		switch (Current) {
		case MENU:

			break;

		case INGAME:

			break;

		case HELP:

			break;
		}
	}

	void Cleanup() const {
		SDL_Quit();
	}

	int Execute() {
		if (Init() == false) {
			return -1;
		}

		SDL_Event event;

		while (Running) {
			while (SDL_PollEvent(&event)) {
				Event(&event);
			}

			Loop();
			Render(this->Display);
		}

		Cleanup();

		return 0;
	}

};

int main(int argc, char* argv[]) {
	EscapeMadness* EscapeMadnessTheGame;

	EscapeMadnessTheGame = new EscapeMadness();

	return EscapeMadnessTheGame->Execute();
}
