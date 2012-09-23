#ifndef MENU_H_
#define MENU_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"
#include "../common/Button.h"

class Menu: public Event, public Structure {
private:
	SDL_Surface* Background;
	Button* game;
	Button* help;
	int Current;
public:
	Menu(int id) {
		Current = id;
	}

	bool Init() {

		Background = Surface::Load("./res/bg.bmp");

		if (Background == NULL) {
			return false;
		}

		if (TTF_Init() == -1) {
			return false;
		}

		this->game = new Button((char*) "Jugar", 20, 20, Background);
		this->help = new Button((char*) "Ayuda", 20, 120, Background);

		return true;
	}

	int Loop() {
		if (Current != Structure::MENU) {
			this->Cleanup();
		}
		return Current;
	}

	void Render(SDL_Surface* Display,float camera=0) {

		Surface::Draw(Display, Background, camera, 0);

		this->game->render();

		this->help->render();

	}

	void Cleanup() const {
		SDL_FreeSurface(Background);
	}

	//Events

	void OnInputFocus() {
	}

	void OnInputBlur() {
	}

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	}

	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	}

	void OnMouseFocus() {
	}

	void OnMouseBlur() {
	}

	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right,
			bool Middle) {
	}

	void OnMouseWheel(bool Up, bool Down) {
	} //Not implemented

	void OnLButtonDown(int mX, int mY) {
		if (help->isClicked(mX, mY)) {
			Current = Structure::HELP;
		}
		if (game->isClicked(mX, mY)) {
			Current = Structure::INGAME;
		}
	}

	void OnLButtonUp(int mX, int mY) {
	}

	void OnRButtonDown(int mX, int mY) {

	}

	void OnRButtonUp(int mX, int mY) {
	}

	void OnMButtonDown(int mX, int mY) {
	}

	void OnMButtonUp(int mX, int mY) {
	}

	void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
	}

	void OnJoyButtonDown(Uint8 which, Uint8 button) {
	}

	void OnJoyButtonUp(Uint8 which, Uint8 button) {
	}

	void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
	}

	void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
	}

	void OnMinimize() {
	}

	void OnRestore() {
	}

	void OnResize(int w, int h) {
	}

	void OnExpose() {
	}

	void OnExit() {
	}

	void OnUser(Uint8 type, int code, void* data1, void* data2) {
	}
};

#endif /* MENU_H_ */
