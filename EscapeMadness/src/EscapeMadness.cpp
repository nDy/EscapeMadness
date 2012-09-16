//============================================================================
// Name        : EscapeMadness.cpp
// Author      : nDy
// Version     : 1.0
// Description : Escape Madness: The Game
//============================================================================

#include <SDL/SDL.h>
#include <iostream>

#include "../lib/windows/Help.h"
#include "../lib/windows/Menu.h"
#include "../lib/windows/InGame.h"
#include "../lib/common/Structure.h"

class EscapeMadness: public Structure {

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
		help = new Help(Structure::HELP);
		menu = new Menu(Structure::MENU);
		ingame = new InGame(Structure::INGAME);
	}

	~EscapeMadness() {
	}

	bool Init() {

		Current = Structure::MENU;

		//Inicializacion de SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return false;

		//Inicializacion de Display
		if ((Display = SDL_SetVideoMode(640, 480, 32,
				SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
			return false;

		//Inicializacion de ventanas
		if (!menu->Init())
			return false;
		if (!help->Init())
			return false;
		if (!ingame->Init())
			return false;

		return true;
	}

	void Event(SDL_Event* Event) {
		if (Event->type == SDL_QUIT) {
			Running = false;
		}
		switch (Current) {
		case Structure::MENU:
			menu->CheckEvent(Event);
			break;

		case Structure::INGAME:
			ingame->CheckEvent(Event);
			break;

		case Structure::HELP:
			help->CheckEvent(Event);
			break;
		}
	}

	int Loop() {

		switch (Current) {
		case Structure::MENU:
			Current = menu->Loop();
			break;

		case Structure::INGAME:
			Current = ingame->Loop();
			break;

		case Structure::HELP:
			Current = help->Loop();
			break;

		}
		return Current;
	}

	void Render(SDL_Surface* display) {
		switch (Current) {
		case Structure::MENU:
			menu->Render(display);
			break;

		case Structure::INGAME:
			ingame->Render(display);
			break;

		case Structure::HELP:
			help->Render(display);
			break;
		}

		SDL_Flip(display);
	}

	void Cleanup() const {
		SDL_Quit();
		menu->Cleanup();
		help->Cleanup();
		ingame->Cleanup();
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
