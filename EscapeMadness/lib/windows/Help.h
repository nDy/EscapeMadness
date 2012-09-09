#ifndef HELP_H_
#define HELP_H_

#include "Event.h"
#include "../common/Surface.h"
#include <SDL/SDL.h>
#include <iostream>

class Help: public Event {
private:
	SDL_Surface* Background;
public:
	Help() {

	}

	bool Init() {

		Background = Surface::Load("../res/bg.bmp");

		if (Background==NULL){
			return false;
		}
		if( TTF_Init() == -1 ){
			return false;
		}

		return true;
	}

	int Loop(int Current) {
		return Current;
	}

	void Render(SDL_Surface* Display) {

		Surface::Draw(Display, Background,0, 0);

		Surface::DrawText("Volver al menu", Display, 20, 20, 255, 255, 255, 200);

	}

	void Cleanup() const {
		SDL_FreeSurface(Background);
		TTF_Quit();
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
	}//Not implemented

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

#endif /* HELP_H_ */
