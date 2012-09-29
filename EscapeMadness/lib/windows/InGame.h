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
	SDL_Surface* img;
//	Mix_Music *music;
	int Current;
	int Lifes;
	bool MoveRight;
	bool MoveLeft;
	bool finished;
//	bool playFirst;

public:
	InGame(int id) {
		Current = id;

		MoveRight = false;
		MoveLeft = false;
		//playFirst = false;

	}

	bool Init() {

		lvl = new Level();
		lvl->Init();
		/*
		 if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		 return false;
		 }

		 music = Mix_LoadMUS("./res/OST/chimaira.wav");
		 */
		this->img = Surface::Load((char*) "./res/heart.png");
		return true;
	}

	int Loop() {
		if (Current != Structure::INGAME) {
			this->Cleanup();
		}
		/*
		 if (playFirst == false) {
		 Mix_PlayMusic(music, -1);
		 playFirst = true;
		 }
		 */
		if (MoveRight)
			movePlayer(0);

		if (MoveLeft)
			movePlayer(1);

		if (!MoveLeft && !MoveRight)
			movePlayer(2);

		lvl->Loop();

		return Current;

	}

	void movePlayer(int LR) {
		switch (LR) {
		case 0:
			this->lvl->getPlayer()->moveRight();
			break;
		case 1:
			this->lvl->getPlayer()->moveLeft();
			break;
		case 2:
			this->lvl->getPlayer()->StopX();
		}
	}

	void Render(SDL_Surface* Display, float camera = 0) {

		lvl->Render(Display);

		if (lvl->finished()) {
			Surface::DrawText("Nivel terminado", Display, 20, 20, 255, 255, 255,
					20);
			Surface::DrawText("Presiona Escape para continuar", Display, 20, 50,
					255, 255, 255, 20);
		}
		//Draw HUD

		for (int i = 0; i < this->lvl->getPlayer()->lifes(); i++) {
			Surface::Draw(Display, this->img, (i + 1) * 25, 25);
		}

		if (lvl->getPlayer()->lifes() <= 0) {
			Surface::DrawText("Game Over", Display, 350, 350, 255, 255, 255,
					75);
		}

	}

	void Cleanup() const {
		lvl->Cleanup();
		delete lvl;
		SDL_FreeSurface(this->img);
//		Mix_FreeMusic(music);
	}


	//Events

	void OnInputFocus() {
	}

	void OnInputBlur() {
	}

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

		if (sym == SDLK_w){
				this->lvl->getPlayer()->jump();
		}
		if (sym == SDLK_d)
			this->MoveRight = true;

		if (sym == SDLK_a)
			this->MoveLeft = true;
	}

	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
		this->MoveRight = false;
		this->MoveLeft = false;
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
		this->lvl->getPlayer()->Shoot(mX + this->lvl->getCamera(), mY);
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
