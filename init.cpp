// libc
#include <cstdlib>
#include <ctime>
#include <err.h>
// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// fractals
#include "macros.hpp"

f_constructor static void sdl_init(void);
f_destructor static void sdl_quit(void);

static void sdl_init(void) {
	srand((unsigned)time(nullptr));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "error could not initialize SDL2: '%s'\n",
			 SDL_GetError());
	int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
	if (IMG_Init(flags) != flags)
		errx(EXIT_FAILURE, "error could not initialize SDL2_image: '%s'\n",
			 IMG_GetError());
}

static void sdl_quit(void) { SDL_Quit(); }
