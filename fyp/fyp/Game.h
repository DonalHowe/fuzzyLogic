
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>

enum class state {
	low,
	medium,
	high
};

class Game
{
public:
	Game();
	~Game();
	void run();
	Player m_player;
	std::vector<Enemy>  m_Enemy;
	sf::Font m_font;
	sf::Text m_textArray[12];
	state m_checker;
	sf::RectangleShape m_rect;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	double FuzzyGrade(double value, double x0, double x1);
	double FuzzyTriangle(double value, double x0, double x1, double x2);
	double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
	double FuzzyAND(double A, double B);
	double FuzzyOR(double A, double B);
	double FuzzyNOT(double A);
	double Defuzification();
	void reset();
	void initialForcePLacement();
	double enemyCount=25;
	double low;
	double medium;
	double high;
	bool resetFuzzy;
	double range;
	double force;

	void threatLevelSetter();
	void setSizeAndRangeOFEnemies();


	double m_forceSize_tiny;
	double m_forceSize_small;
	double m_forceSize_moderate;
	double m_forceSize_large;

	double m_Range_Close;
	double m_Range_Medium;
	double m_Range_Far;


	sf::RenderWindow m_window; 

	bool m_exitGame; 

};

#endif 


