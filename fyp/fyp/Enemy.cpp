#include "Enemy.h"

Enemy::Enemy()
{
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setRadius(5u);
}

Enemy::~Enemy()
{
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}

void Enemy::update(sf::Time t_deltaTime)
{
}
