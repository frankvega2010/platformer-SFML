#include "gameplay.h"

#include "menu.h"


namespace Juego
{	

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("res/assets/tiles/testlevel.tmx");

	pugi::xml_node object = doc.child("map").child("objectgroup");

	pugi::xml_node_iterator someObjects = object.begin();

	tmx::TileMap map("res/assets/tiles/testlevel.tmx");

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 800.f));

	static bool cameraRight = false; // der unbool
	static bool cameraLeft = false; // izq otrobool
	static bool cameraDown = false; // abajo unbooly
	static bool cameraUp = false; // arriba cameraUp

	Player player1;

	sf::CircleShape triangle(100.0f, 3);
	sf::RectangleShape playerRectangle;

	sf::Font deltaFont;
	sf::Text deltaText;

	const int maxColisionsBoxes = 4;

	sf::RectangleShape rectangles[maxColisionsBoxes];

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
			
			
			map.ShowObjects();

			view.setCenter(0.0f, 0.f);
			//view.zoom(2.0f);

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

			int i = 0;
			for (pugi::xml_node_iterator it = object.begin(); it != object.end(); ++it)
			{
				rectangles[i].setPosition(sf::Vector2f(it->attribute("x").as_int(),
					it->attribute("y").as_int()));

				rectangles[i].setSize(sf::Vector2f(it->attribute("width").as_int(),
					it->attribute("height").as_int()));

				rectangles[i].setFillColor(sf::Color::Green);
				i++;
			}
			i = 0;

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
			_window.setView(view);
			input();
			playerRectangle.move(player1.getMove());
			deltaText.setString(toString(deltaTime));

			if (playerRectangle.getPosition().x > view.getCenter().x + 300)
			{
				if (!(cameraRight))
				{
					cameraRight = true;
					cameraLeft = false;
				}
			}
			else if (playerRectangle.getPosition().x < view.getCenter().x - 300)
			{
				if (!(cameraLeft))
				{
					cameraLeft = true;
					cameraRight = false;
				}
			}

			if (playerRectangle.getPosition().y > view.getCenter().y + 300)
			{
				if (!(cameraDown))
				{
					cameraDown = true;
					cameraUp = false;
				}
			}
			else if (playerRectangle.getPosition().y < view.getCenter().y - 300)
			{
				if (!(cameraUp))
				{
					cameraUp = true;
					cameraDown = false;
				}
			}



			if (cameraDown) view.setCenter(view.getCenter().x, playerRectangle.getPosition().y - 300); //triangle.getPosition().y - 300
			if (cameraUp) view.setCenter(view.getCenter().x, playerRectangle.getPosition().y + 300); ////triangle.getPosition().y + 300

			if (cameraRight) view.setCenter(playerRectangle.getPosition().x - 300, view.getCenter().y);
			if (cameraLeft) view.setCenter(playerRectangle.getPosition().x + 300, view.getCenter().y);
		}

		void GameplayScreen::draw()
		{
			for (int i = 0; i < maxColisionsBoxes; i++)
			{
				_window.draw(rectangles[i]);
			}
			_window.draw(deltaText);
			_window.draw(playerRectangle);
			_window.draw(map);
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