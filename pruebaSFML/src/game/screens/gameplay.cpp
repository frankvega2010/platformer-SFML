#include "gameplay.h"

#include "menu.h"


namespace Juego
{	
	sf::CircleShape triangle(100.0f, 3);

	namespace Gameplay_Section
	{
		GameplayScreen::GameplayScreen()
		{
		}

		GameplayScreen::~GameplayScreen()
		{
		}

		void GameplayScreen::init()
		{
			setHasScreenFinished(false);

			triangle.setFillColor(sf::Color::Cyan);
			
			//_hasScreenFinished = false;
		}

		void GameplayScreen::input()
		{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (!(Game::getIsKeyPressed()))
					{
						Game::setButtonOption(buttonGameOver);
						Screens::setHasScreenFinished(true);
						Game::setIsKeyPressed(true);
					}
				}
				else
				{
					Game::setIsKeyPressed(false);
				}
		}

		void GameplayScreen::update()
		{

			input();
		}

		void GameplayScreen::draw()
		{
			_window.draw(triangle);
		}

		void GameplayScreen::deInit()
		{

		}

		bool GameplayScreen::finish()
		{
			return getHasScreenFinished();
		}

		void GameplayScreen::restart()
		{

		}
	}
}