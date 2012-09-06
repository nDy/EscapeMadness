#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "SDL/SDL.h"

class Structure {
public:

	virtual bool Init() = 0;

	virtual void Event(SDL_Event* Event) = 0;

	virtual void Render(SDL_Surface* Display) = 0;

	virtual void Loop() const = 0;

	virtual void Cleanup() const = 0;
};

#endif
