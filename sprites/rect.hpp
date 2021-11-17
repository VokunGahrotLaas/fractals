#ifndef FRACTALS_SPRITES_RECT_H
#define FRACTALS_SPRITES_RECT_H

// SDL2
#include <SDL2/SDL.h>
// fractals
#include "../app.hpp"
#include "../macros.hpp"
#include "../window.hpp"
#include "sprite.hpp"

namespace fractals {

class Rect: virtual public Sprite {
public:
	enum DrawMode { Draw, Fill };

	Rect(App& app, SDL_Rect rect, SDL_Color color, DrawMode mode);
	~Rect(void) override;

	void draw(Window& window) override;

	SDL_Rect& rect(void);
	SDL_Rect const& rect(void) const;
	SDL_Color& rect_color(void);
	SDL_Color const& rect_color(void) const;
	DrawMode& rect_draw_mode(void);
	DrawMode const& rect_draw_mode(void) const;

protected:
	SDL_Rect m_rect;
	SDL_Color m_rect_color;
	DrawMode m_rect_draw_mode;
};

} // namespace fractals

namespace fractals {

Rect::Rect(App& app, SDL_Rect rect, SDL_Color color, DrawMode mode)
	: Sprite(app), m_rect(rect), m_rect_color(color), m_rect_draw_mode(mode) {
	f_debug_func("%zu", id());
}

Rect::~Rect(void) {
	f_debug_func("%zu", id());
}

void Rect::draw(Window& window) {
	window.color(m_rect_color);
	switch (m_rect_draw_mode) {
	case Draw:
		window.draw_rect(&m_rect);
		break;
	case Fill:
		window.fill_rect(&m_rect);
		break;
	}
}

SDL_Rect& Rect::rect(void) { return m_rect; }
SDL_Rect const& Rect::rect(void) const { return m_rect; }
SDL_Color& Rect::rect_color(void) { return m_rect_color; }
SDL_Color const& Rect::rect_color(void) const { return m_rect_color; }
Rect::DrawMode& Rect::rect_draw_mode(void) { return m_rect_draw_mode; }
Rect::DrawMode const& Rect::rect_draw_mode(void) const { return m_rect_draw_mode; }

} // namespace fractals

#endif // FRACTALS_SPRITES_RECT_H
