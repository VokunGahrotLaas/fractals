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

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::thread* update_loop_thread;
	bool looping;
	int exit_code;
	int w;
	int h;
	double framerate;
	SDL_Color background_color;
};

} // namespace fractals

namespace fractals {

App::App(void)
	: window(nullptr), renderer(nullptr), update_loop_thread(nullptr),
	  looping(false), exit_code(EXIT_SUCCESS), w(0), h(0), framerate(60),
	  background_color({ 0, 0, 0, 255 }) {
	//
}

App::~App(void) {
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (update_loop_thread) delete update_loop_thread;
}

int App::main(int argc, char** argv) {
	init(argc, argv);
	looping = true;
	update_loop_thread = new std::thread(&App::update_loop, this);
	main_loop();
	looping = false;
	update_loop_thread->detach();
	return exit_code;
}

void App::init(unused int argc, unused char** argv) {
	window = SDL_CreateWindow(
		"Fractals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
		SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_BORDERLESS
			| SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		errx(EXIT_FAILURE, "error could not create a window: '%s'",
			 SDL_GetError());
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		errx(EXIT_FAILURE, "error could not create a renderer: '%s'",
			 SDL_GetError());
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
						   background_color.b, 255);
}

void App::update_loop(void) {
	while (looping) {
		updates();
		if (SDL_SetWindowOpacity(window, 1.f) != 0)
			errx(EXIT_FAILURE, "opacity");
		std::this_thread::sleep_for(
			std::chrono::duration<double, std::milli>(1000));
		if (SDL_SetWindowOpacity(window, 0.f) != 0)
			errx(EXIT_FAILURE, "opacity");
		std::this_thread::sleep_for(
			std::chrono::duration<double, std::milli>(1000));
	}
}

void App::updates(void) {
	//
}

void App::main_loop(void) {
	while (looping) {
		auto start = std::chrono::high_resolution_clock::now();
		events();
		draw();
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
			looping = false;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				w = event.window.data1;
				h = event.window.data1;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				looping = false;
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

void App::draw(void) {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

} // namespace fractals
