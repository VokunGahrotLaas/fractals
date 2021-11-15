// stdlib
#include <iostream>
// libc
#include <err.h>
// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// fractals
#include "macros.hpp"

namespace fractals {

class Keyboard {
public:
	Keyboard(void);
	virtual ~Keyboard(void);

	bool is_key_pressed(SDL_Scancode code) const;
	bool is_key_pressed(SDL_Keycode code) const;

protected:
	const Uint8* m_states;
};

} // namespace fractals

namespace fractals {

Keyboard::Keyboard(void): m_states(SDL_GetKeyboardState(NULL)) {
	f_debug_func_name();
}

Keyboard::~Keyboard(void) { f_debug_func_name(); }

bool Keyboard::is_key_pressed(SDL_Scancode code) const {
	return m_states[code];
}

bool Keyboard::is_key_pressed(SDL_Keycode code) const {
	return m_states[SDL_GetScancodeFromKey(code)];
}

} // namespace fractals
