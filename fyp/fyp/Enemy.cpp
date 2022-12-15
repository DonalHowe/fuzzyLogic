#include "Enemy.h"

Enemy::Enemy()
{
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setRadius(5u);
}

Enemy::~Enemy()
{
}

void Enemy::setTriangleShape()
{
	m_sprite = sf::CircleShape(80, 3);
}

void Enemy::setColor(sf::Color t_color)
{
	m_sprite.setFillColor(t_color);
}


void Enemy::update(sf::Time t_deltaTime)
{
}
