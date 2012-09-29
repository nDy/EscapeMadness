#ifndef STORY_H_
#define STORY_H_

#include <SDL/SDL.h>
#include "Event.h"
#include "../common/Structure.h"
#include "../common/Button.h"
#include <SDL/SDL_mixer.h>

class Story: public Event {

private:

	SDL_Surface* Background;
	SDL_Surface* frame;
	int Current;
	int show;
	char * texto;

public:

	Story(int id) {
		Current = id;
		show = 0;
	}

	bool Init() {
		Background = Surface::Load("./res/Fondos/back.jpg");
		frame = Surface::Load("./res/frame.png");

		if (Background == NULL) {
			return false;
		}

		if (frame == NULL) {
			return false;
		}

		return true;
	}

	int Loop() {

		if (Current != Structure::STORY) {
			this->Cleanup();
		}

		switch (show) {
		case 0:
			texto = (char *) "Ughhh....";
			break;
		case 1:
			texto =
					(char *) "(Enfermera) No desesperes, ya traigo algo para el dolor.";
			break;
		case 2:
			texto = (char *) "...";
			break;
		case 3:
			texto = (char *) "******ALARMA SONANDO******";
			break;
		case 4:
			texto =
					(char *) "(Enfermera) Si te dejo aqui moriras, y... honestamente, no podria hacerte eso.";
			break;
		case 5:
			texto =
					(char *) "(Enfermera) Vete. La salida siempre es hacia arriba";
			break;
		case 6:
			texto = (char *) "Arghhh";
			break;
		case 7:
			texto = (char *) "...";
			break;
		case 8:
			Current = Structure::INGAME;
			break;

		}

		return Current;
	}

	void Render(SDL_Surface* Display, float camera = 0) {

		Surface::Draw(Display, Background, camera, 0);
		Surface::Draw(Display, frame, 0, 384);

		Surface::DrawText(texto, Display, 25, 400, 255, 255, 255, 20);

		Surface::DrawText((char *) "Presiona espacio para continuar", Display,
				25, 684, 255, 255, 255, 20);

	}

	void Cleanup() {
		SDL_FreeSurface(Background);
		SDL_FreeSurface(frame);
	}

	//Events

	void OnInputFocus() {
	}

	void OnInputBlur() {
	}

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
		if (sym == SDLK_SPACE)
			show++;
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
