#ifndef FRACTALS_SPRITES_SPRITE_H
#define FRACTALS_SPRITES_SPRITE_H

// SDL2
#include <SDL2/SDL.h>
// fractals
#include "../app_declatation.hpp"
#include "../macros.hpp"
#include "../window.hpp"

namespace fractals {

class Sprite {
public:
	Sprite(App& app);
	virtual ~Sprite(void);

	size_t id(void) const;

	virtual void draw(Window& window) = 0;

protected:
	App& app;

private:
	size_t m_id;
	static size_t next_id;
};

} // namespace fractals

namespace std {

template <> class hash<fractals::Sprite> {
	std::size_t operator()(fractals::Sprite const& s) const noexcept {
		return s.id();
	}
};

template <> class equal_to<fractals::Sprite> {
	bool operator()(fractals::Sprite const& a,
					fractals::Sprite const& b) const noexcept {
		return a.id() == b.id();
	}
};

} // namespace std

#include "../app.hpp"

namespace fractals {

size_t Sprite::next_id = 0;

Sprite::Sprite(App& app): app(app), m_id(next_id++) {
	app.sprites.insert(this);
}

Sprite::~Sprite(void) { app.sprites.erase(this); }

size_t Sprite::id(void) const { return m_id; }

} // namespace fractals

#endif // FRACTALS_SPRITES_SPRITE_H
