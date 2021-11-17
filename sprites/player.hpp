#ifndef FRACTALS_SPRITES_PLAYER_H
#define FRACTALS_SPRITES_PLAYER_H

#include "rect.hpp"
#include "updatable_sprite.hpp"

namespace fractals {

class Player: virtual public UpdatableSprite, virtual public Rect {
public:
	Player(App& app, SDL_Rect rect, SDL_Color color);
	~Player(void) override;

	void draw(Window& window) override;
	void update(void) override;
};

} // namespace fractals

namespace fractals {

Player::Player(App& app, SDL_Rect rect, SDL_Color color)
	: Sprite(app), UpdatableSprite(app), Rect(app, rect, color, Rect::Fill) {
	f_debug_func("%zu", id());
}

Player::~Player(void) { f_debug_func("%zu", id()); }

void Player::draw(Window& window) { Rect::draw(window); }

void Player::update(void) {
	m_rect.x += (int)app.keyboard.is_key_pressed(SDLK_RIGHT)
				- (int)app.keyboard.is_key_pressed(SDLK_LEFT);
	m_rect.y += (int)app.keyboard.is_key_pressed(SDLK_DOWN)
				- (int)app.keyboard.is_key_pressed(SDLK_UP);
}

} // namespace fractals

#endif // FRACTALS_SPRITES_PLAYER_H
