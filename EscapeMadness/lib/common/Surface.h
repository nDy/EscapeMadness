#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <SDL/SDL.h>

class Surface {
public:
	Surface();

	static SDL_Surface* Load(char* File) {
		SDL_Surface* Surf_Temp = NULL;
		SDL_Surface* Surf_Return = NULL;

		if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
			return NULL;
		}

		Surf_Return = SDL_DisplayFormat(Surf_Temp);
		SDL_FreeSurface(Surf_Temp);

		return Surf_Return;
	}

	static bool Draw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
		if (Surf_Dest == NULL || Surf_Src == NULL) {
			return false;
		}

		SDL_Rect DestR;

		DestR.x = X;
		DestR.y = Y;

		SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

		return true;
	}

	static bool DrawText(string text, SDL_Surface* Dest, int X, int Y, int r, int g, int b, int size) {
		if (Surf_Dest == NULL || Surf_Src == NULL) {
			return false;
		}

		SDL_Surface* message = NULL;
		TTF_Font* font = NULL;
		SDL_Color textColor = { r, g, b };
		font = TTF_OpenFont( "font.ttf", size );
		message = TTF_RenderText_Solid( font, text, textColor );
		apply_surface( 0, 150, message, Dest );

		return true;
	}

};

#endif
