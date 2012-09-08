#ifndef MENU_H_
#define MENU_H_

#include "Event.h"
#include "../common/Structure.h"

class Menu {
private:

public:
	Menu() {

	}

	bool Init() {
		return true;
	}

	void Event(SDL_Event* Event) {

	}

	int Loop(int Current) {
		return Current;
	}

	void Render() const {

	}

	void Cleanup() const {

	}

};

#endif /* MENU_H_ */
