#ifndef FRACTALS_SPRITES_SPRITE_H
#define FRACTALS_SPRITES_SPRITE_H

// stdlib
#include <set>
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

	static std::set<size_t> free_ids;
	static size_t next_id(void);
	static void free_id(size_t id);
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

Sprite::Sprite(App& app): app(app), m_id(next_id()) {
	f_debug_func("%zu", id());
	app.sprites.insert(this);
}

Sprite::~Sprite(void) {
	f_debug_func("%zu", id());
	app.sprites.erase(this);
	free_id(m_id);
}

size_t Sprite::id(void) const { return m_id; }

std::set<size_t> Sprite::free_ids = std::set<size_t>({ 0 });

size_t Sprite::next_id(void) {
	f_debug_func_name();
	for (size_t id: free_ids)
		f_debug("%zu ", id);
	size_t id = *free_ids.begin();
	free_ids.erase(id);
	free_ids.insert(id + 1);
	return id;
}

void Sprite::free_id(size_t id) {
	free_ids.insert(id);
}

} // namespace fractals

#endif // FRACTALS_SPRITES_SPRITE_H
