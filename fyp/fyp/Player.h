#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Player
{
	sf::CircleShape m_sprite;


public:

	~Player();
	Player();
	void update(sf::Time t_deltatime);
	void render(sf::RenderWindow& t_window);
};

