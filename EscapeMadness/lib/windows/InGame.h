#ifndef INGAME_H_
#define INGAME_H_

#include "Event.h"
#include "../common/Level.h"
#include "../common/BossLevel.h"
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>
#include "../common/Structure.h"
#include "../character/BasicCharacter.h"
#include "../platform/Platform.h"

class InGame: public Event {
private:
	Level *lvl;
	BossLevel *blvl;
	SDL_Surface* img;
	Mix_Music *music;
	int Current;
	int Lifes;
	bool MoveRight;
	bool MoveLeft;
	bool Standing;
	bool finished;
	bool gameOver;
	int gameOverCount;
	bool playFirst;
	int currentDisplay; // 0 para Level, 1 para bossLevel, 2 para creditos

public:
	InGame(int id) {
		Current = id;
		gameOver = false;
		MoveRight = false;
		MoveLeft = false;
		playFirst = false;
		currentDisplay = 0;

	}

	bool Init() {

		lvl = new Level();
		lvl->Init();
		blvl = new BossLevel();
		blvl->Init();

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			return false;
		}

		music = Mix_LoadMUS("./res/OST/Zandback.ogg");

		this->img = Surface::Load((char*) "./res/heart.png");
		return true;
	}

	int Loop() {

		if (playFirst == false) {
			Mix_PlayMusic(music, -1);
			playFirst = true;
		}

		if (MoveRight) {
			movePlayer(0);
			Standing = false;
		}
		if (MoveLeft) {
			movePlayer(1);
			Standing = false;
		}

		if (!MoveLeft && !MoveRight && !Standing) {
			movePlayer(2);
			Standing = true;
		}

		switch (currentDisplay) {
		case 0:
			if (lvl->getPlayer()->lifes() <= 0) {
				gameOver = true;
			}

			if (lvl->getPlayer()->getBody()->GetTransform().p.y < 0) {
				gameOver = true;
			}

			lvl->Loop();

			break;
		case 1:
			if (blvl->getPlayer()->lifes() <= 0) {
				gameOver = true;
			}

			if (blvl->getPlayer()->getBody()->GetTransform().p.y < 0) {
				gameOver = true;
			}

			blvl->Loop();
			break;
		case 2:
			break;
		}

		if (Current != Structure::INGAME) {
			this->Cleanup();
		}

		return Current;

	}

	void movePlayer(int LR) {
		switch (currentDisplay) {
		case 0:
			switch (LR) {
			case 0:
				this->lvl->getPlayer()->moveRight();
				break;
			case 1:
				this->lvl->getPlayer()->moveLeft();
				break;
			case 2:
				this->lvl->getPlayer()->StopX();
				break;
			}
			break;
		case 1:
			switch (LR) {
			case 0:
				this->blvl->getPlayer()->moveRight();
				break;
			case 1:
				this->blvl->getPlayer()->moveLeft();
				break;
			case 2:
				this->blvl->getPlayer()->StopX();
				break;
			}
			break;
		}

	}

	void Render(SDL_Surface* Display, float camera = 0) {

		if (isNull()) {
			this->Init();
		}
		switch (currentDisplay) {
		case 0:
			lvl->Render(Display);

			for (int i = 0; i < this->lvl->getPlayer()->lifes(); i++) {
				Surface::Draw(Display, this->img, (i + 1) * 25, 25);
			}

			break;
		case 1:
			blvl->Render(Display);

			for (int i = 0; i < this->blvl->getPlayer()->lifes(); i++) {
				Surface::Draw(Display, this->img, (i + 1) * 25, 25);
			}

			break;
		}

		if (lvl->finished() && this->currentDisplay == 0) {
			// this->currentDisplay = 1; crashea al tratar de entrar a bosslvl
		}

		//Draw HUD

		if (gameOver) {
			Surface::DrawText("Game Over", Display, 350, 350, 255, 255, 255,
					75);
		}

	}

	bool isNull() {
		if (img == NULL) {
			return true;
		}

		return false;
	}

	void Cleanup() {
		lvl->Cleanup();
		blvl->Cleanup();
		delete lvl;
		delete blvl;
		SDL_FreeSurface(this->img);
		img = NULL;
		Mix_FreeMusic(music);
	}

	//Events

	void OnInputFocus() {
	}

	void OnInputBlur() {
	}

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

		if (sym == SDLK_w) {
			switch (currentDisplay) {
			case 0:
				this->lvl->getPlayer()->jump();
				break;
			case 1:
				this->blvl->getPlayer()->jump();
				break;
			}

		}
		if (sym == SDLK_d)
			this->MoveRight = true;

		if (sym == SDLK_a)
			this->MoveLeft = true;
	}

	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
		if (sym == SDLK_d || sym == SDLK_a) {
			this->MoveRight = false;
			this->MoveLeft = false;
		}
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

}
;

#endif /* INGAME_H_ */
