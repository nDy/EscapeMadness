#ifndef INGAME_H_
#define INGAME_H_

#include "Event.h"
#include "../common/Level.h"
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>

#include "../common/Structure.h"
#include "../character/BasicCharacter.h"
#include "../platform/Platform.h"

class InGame: public Event, public Structure {
private:
	Level *lvl;

	int Current;
	int Lifes;
	float Life;

public:
	InGame(int id) {
		Current = id;

	}

	bool Init() {

		lvl = new Level();
		lvl->init();

		return true;
	}

	int Loop() {
		if (Current != Structure::INGAME) {
			this->Cleanup();
		}

		lvl->loop();

		return Current;

	}

	void Render(SDL_Surface* Display) {

		lvl->render(Display);

		//Draw HUD

	}

	void Cleanup() const {

	}

	//Events

	void OnInputFocus() {
	}

	void OnInputBlur() {
	}

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
		if (sym == SDLK_RIGHT)
			this->lvl->getPlayer()->moveRight();
		if (sym == SDLK_LEFT)
			this->lvl->getPlayer()->moveLeft();
		if (sym == SDLK_SPACE) {
			this->lvl->getPlayer()->jump();
			std::cout << "salta hdp" << std::endl;
		}

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

#endif /* INGAME_H_ */
