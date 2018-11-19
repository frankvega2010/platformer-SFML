#include "gameover.h"

namespace Juego
{
//	static const int Menu = 6;
	static const int Restart_Gameplay = 5;

	sf::CircleShape circle(100.0f);

	namespace GameOver_Section
	{
		GameOverScreen::GameOverScreen()
		{
		}

		GameOverScreen::~GameOverScreen()
		{
		}

		void GameOverScreen::init()
		{
			circle.setPosition(0, 0);
			circle.setFillColor(sf::Color::Yellow);
			setHasScreenFinished(false);
			//_hasScreenFinished = false;
		}

		void GameOverScreen::input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!(Game::getIsKeyPressed()))
				{
					Game::setButtonOption(buttonMenu);
					Screens::setHasScreenFinished(true);
					Game::setIsKeyPressed(true);
				}
			}
			else
			{
				Game::setIsKeyPressed(false);
			}
		}

		void GameOverScreen::update()
		{
			input();
		}

		void GameOverScreen::draw()
		{
			_window.draw(circle);
		}

		void GameOverScreen::deInit()
		{

		}

		bool GameOverScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}