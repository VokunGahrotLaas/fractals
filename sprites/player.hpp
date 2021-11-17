#ifndef FRACTALS_SPRITES_PLAYER_H
#define FRACTALS_SPRITES_PLAYER_H

#include "rect.hpp"
#include "updatable_sprite.hpp"

namespace fractals {

class Player: public UpdatableSprite {
public:
	Player(App& app, SDL_Rect rect, SDL_Color color);
	~Player(void) override;

	void draw(Window& window) override;
	void update(void) override;

protected:
	Rect rect;
};

} // namespace fractals

namespace fractals {

Player::Player(App& app, SDL_Rect rect, SDL_Color color)
	: UpdatableSprite(app), rect(app, rect, color, Rect::Fill) {
	f_debug_func("%zu", id());
}

Player::~Player(void) {
	f_debug_func("%zu", id());
}

void Player::draw(Window& window) { rect.draw(window); }

void Player::update(void) {
	rect.rect().x += (int)app.keyboard.is_key_pressed(SDLK_RIGHT)
					 - (int)app.keyboard.is_key_pressed(SDLK_LEFT);
	rect.rect().y += (int)app.keyboard.is_key_pressed(SDLK_DOWN)
					 - (int)app.keyboard.is_key_pressed(SDLK_UP);
}

} // namespace fractals

#endif // FRACTALS_SPRITES_PLAYER_H
