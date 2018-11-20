#include "gameplay.h"

#include "menu.h"


namespace Juego
{	
	//(100,100,300,300,sf::Color::Red)
	Player player1;

	sf::CircleShape triangle(100.0f, 3);
	sf::RectangleShape playerRectangle;

	sf::Font deltaFont;
	sf::Text deltaText;

	namespace Gameplay_Section
	{
		std::string toString(sf::Time value)
		{
			std::ostringstream stream;
			stream.setf(std::ios_base::fixed);
			stream.precision(10);
			stream << value.asSeconds();
			return stream.str();
		}

		GameplayScreen::GameplayScreen()
		{
		}

		GameplayScreen::~GameplayScreen()
		{
		}

		void GameplayScreen::init()
		{
			
			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");

			deltaText.setCharacterSize(30);
			deltaText.setFont(deltaFont);
			deltaText.setPosition(400, 400);


			player1.setPosition(0, 0);
			player1.setSize(200, 200);
			player1.setColor(sf::Color::Red);
			player1.setIsAlive(true);
			player1.setSpeed(800);
			
			playerRectangle.setFillColor(player1.getColor());
			playerRectangle.setPosition(static_cast<sf::Vector2f>(player1.getPosition()));
			playerRectangle.setSize(static_cast<sf::Vector2f>(player1.getSize()));

			setHasScreenFinished(false);

			triangle.setFillColor(sf::Color::Cyan);
			
			//_hasScreenFinished = false;
		}

		void GameplayScreen::input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player1.setMove((player1.getSpeed() * deltaTime.asSeconds()), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				player1.setMove((player1.getSpeed() * deltaTime.asSeconds()*(-1)), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player1.setMove(0, (player1.getSpeed() * deltaTime.asSeconds()));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player1.setMove(0, (player1.getSpeed() * deltaTime.asSeconds()*(-1)));
			}
			else
			{
				player1.setMove(0, 0);
			}

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
			//deltaTime.;
			input();
			playerRectangle.move(player1.getMove());
			deltaText.setString(toString(deltaTime));
			//playerRectangle.move(static_cast<sf::Vector2f>(player1.getPosition()));
		}

		void GameplayScreen::draw()
		{
			_window.draw(deltaText);
			_window.draw(playerRectangle);
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