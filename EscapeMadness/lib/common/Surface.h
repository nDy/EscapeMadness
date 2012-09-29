#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

class Surface {
public:
	Surface();

	static SDL_Surface* Load(const char* File) {
		SDL_Surface* Surf_Temp = NULL;
		SDL_Surface* Surf_Return = NULL;

		if ((Surf_Temp = IMG_Load(File)) == NULL) {
			return NULL;
		}

		Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
		SDL_FreeSurface(Surf_Temp);

		return Surf_Return;
	}

	static bool Draw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X,
			int Y) {
		if (Surf_Dest == NULL || Surf_Src == NULL) {
			return false;
		}

		SDL_Rect DestR;

		DestR.x = X;
		DestR.y = Y;

		SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

		return true;
	}

	static bool DrawText(const char* text, SDL_Surface* Dest, int X, int Y,
			Uint8 r, Uint8 g, Uint8 b, int size) {
		if (!(TTF_Init() < 0) && !(Dest == NULL)) {
			TTF_Font* font = NULL;
			SDL_Color textColor = { r, g, b };
			font = TTF_OpenFont("./res/Fonts/font.ttf", size);
			SDL_Surface* message = TTF_RenderText_Blended(font, text, textColor);
			TTF_CloseFont(font);
			return Draw(Dest, message, X, Y);
		}

		return false;
	}

};

#endif
