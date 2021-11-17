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

class Rect: public Sprite {
public:
	enum DrawMode { Draw, Fill };

	Rect(App& app, SDL_Rect rect, SDL_Color color, DrawMode mode);
	~Rect(void) override = default;

	void draw(Window& window) override;

	SDL_Rect& rect(void);
	SDL_Rect const& rect(void) const;
	SDL_Color& color(void);
	SDL_Color const& color(void) const;
	DrawMode& mode(void);
	DrawMode const& mode(void) const;

protected:
	SDL_Rect m_rect;
	SDL_Color m_color;
	DrawMode m_mode;
};

} // namespace fractals

namespace fractals {

Rect::Rect(App& app, SDL_Rect rect, SDL_Color color, DrawMode mode)
	: Sprite(app), m_rect(rect), m_color(color), m_mode(mode) {}

void Rect::draw(Window& window) {
	window.color(m_color);
	switch (m_mode) {
	case Draw:
		break;
	case Fill:
		break;
	}
	window.draw_rect(&m_rect);
}

SDL_Rect& Rect::rect(void) { return m_rect; }
SDL_Rect const& Rect::rect(void) const { return m_rect; }
SDL_Color& Rect::color(void) { return m_color; }
SDL_Color const& Rect::color(void) const { return m_color; }
Rect::DrawMode& Rect::mode(void) { return m_mode; }
Rect::DrawMode const& Rect::mode(void) const { return m_mode; }

} // namespace fractals

#endif // FRACTALS_SPRITES_RECT_H
