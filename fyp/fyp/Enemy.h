#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Enemy
{

	sf::CircleShape m_sprite;

public:
	Enemy();
	~Enemy();
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
};

