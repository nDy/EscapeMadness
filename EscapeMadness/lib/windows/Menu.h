#ifndef MENU_H_
#define MENU_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"
#include "../common/Button.h"
#include <SDL/SDL_mixer.h>

class Menu: public Event {

private:

	SDL_Surface* Background;
	Mix_Music *music;
	Button* game;
	Button* title;
	int Current;

public:

	Menu(int id) {
		Current = id;
	}

	bool Init() {

		Background = Surface::Load("./res/Fondos/back.jpg");

	    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		    return false;
	    }

		if (Background == NULL) {
			return false;
		}

		if (TTF_Init() == -1) {
			return false;
		}

		music = Mix_LoadMUS( "./res/OST/Bonehead - Naked City.wav");

		this->title = new Button((char*) "Escape Madness", 35, 140, Background, 150);
		this->game = new Button((char*) "PRESIONA AQUI PARA COMENZAR", 300, 340, Background, 40);

		Mix_PlayMusic( music, 0 );
		return true;
	}

	int Loop() {

		if( Mix_PlayingMusic() == 0 ) {
			music = Mix_LoadMUS( "./res/OST/01 - Ocean of Molasses.wav");
			Mix_PlayMusic( music, 0);
		}

		if (Current != Structure::MENU) {
			this->Cleanup();
		}
		return Current;
	}



	void Render(SDL_Surface* Display,float camera=0) {

		Surface::Draw(Display, Background, camera, 0);

		this->game->render();

		this->title->render();

	}

	void Cleanup() {
		SDL_FreeSurface(Background);
		Mix_FreeMusic( music );
		Mix_CloseAudio();
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
		if (game->isClicked(mX, mY)) {
			Mix_HaltMusic();
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
