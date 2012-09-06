/*
 * Platform.h
 *
 *  Created on: Sep 6, 2012
 *      Author: root
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "../common/Structure.h"

class Platform: public Structure{
private:
	SDL_Surface* img;
public:
	Platform(int x, int y){}//TODO: World Parameter
	Platform(int x, int y, float movementlength,short orientation){}//TODO: World Parameter
	Platform(int x, int y, float angle){}//TODO: World Parameter
	Platform(int x, int y, float angle, float movementlength){}//TODO: World Parameter
	Platform(int x, int y, float angle, float movementlength,short orientation){}//TODO: World Parameter
	void Render(SDL_Surface* Display) {

	}
};



#endif /* PLATFORM_H_ */
