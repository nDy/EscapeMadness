/*
 * Button.h
 *
 *  Created on: Sep 9, 2012
 *      Author: ndy
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "SDL/SDL.h"
#include "Surface.h"
#include <iostream>
class Button {
	SDL_Surface* Background;
	int x;
	int y;
	char* text;
public:
	Button(char* input, int x, int y, SDL_Surface* bg) {
		Background = bg;
		this->x = x;
		this->y = y;
		text = input;

	}

	void render() {
		Surface::DrawText(text, Background, x, y, 255, 255, 255, 50);
	}

	bool isClicked(int mX, int mY) {
		if(mX>=x&&mX<=x+50&&mY>=y&&mY<=y+50)
			return true;
		return false;
	}

};

#endif /* BUTTON_H_ */
