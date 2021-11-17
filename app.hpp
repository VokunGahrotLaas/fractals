#ifndef FRACTALS_APP_H
#define FRACTALS_APP_H

// fractals
#include "app_declatation.hpp"
#include "sprites/player.hpp"
#include "sprites/rect.hpp"
#include "sprites/sprite.hpp"
#include "sprites/updatable_sprite.hpp"

namespace fractals {

App::App(f_unused int argc, f_unused char** argv)
	: window(), keyboard(), update_loop_thread(), looping(false), pause(false),
	  exit_code(EXIT_SUCCESS), framerate(60), dynamic_sprites(), sprites(),
	  updatable_sprites() {
	f_debug_func_name();
}

App::~App(void) {
	f_debug_func_name();
	for (Sprite* sprite: dynamic_sprites)
		delete sprite;
}

int App::main(void) {
	f_debug_func("begin");
	looping = true;
	update_loop_thread = std::thread(&App::update_loop, this);
	main_loop();
	looping = false;
	f_debug_func("end");
	return exit_code;
}

void App::update_loop(void) {
	f_debug_func("begin");
	while (looping) {
		if (!pause) update();
	}
	f_debug_func("end");
}

void App::update(void) {
	auto copy = updatable_sprites;
	for (UpdatableSprite* sprite: copy)
		if (updatable_sprites.contains(sprite)) sprite->update();
	SDL_Color& color = window.background_color();
	color.r = (Uint8)(color.r * 0.99);
	color.g = (Uint8)(color.g * 0.99);
	color.b = (Uint8)(color.b * 0.99);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void App::main_loop(void) {
	f_debug_func("begin");
	auto start = std::chrono::high_resolution_clock::now();
	for (auto end = start; looping; start = end) {
		if (pause)
			pause_events();
		else
			events();
		if (!looping) break;
		draw();
		if (!looping) break;
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		std::chrono::duration<double, std::milli> to_wait =
			std::chrono::milliseconds(1000) / framerate - elapsed;
		if (to_wait < decltype(to_wait)::zero()) {
			f_debug_func("frame took too long (%lg > %lg)", elapsed.count(),
						 1000. / framerate);
			continue;
		}
		std::this_thread::sleep_for(
			std::max(decltype(to_wait)::zero(), to_wait));
		end = std::chrono::high_resolution_clock::now();
		// std::cout << "Elapsed: " << elapsed.count() << "ms" << std::endl;
		// std::cout << "To Wait: " << to_wait.count() << "ms" << std::endl;
	}
	f_debug_func("end");
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
			case SDLK_F11:
				window.toggle_fullscreen();
				break;
			case SDLK_ESCAPE:
			case SDLK_p:
				toggle_pause();
				break;
			case SDLK_q:
				if (keyboard.is_key_pressed(SDLK_LCTRL)
					| keyboard.is_key_pressed(SDLK_RCTRL))
					quit();
				break;
			case SDLK_c: {
				Uint8 r = (Uint8)rand(), g = (Uint8)rand(), b = (Uint8)rand();
				window.background_color() = { r, g, b, 255 };
				f_debug_func("changed color: %.2hhx%.2hhx%.2hhx", r, g, b);
				break;
			}
			case SDLK_r: {
				SDL_Rect r;
				r.w = window.w() / 10;
				r.h = window.h() / 10;
				r.x = window.w() / 2 - r.w / 2;
				r.y = window.h() / 2 - r.h / 2;
				dynamic_sprites.insert(new Player(*this, r, f_rand_color()));
				break;
			}
			case SDLK_d: {
				for (Sprite* sprite: dynamic_sprites)
					delete sprite;
				dynamic_sprites.clear();
				break;
			}
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void App::pause_events(void) {
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
			case SDLK_F11:
				window.toggle_fullscreen();
				break;
			case SDLK_ESCAPE:
			case SDLK_p:
				toggle_pause();
				break;
			case SDLK_q:
				if (keyboard.is_key_pressed(SDLK_LCTRL)
					| keyboard.is_key_pressed(SDLK_RCTRL))
					quit();
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
	window.clear();
	for (Sprite* sprite: sprites)
		sprite->draw(window);
	window.present();
}

void App::quit(void) {
	if (std::this_thread::get_id() == update_loop_thread.get_id())
		errx(EXIT_FAILURE, "can't quit inside the update loop");
	f_debug_func_name();
	looping = false;
	update_loop_thread.join();
}

void App::force_quit(void) {
	if (std::this_thread::get_id() == update_loop_thread.get_id())
		errx(EXIT_FAILURE, "can't force quit inside the update loop");
	f_debug_func_name();
	quick_exit(exit_code);
}

void App::toggle_pause(void) {
	pause = !pause;
	f_debug_func("%s", pause ? "paused" : "unpaused");
}

} // namespace fractals

#endif // FRACTALS_APP_H
