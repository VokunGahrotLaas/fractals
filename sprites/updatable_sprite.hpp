#ifndef FRACTALS_SPRITES_UPDATABLE_SPRITE_H
#define FRACTALS_SPRITES_UPDATABLE_SPRITE_H

// SDL2
#include <SDL2/SDL.h>
// fractals
#include "../macros.hpp"
#include "../window.hpp"
#include "sprite.hpp"

namespace fractals {

class UpdatableSprite: virtual public Sprite {
public:
	UpdatableSprite(App& app);
	~UpdatableSprite(void) override;

	void draw(Window& window) override = 0;
	virtual void update(void) = 0;
};

} // namespace fractals

namespace fractals {

UpdatableSprite::UpdatableSprite(App& app): Sprite(app) {
	f_debug_func("%zu", id());
	app.updatable_sprites.insert(this);
}

UpdatableSprite::~UpdatableSprite(void) {
	f_debug_func("%zu", id());
	app.updatable_sprites.erase(this);
}

} // namespace fractals

#endif // FRACTALS_SPRITES_UPDATABLE_SPRITE_H

