#ifndef HELP_H_
#define HELP_H_

#include "Event.h"
#include "../common/Surface.h"
#include "../common/Structure.h"
#include <SDL/SDL.h>
#include <iostream>

class Help: public Event {

private:
	SDL_Surface* Background;
	int Current;
	Button* menu;

public:
	Help(int id) {
		Current = id;
	}

	bool Init() {

		Background = Surface::Load("./res/Fondos/back.jpg");

		if (Background == NULL) {
			return false;
		}
		if (TTF_Init() == -1) {
			return false;
		}

		this->menu = new Button((char*) "VOLVER", 470, 30, Background,
						50);

		return true;
	}

	int Loop() {
		return Current;
	}

	void Render(SDL_Surface* Display,float camera=0) {

		if (Background == NULL){
			this->Init();
		}

		Surface::Draw(Display, Background, camera, 0);
		this->menu->render();
		Surface::DrawText("Mover al personaje: WASD", Display, 280, 180, 247, 49, 49, 40);
		Surface::DrawText("Disparar: click en la pantalla", Display, 230, 280, 247, 49, 49, 40);
	}

	void Cleanup() {
		SDL_FreeSurface(Background);
		Background = NULL;
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
		if (menu->isClicked(mX, mY)){
			Current = Structure::MENU;
			this->Cleanup();
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

#endif /* HELP_H_ */
