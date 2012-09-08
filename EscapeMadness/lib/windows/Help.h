#ifndef HELP_H_
#define HELP_H_

#include "Event.h"
#include "../common/Structure.h"

class Help{
private:

public:
	Help() {

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

#endif /* HELP_H_ */
