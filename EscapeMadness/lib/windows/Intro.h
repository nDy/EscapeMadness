#ifndef INTRO_H_
#define INTRO_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"
#include "../common/Button.h"
#include <SDL/SDL_mixer.h>

class Intro: public Event {

private:

	SDL_Surface* Background;
	SDL_Surface* logoBox2d;
	SDL_Surface* logoSDL;
	int Current;
	int time;

public:

	Intro(int id) {
		Current = id;
		time = 0;
	}

	bool Init() {

		Background = Surface::Load("./res/Fondos/white.jpg");
		logoBox2d = Surface::Load("./res/Logos/box2d.png");
		logoSDL = Surface::Load("./res/Logos/sdl.png");


		if (Background == NULL) {
			return false;
		}

		return true;
	}

	int Loop() {

		if (Current != Structure::INTRO) {
			this->Cleanup();
		}

		if (time > 10){
			Current = Structure::MENU;
		}

		return Current;
	}



	void Render(SDL_Surface* Display,float camera=0) {

		Surface::Draw(Display, Background, camera, 0);

		if (time < 5)
		Surface::Draw(Display, logoSDL, 300, 250);

		if (time > 5)
		Surface::Draw(Display, logoBox2d, 370, 300);

		SDL_Delay(1000);

		time++;

	}

	void Cleanup() {
		SDL_FreeSurface(Background);
		SDL_FreeSurface(logoBox2d);
		SDL_FreeSurface(logoSDL);
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

#endif /* INTRO_H_ */
