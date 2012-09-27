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
	int size;

public:
	Button(char* input, int x, int y, SDL_Surface* bg, int size) {
		Background = bg;
		this->x = x;
		this->y = y;
		text = input;
		this->size = size;

	}

	void render() {
		Surface::DrawText(text, Background, x, y, 247, 49, 49, size);
	}

	bool isClicked(int mX, int mY) {
		if(mX>=x&&mX<=x+50&&mY>=y&&mY<=y+50)
			return true;
		return false;
	}

};

#endif /* BUTTON_H_ */
