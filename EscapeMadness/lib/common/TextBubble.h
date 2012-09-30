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

	SDL_Surface* frame;
	int x;
	int y;
	char* text;
	int size;

public:

	TextBubble(char* input, int x, int y, int size) {
		this->x = x;
		this->y = y;
		this->text = input;
		this->size = size;
		this->frame = Surface::Load("./res/frame.png");

	}

	void switchText(char* input) {
		this->text = input;
	}
	void switchPos(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void render(SDL_Surface* Display) {
		Surface::Draw(Display, frame, x, y);
		Surface::DrawText(text, Display, x + 10, y + 10, 255, 255, 255, size);
	}

};

#endif /* TEXTBUBBLE_H_ */
