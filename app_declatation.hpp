#ifndef FRACTALS_DECLARATION_APP_H
#define FRACTALS_DECLARATION_APP_H

// stdlib
#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
#include <unordered_set>
// libc
#include <err.h>
// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// fractals
#include "keyboard.hpp"
#include "macros.hpp"
#include "window.hpp"

namespace fractals {

class Sprite;
class UpdatableSprite;

class App {
public:
	App(int argc = 0, char** argv = nullptr);
	virtual ~App(void);
	int main(void);

protected:
	void update_loop(void);
	void update(void);
	void main_loop(void);
	void events(void);
	void pause_events(void);
	void draw(void);

	void quit(void);
	void force_quit(void);

	void toggle_pause(void);

public:
	Window window;
	Keyboard keyboard;
	std::thread update_loop_thread;
	bool looping;
	bool pause;
	int exit_code;
	double framerate;

	std::unordered_set<Sprite*> dynamic_sprites;
	std::unordered_set<Sprite*> sprites;
	std::unordered_set<UpdatableSprite*> updatable_sprites;
};

} // namespace fractals

#endif // FRACTALS_DECLARATION_APP_H
