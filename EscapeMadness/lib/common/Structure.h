#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "SDL/SDL.h"

class Structure {
public:
	enum {
		MENU, INGAME, HELP
	};
	Structure() {
	}

	virtual bool Init() = 0;

	virtual void Render(SDL_Surface* Display,float camera) = 0;

	virtual int Loop() = 0;

	virtual void Cleanup() const = 0;
};

#endif
