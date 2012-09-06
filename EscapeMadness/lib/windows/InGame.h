#ifndef INGAME_H_
#define INGAME_H_

#include "Event.h"
#include "Structure.h"

class InGame: public Event, public Structure {
private:

public:
	InGame() {

	}

	bool Init() {
		return true;
	}

	void Event(SDL_Event* Event) {

	}

	void Loop() const {

	}

	void Render() const {

	}

	void Cleanup() const {

	}

};

#endif /* INGAME_H_ */
