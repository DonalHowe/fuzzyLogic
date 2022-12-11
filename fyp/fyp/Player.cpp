#include "Player.h"

Player::~Player()
{
}

Player::Player()
{
	m_sprite.setFillColor(sf::Color::Blue);
	m_sprite.setRadius(5u);
	m_sprite.setPosition(10, 400);
}

void Player::update(sf::Time t_deltatime)
{
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}
