#ifndef MENU_H_
#define MENU_H_

#include "Event.h"
#include "Structure.h"

class Menu: public Event, public Structure {
private:

public:
	Menu() {

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

#endif /* MENU_H_ */
