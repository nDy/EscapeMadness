//============================================================================
// Name        : EscapeMadness.cpp
// Author      : nDy
// Version     : 1.0
// Description : Escape Madness: The Game
//============================================================================

#include <SDL/SDL.h>

#include "../lib/windows/Help.h"
#include "../lib/windows/Menu.h"
#include "../lib/windows/InGame.h"
#include "../lib/common/Structure.h"
#include <iostream>
enum {
	MENU, INGAME, HELP
};

class EscapeMadness{

private:

	bool Running;
	int Current;
	SDL_Surface* Display;
	InGame* ingame;
	Menu* menu;
	Help* help;

public:

	EscapeMadness() {
		Display = NULL;
		Running = true;
		//ingame = new InGame();
		menu = new Menu();
		//help = new Help();
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
		//help->Init();
		//ingame->Init();
		menu->Init();

		return true;
	}

	void Event(SDL_Event* Event) {
		if (Event->type == SDL_QUIT) {
			Running = false;
		}
		switch (Current) {
		case MENU:
			menu->Event(Event);
			break;

		case INGAME:
			ingame->Event(Event);
			break;

		case HELP:
			help->Event(Event);
			break;
		}
	}

	void Loop() {
		switch (Current) {
		case MENU:
			this->Current = menu->Loop(Current);
			break;

		case INGAME:
			this->Current = ingame->Loop(Current);
			break;

		case HELP:
			this->Current = help->Loop(Current);
			break;
		}
	}

	void Render(SDL_Surface* display) {
		switch (Current) {
		case MENU:
			menu->Render(display);
			break;

		case INGAME:
			ingame->Render(display);
			break;

		case HELP:
			help->Render(display);
			break;
		}
	}

	void Cleanup() const {
		SDL_Quit();
		menu->Cleanup();
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
