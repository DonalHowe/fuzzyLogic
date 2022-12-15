#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Enemy
{



public:
	Enemy();
	~Enemy();
	void setColor(sf::Color t_color);
	void update(sf::Time t_deltaTime);
	sf::CircleShape m_sprite;
};

