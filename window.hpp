#ifndef FRACTALS_WINDOW_H
#define FRACTALS_WINDOW_H

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

class Window {
public:
	Window(void);
	virtual ~Window(void);

	void event(SDL_WindowEvent event);
	void toggle_fullscreen(void);
	void clear(void);
	void present(void);

	void color(SDL_Color color);
	SDL_Color color(void) const;

	void draw_rect(SDL_Rect* rect);
	void fill_rect(SDL_Rect* rect);

	SDL_Color& background_color(void);
	SDL_Color const& background_color(void) const;
	int w(void) const;
	int h(void) const;

protected:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_w;
	int m_h;
	bool m_fullscreen;
	SDL_Color m_background_color;
};

} // namespace fractals

namespace fractals {

Window::Window(void)
	: m_window(nullptr), m_renderer(nullptr), m_w(1280), m_h(720),
	  m_fullscreen(true), m_background_color({ 0, 0, 0, 255 }) {
	f_debug_func_name();
	m_window = SDL_CreateWindow("Fractals", SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, 1280, 720,
								SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
	if (m_window == NULL)
		errx(EXIT_FAILURE, "error could not create a window: '%s'",
			 SDL_GetError());
	m_fullscreen = !m_fullscreen;
	if (!m_fullscreen) toggle_fullscreen();
	m_renderer = SDL_CreateRenderer(
		m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
		errx(EXIT_FAILURE, "error could not create a renderer: '%s'",
			 SDL_GetError());
	clear();
	present();
	SDL_ShowWindow(m_window);
}

Window::~Window(void) {
	f_debug_func_name();
	if (m_window) SDL_DestroyWindow(m_window);
	if (m_renderer) SDL_DestroyRenderer(m_renderer);
}

void Window::event(SDL_WindowEvent event) {
	switch (event.event) {
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		m_w = event.data1;
		m_h = event.data2;
		f_debug_func("resize event (%i, %i)", m_w, m_h);
		break;
	default:
		break;
	}
}

void Window::toggle_fullscreen(void) {
	f_debug_func_name();
	m_fullscreen = !m_fullscreen;
	SDL_HideWindow(m_window);
	SDL_SetWindowBordered(m_window, m_fullscreen ? SDL_FALSE : SDL_TRUE);
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(SDL_GetWindowDisplayIndex(m_window), &mode);
	if (m_fullscreen) {
		SDL_SetWindowPosition(m_window, 0, 0);
		SDL_SetWindowSize(m_window, mode.w, mode.h);
	} else {
		int tw = mode.w / 2, th = mode.h / 2;
		SDL_SetWindowSize(m_window, tw, th);
		SDL_SetWindowPosition(m_window, (mode.w - tw) / 2, (mode.h - th) / 2);
	}
	SDL_ShowWindow(m_window);
}

void Window::clear(void) {
	SDL_SetRenderDrawColor(m_renderer, m_background_color.r,
						   m_background_color.g, m_background_color.b,
						   m_background_color.a);
	SDL_RenderClear(m_renderer);
}

void Window::present(void) { SDL_RenderPresent(m_renderer); }

void Window::color(SDL_Color color) {
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

SDL_Color Window::color(void) const {
	SDL_Color color;
	SDL_GetRenderDrawColor(m_renderer, &color.r, &color.g, &color.b, &color.a);
	return color;
}

void Window::draw_rect(SDL_Rect* rect) { SDL_RenderDrawRect(m_renderer, rect); }

void Window::fill_rect(SDL_Rect* rect) { SDL_RenderFillRect(m_renderer, rect); }

SDL_Color& Window::background_color(void) { return m_background_color; }

SDL_Color const& Window::background_color(void) const {
	return m_background_color;
}

int Window::w(void) const { return m_w; }

int Window::h(void) const { return m_h; }

} // namespace fractals

#endif // FRACTALS_WINDOW_H
