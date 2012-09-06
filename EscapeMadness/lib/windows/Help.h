#ifndef HELP_H_
#define HELP_H_

#include "Event.h"
#include "Structure.h"

class Help: public Event, public Structure {
private:

public:
	Help() {

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

#endif /* HELP_H_ */
