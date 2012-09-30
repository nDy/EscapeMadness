/*
 * TextBubble.h
 *
 *  Created on: Sep 9, 2012
 *      Author: ndy
 */

#ifndef TEXTBUBBLE_H_
#define TEXTBUBBLE_H_

#include "SDL/SDL.h"
#include "Surface.h"
#include <iostream>

class TextBubble {

	SDL_Surface* background;
	SDL_Surface* frame;
	int x;
	int y;
	char* text;
	int size;

public:

	TextBubble (char* input, int x, int y, SDL_Surface* Background, int size) {
		this->background = Background;
		this->x = x;
		this->y = y;
		this->text = input;
		this->size = size;
		this->frame = Surface::Load("./res/frame.png");

	}

	void render() {
		Surface::Draw(background, frame, x, y);
		Surface::DrawText(text, frame, x, y, 255, 255, 255, size);
	}

	bool isClicked(int mX, int mY) {
		if(mX >= x && mX <= x + 50 && mY >= y && mY <= y + 50)
			return true;
		return false;
	}

};

#endif /* TEXTBUBBLE_H_ */
