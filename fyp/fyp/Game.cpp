
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Ai Labs" }, m_exitGame{ false }
{
	initialForcePLacement();
	m_rect.setSize(sf::Vector2f{ 300,400 });
	m_rect.setPosition(0, ScreenSize::M_HEIGHT - m_rect.getSize().y);
	m_rect.setFillColor(sf::Color::Black);
	if (!m_font.loadFromFile("BebasNeue.otf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	int yPosText = 400;
	for (int i = 0; i < 12; i++)
	{
		m_textArray[i].setFont(m_font);
		m_textArray[i].setCharacterSize(25u);
		m_textArray[i].setFillColor(sf::Color::Cyan);
		m_textArray[i].setPosition(10, yPosText);

		yPosText += 30;
	}
	m_textArray[0].setString("press r to reset");
	int i = 0;

}


Game::~Game()
{

}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); 
	while (m_window.isOpen())
	{
		processEvents(); 
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render(); 
	}
}

double Game::Defuzification() {

	double deply;
	deply = (low * 10 + medium * 30 + high * 50) / (low + medium + high);

	m_textArray[11].setString(" defuzz: " + std::to_string(deply));

	return deply;
}


double Game::FuzzyGrade(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

		if (x <= x0)
		{
			result = 0;
		}
			
		else if (x > x1)
		{
			result = 1;
		}
			
		else
		{
			result = ((x - x0) / (x1 - x0));

		}
			
		return result;
}

double Game::FuzzyTriangle(double value, double x0, double x1, double x2)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x2))
	{
		result = 0;
	}
			
	else if (x == x1)
	{
		result = 1;
	}
			
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
			
	else
	{
		result = ((x2 - x) / (x2 - x1));

	}
			
	return result;
}

double Game::FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x3))
	{
		result = 0;
	}
			
	else if ((x >= x1) && (x <= x2))
	{
		result = 1;
	}
			
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
			
	else
	{
		result = ((x3 - x) / (x3 - x2));
	}
			
	return result;
}


double Game::FuzzyAND(double A, double B)
{
	return std::min(A, B);
}

double Game::FuzzyOR(double A, double B)
{
	return std::max(A, B);
}

double Game::FuzzyNOT(double A)
{
	return 1.0 - A;
}

void Game::setSizeAndRangeOFEnemies()
{

	// force tiny to large
	/// tiny 1-5
	/// small 6-12
	/// moderate 10- 15
	/// large 15 -25
	/// 

	m_forceSize_tiny = FuzzyTriangle(enemyCount, 0, 1, 7);
	m_forceSize_small = FuzzyTrapezoid(enemyCount, 6, 8, 10, 12);
	m_forceSize_moderate = FuzzyTrapezoid(enemyCount, 11, 13, 15, 17);
	m_forceSize_large = FuzzyGrade(enemyCount, 16, 19);


	m_textArray[4].setString(" tiny size " + std::to_string(m_forceSize_tiny));
	m_textArray[5].setString(" small size " + std::to_string(m_forceSize_small));
	m_textArray[6].setString(" moderate size " + std::to_string(m_forceSize_moderate));
	m_textArray[7].setString(" large size " + std::to_string(m_forceSize_large));



	// range 

	m_Range_Close = FuzzyTriangle(range, 0, 500,1300 );
	m_Range_Medium = FuzzyTrapezoid(range, 1150, 1350, 1900, 2100);
	m_Range_Far = FuzzyGrade(range, 1950, 2250);

	m_textArray[8].setString(" close " + std::to_string(m_Range_Close));
	m_textArray[9].setString(" medium range " + std::to_string(m_Range_Medium));
	m_textArray[10].setString(" far" + std::to_string(m_Range_Far));
}

void Game::threatLevelSetter()
{

	low = FuzzyOR(FuzzyOR(FuzzyAND(m_Range_Medium, m_forceSize_tiny), FuzzyAND(m_Range_Medium, m_forceSize_small)), FuzzyAND(m_Range_Far, FuzzyNOT(m_forceSize_large)));
	medium = FuzzyOR(FuzzyOR(FuzzyAND(m_Range_Close, m_forceSize_tiny), FuzzyAND(m_Range_Medium, m_forceSize_moderate)), FuzzyAND(m_Range_Far, m_forceSize_large));
	high = FuzzyOR(FuzzyAND(m_Range_Close, FuzzyNOT(m_forceSize_tiny)), FuzzyAND(m_Range_Medium, m_forceSize_large));

	m_textArray[1].setString(" low danger " + std::to_string(low));
	m_textArray[2].setString(" medium danger " + std::to_string(medium));
	m_textArray[3].setString(" high danger " + std::to_string(high));

}


void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::R == t_event.key.code)
	{
		resetFuzzy = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (resetFuzzy == true)
	{
		reset();
	}
	
	for (int i = 0; i < enemyCount; i++)
	{
		if (low > 0)
		{

			m_Enemy.at(i).setColor(sf::Color::Black);	
		

		}
		else if (medium > 0)
		{

			m_Enemy.at(i).setColor(sf::Color::Cyan);
		

		}
		else if (high > 0)
		{

			m_Enemy.at(i).setColor(sf::Color::Magenta);
		
		}
		else {
			m_Enemy.at(i).setColor(sf::Color::Red);
		}
	
	
	}
	
	

}
void Game::reset()
{

	resetFuzzy = false;
	initialForcePLacement();
	setSizeAndRangeOFEnemies();
	threatLevelSetter();
	Defuzification();
}

void Game::initialForcePLacement()
{
	float randomX = rand() % 700 + 350;
	int Y = 100;
	enemyCount = rand() % 25 + 8;

	for (int i = 0; i < enemyCount; i++)
	{
		Y += 15;
		Enemy m_enem;
		m_Enemy.push_back(m_enem);
		m_Enemy.at(i).m_sprite.setPosition(randomX, Y);
	}
	
	
	range = randomX;
}


void Game::render()
{
	m_window.clear(sf::Color::White);
	m_player.render(m_window);
	for (int i = 0; i < enemyCount; i++)
	{
		m_window.draw(m_Enemy.at(i).m_sprite);
	}
	m_window.draw(m_rect);
	for (int i = 0; i < 12; i++)
	{
		m_window.draw(m_textArray[i]);
	}


	m_window.display();
}



