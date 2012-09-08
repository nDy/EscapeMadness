#ifndef _EVENT_H_
#define _EVENT_H_

#include <SDL/SDL.h>

class Event {
public:
	Event() {
	}
	void CheckEvent(SDL_Event* event) {
		switch (event->type) {
		case SDL_ACTIVEEVENT: {
			switch (event->active.state) {
			case SDL_APPMOUSEFOCUS: {
				if (event->active.gain)
					OnMouseFocus();
				else
					OnMouseBlur();

				break;
			}
			case SDL_APPINPUTFOCUS: {
				if (event->active.gain)
					OnInputFocus();
				else
					OnInputBlur();

				break;
			}
			case SDL_APPACTIVE: {
				if (event->active.gain)
					OnRestore();
				else
					OnMinimize();

				break;
			}
			}
			break;
		}

		case SDL_KEYDOWN: {
			OnKeyDown(event->key.keysym.sym, event->key.keysym.mod,
					event->key.keysym.unicode);
			break;
		}

		case SDL_KEYUP: {
			OnKeyUp(event->key.keysym.sym, event->key.keysym.mod,
					event->key.keysym.unicode);
			break;
		}

		case SDL_MOUSEMOTION: {
			OnMouseMove(event->motion.x, event->motion.y, event->motion.xrel,
					event->motion.yrel,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			switch (event->button.button) {
			case SDL_BUTTON_LEFT: {
				OnLButtonDown(event->button.x, event->button.y);
				break;
			}
			case SDL_BUTTON_RIGHT: {
				OnRButtonDown(event->button.x, event->button.y);
				break;
			}
			case SDL_BUTTON_MIDDLE: {
				OnMButtonDown(event->button.x, event->button.y);
				break;
			}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP: {
			switch (event->button.button) {
			case SDL_BUTTON_LEFT: {
				OnLButtonUp(event->button.x, event->button.y);
				break;
			}
			case SDL_BUTTON_RIGHT: {
				OnRButtonUp(event->button.x, event->button.y);
				break;
			}
			case SDL_BUTTON_MIDDLE: {
				OnMButtonUp(event->button.x, event->button.y);
				break;
			}
			}
			break;
		}

		case SDL_JOYAXISMOTION: {
			OnJoyAxis(event->jaxis.which, event->jaxis.axis,
					event->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION: {
			OnJoyBall(event->jball.which, event->jball.ball, event->jball.xrel,
					event->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION: {
			OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP: {
			OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
			break;
		}

		case SDL_QUIT: {
			OnExit();
			break;
		}

		case SDL_SYSWMEVENT: {
			//Ignore
			break;
		}

		case SDL_VIDEORESIZE: {
			OnResize(event->resize.w, event->resize.h);
			break;
		}

		case SDL_VIDEOEXPOSE: {
			OnExpose();
			break;
		}

		default: {
			OnUser(event->user.type, event->user.code, event->user.data1,
					event->user.data2);
			break;
		}
		}
	}

	virtual void OnInputFocus()=0;

	virtual void OnInputBlur()=0;

	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)=0;

	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)=0;

	virtual void OnMouseFocus()=0;

	virtual void OnMouseBlur()=0;

	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,
			bool Right, bool Middle)=0;

	virtual void OnMouseWheel(bool Up, bool Down)=0;    //Not implemented

	virtual void OnLButtonDown(int mX, int mY)=0;

	virtual void OnLButtonUp(int mX, int mY)=0;

	virtual void OnRButtonDown(int mX, int mY)=0;

	virtual void OnRButtonUp(int mX, int mY)=0;

	virtual void OnMButtonDown(int mX, int mY)=0;

	virtual void OnMButtonUp(int mX, int mY)=0;

	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)=0;

	virtual void OnJoyButtonDown(Uint8 which, Uint8 button)=0;

	virtual void OnJoyButtonUp(Uint8 which, Uint8 button)=0;

	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)=0;

	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)=0;

	virtual void OnMinimize()=0;

	virtual void OnRestore()=0;

	virtual void OnResize(int w, int h)=0;

	virtual void OnExpose()=0;

	virtual void OnExit()=0;

	virtual void OnUser(Uint8 type, int code, void* data1, void* data2)=0;
};

#endif
