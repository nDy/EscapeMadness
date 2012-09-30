#ifndef STORY_H_
#define STORY_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"
#include "../common/TextBubble.h"
#include "../common/Button.h"
#include <SDL/SDL_mixer.h>

class Story: public Event {

private:

	SDL_Surface* Background;
	TextBubble* tb;
	int Current;
	Mix_Music *music;
	bool playFirst;
	int currentTb;

public:

	Story(int id) {
		Current = id;
		playFirst = false;
		currentTb = 0;
	}

	bool Init() {
		Background = Surface::Load("./res/Fondos/white.jpg");
		tb = new TextBubble((char *) "Te sientes bien?", 1024 / 2, 0, 20);

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			return false;
		}

		music = Mix_LoadMUS("./res/OST/09 The Nurse Who Loved Me.wav");

		if (Background == NULL) {
			return false;
		}

		return true;
	}

	int Loop() {

		if (Current != Structure::STORY) {
			this->Cleanup();
		}

		if (playFirst == false) {
			Mix_PlayMusic(music, -1);
			playFirst = true;
		}

		return Current;
	}

	void Render(SDL_Surface* Display, float camera = 0) {

		if (isNull()) {
			this->Init();
		}

		Surface::Draw(Display, Background, 0, 0);
		tb->render(Display);

	}

	bool isNull() {
		if (Background == NULL) {
			return true;
		}

		return false;
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
		if (sym == SDLK_SPACE)
			switch (currentTb) {
			case 0:
				this->tb->switchText((char*) "*Balbucea*");
				this->tb->switchPos(0, 768/2);
				this->currentTb++;
				break;
			case 1:
				this->tb->switchText((char*) "No puedo verte asi");
				this->tb->switchPos(1024/2, 0);
				this->currentTb++;
				break;
			case 2:
				this->tb->switchText((char*) "Que sucede?");
				this->tb->switchPos(0, 768/2);
				this->currentTb++;
				break;
			case 3:
				this->tb->switchText((char*) "Necesitas salir de aqui");
				this->tb->switchPos(1024/2, 0);
				this->currentTb++;
				break;
			case 4:
				this->tb->switchText((char*) "Pero...");
				this->tb->switchPos(0, 768/2);
				this->currentTb++;
				break;
			case 5:
				this->tb->switchText((char*) "No, No hay tiempo para esto...");
				this->tb->switchPos(1024/2, 0);
				this->currentTb++;
				break;
			case 6:
				this->tb->switchText((char*) "Que pretendes hacer con eso?");
				this->tb->switchPos(0, 768/2);
				this->currentTb++;
				break;
			case 7:
				this->tb->switchText((char*) "No puedo estar aqui cuando despiertes");
				this->tb->switchPos(1024/2, 0);
				this->currentTb++;
				break;
			case 8:
				this->tb->switchText((char*) "Por que?");
				this->tb->switchPos(0, 768/2);
				this->currentTb++;
				break;
			case 9:
				this->tb->switchText((char*) "No es seguro... Para mi...");
				this->tb->switchPos(1024/2, 0);
				this->currentTb++;
				break;
			case 10:
				Current = Structure::INGAME;
				break;
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

#endif /* STORY_H_ */
