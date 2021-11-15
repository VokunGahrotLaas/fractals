// stdlib
#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
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

class App {
public:
	App(int argc = 0, char** argv = nullptr);
	virtual ~App(void);
	int main(void);

protected:
	void update_loop(void);
	void updates(void);
	void main_loop(void);
	void events(void);
	void draw(void);

	void quit(void);
	void force_quit(void);

	void toggle_fullscreen(void);

	Window window;
	Keyboard keyboard;
	std::thread* update_loop_thread;
	bool looping;
	int exit_code;
	double framerate;
};

} // namespace fractals

namespace fractals {

App::App(f_unused int argc, f_unused char** argv)
	: window(), keyboard(), update_loop_thread(nullptr), looping(false),
	  exit_code(EXIT_SUCCESS), framerate(60) {
	f_debug_func_name();
}

App::~App(void) {
	if (update_loop_thread) delete update_loop_thread;
	f_debug_func_name();
}

int App::main(void) {
	f_debug_func_name();
	looping = true;
	update_loop_thread = new std::thread(&App::update_loop, this);
	main_loop();
	looping = false;
	return exit_code;
}

void App::update_loop(void) {
	f_debug_func_name();
	while (looping) {
		updates();
	}
}

void App::updates(void) {
	//
}

void App::main_loop(void) {
	f_debug_func_name();
	while (looping) {
		auto start = std::chrono::high_resolution_clock::now();
		events();
		if (!looping) break;
		draw();
		if (!looping) break;
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		std::chrono::duration<double, std::milli> to_wait =
			std::chrono::milliseconds(1000) / framerate - elapsed;
		std::this_thread::sleep_for(
			std::max(decltype(to_wait)::zero(), to_wait));
		// std::cout << "Elapsed: " << elapsed.count() << "ms" << std::endl;
		// std::cout << "To Wait: " << to_wait.count() << "ms" << std::endl;
	}
}

void App::events(void) {
	SDL_Event event;
	while (looping && SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit();
			break;
		case SDL_WINDOWEVENT:
			window.event(event.window);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit();
				break;
			case SDLK_F11:
				window.toggle_fullscreen();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void App::draw(void) { window.draw(); }

void App::quit(void) {
	if (std::this_thread::get_id() == update_loop_thread->get_id())
		errx(EXIT_FAILURE, "can't quit inside the update loop");
	f_debug_func_name();
	looping = false;
	update_loop_thread->join();
}

void App::force_quit(void) {
	if (std::this_thread::get_id() == update_loop_thread->get_id())
		errx(EXIT_FAILURE, "can't force quit inside the update loop");
	f_debug_func_name();
	looping = false;
	update_loop_thread->detach();
}

} // namespace fractals
