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
#include "macros.hpp"
#include "window.hpp"

namespace fractals {

class App {
public:
	App(void);
	virtual ~App(void);
	int main(int argc, char** argv);

protected:
	void init(int argc, char** argv);
	void update_loop(void);
	void updates(void);
	void main_loop(void);
	void events(void);
	void draw(void);

	void clean(void);
	void quit(void);
	void force_quit(void);

	void toggle_fullscreen(void);

	Window window;
	std::thread* update_loop_thread;
	bool looping;
	int exit_code;
	double framerate;
};

} // namespace fractals

namespace fractals {

App::App(void)
	: window(), update_loop_thread(nullptr), looping(false),
	  exit_code(EXIT_SUCCESS), framerate(60) {
	//
}

App::~App(void) {
	if (update_loop_thread) delete update_loop_thread;
}

int App::main(int argc, char** argv) {
	debug("main()\n");
	init(argc, argv);
	looping = true;
	update_loop_thread = new std::thread(&App::update_loop, this);
	main_loop();
	looping = false;
	return exit_code;
}

void App::init(unused int argc, unused char** argv) {
	debug("init()\n");
	window.init();
}

void App::update_loop(void) {
	debug("update_loop()\n");
	while (looping) {
		updates();
	}
}

void App::updates(void) {
	//
}

void App::main_loop(void) {
	debug("main_loop()\n");
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

void App::clean(void) { debug("clean()\n"); }

void App::quit(void) {
	if (std::this_thread::get_id() == update_loop_thread->get_id())
		errx(EXIT_FAILURE, "can't quit inside the update loop");
	debug("quit()\n");
	looping = false;
	update_loop_thread->join();
	clean();
}

void App::force_quit(void) {
	if (std::this_thread::get_id() == update_loop_thread->get_id())
		errx(EXIT_FAILURE, "can't force quit inside the update loop");
	debug("force_quit()\n");
	looping = false;
	update_loop_thread->detach();
}

} // namespace fractals
