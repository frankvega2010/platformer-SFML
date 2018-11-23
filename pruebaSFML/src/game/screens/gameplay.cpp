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
	static float cameraLimitUp = 300.f;
	static float cameraLimitDown = 100.f;
	static float cameraLimitLeft = 300.f;
	static float cameraLimitRight = 100.f;

	static int gravitySpeed = 0;

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
			//_window.setView(view);
			map.ShowObjects();

			view.setCenter(0.0f, 0.f);
			//view.zoom(2.0f);

			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");

			deltaText.setCharacterSize(30);
			deltaText.setFont(deltaFont);
			deltaText.setPosition(400, 400);

			gravitySpeed = 500;

			//playerRectangle.getGlobalBounds().

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
				if (player1.getCanMoveRight())
				{
					player1.setDirection(Right);
					cameraLeft = false;
					player1.setMove((player1.getSpeed() * deltaTime.asSeconds()), 0);
					player1.setCanMoveUp(true);
					player1.setCanMoveDown(true);
					player1.setCanMoveLeft(true);
					player1.setCanMoveRight(true);
				}
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (player1.getCanMoveLeft())
				{
					player1.setDirection(Left);
					cameraRight = false;
					player1.setMove((player1.getSpeed() * deltaTime.asSeconds()*(-1)), 0);
					player1.setCanMoveUp(true);
					player1.setCanMoveDown(true);
					player1.setCanMoveLeft(true);
					player1.setCanMoveRight(true);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (player1.getCanMoveDown())
				{
					player1.setDirection(Down);
					cameraUp = false;
					player1.setMove(0, (player1.getSpeed() * deltaTime.asSeconds()));
					player1.setCanMoveUp(true);
					player1.setCanMoveDown(true);
					player1.setCanMoveLeft(true);
					player1.setCanMoveRight(true);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (player1.getCanMoveUp())
				{
					player1.setDirection(Up);
					cameraDown = false;
					player1.setMove(0, (player1.getSpeed() * deltaTime.asSeconds()*(-1)));
					player1.setCanMoveUp(true);
					player1.setCanMoveDown(true);
					player1.setCanMoveLeft(true);
					player1.setCanMoveRight(true);
				}
			}
			else
			{
				player1.setMove(0, 0);
				//player1.setDirection(0);
				
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

			// gravity

			//if (player1.getGravity())
			//{
			//	//playerRectangle.setPosition(playerRectangle.getPosition().x,(gravitySpeed * deltaTime.asSeconds()));
			//	playerRectangle.setPosition(playerRectangle.getPosition().x, (playerRectangle.getPosition().y + (gravitySpeed * deltaTime.asSeconds())));
			//	player1.setDirection(Down);
			//	cameraUp = false;
			//	player1.setCanMoveUp(true);
			//	player1.setCanMoveDown(true);
			//	player1.setCanMoveLeft(true);
			//	player1.setCanMoveRight(true);
			//}

			playerRectangle.move(player1.getMove());
			deltaText.setString(toString(deltaTime));

			if (playerRectangle.getPosition().x > view.getCenter().x + cameraLimitRight)
			{
				if (!(cameraRight))
				{
					cameraRight = true;
					cameraLeft = false;
				}
			}
			else if (playerRectangle.getPosition().x< view.getCenter().x - cameraLimitLeft)
			{
				if (!(cameraLeft))
				{
					cameraLeft = true;
					cameraRight = false;
				}
			}

			if (playerRectangle.getPosition().y > view.getCenter().y + cameraLimitDown)
			{
				if (!(cameraDown))
				{
					cameraDown = true;
					cameraUp = false;
				}
			}
			else if (playerRectangle.getPosition().y < view.getCenter().y-cameraLimitUp)
			{
				if (!(cameraUp))
				{
					cameraUp = true;
					cameraDown = false;
				}
			}

			if (cameraDown) view.setCenter(view.getCenter().x, playerRectangle.getPosition().y - cameraLimitDown); //triangle.getPosition().y - 300
			if (cameraUp) view.setCenter(view.getCenter().x, playerRectangle.getPosition().y + cameraLimitUp); ////triangle.getPosition().y + 300

			if (cameraRight) view.setCenter(playerRectangle.getPosition().x - cameraLimitRight, view.getCenter().y);
			if (cameraLeft) view.setCenter(playerRectangle.getPosition().x + cameraLimitLeft, view.getCenter().y);

			for (int i = 0; i < maxColisionsBoxes; i++)
			{
				
				/*if (playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width < rectangles[i].getPosition().x || playerRectangle.getPosition().x > rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width)
				{
					gravitySpeed = 500;
				}*/

				if (playerRectangle.getGlobalBounds().intersects(rectangles[i].getGlobalBounds()))
				{	
					

					if (player1.getDirection() == Right)
					{
						player1.setCanMoveRight(false);
						playerRectangle.setPosition(rectangles[i].getPosition().x - (playerRectangle.getLocalBounds().width), playerRectangle.getPosition().y);
					}

					if (player1.getDirection() == Left)
					{
						player1.setCanMoveLeft(false);
						playerRectangle.setPosition(rectangles[i].getPosition().x + (rectangles[i].getLocalBounds().width), playerRectangle.getPosition().y);
					}

					if (player1.getDirection() == Up)
					{
						player1.setCanMoveUp(false);
						playerRectangle.setPosition(playerRectangle.getPosition().x, rectangles[i].getPosition().y + (rectangles[i].getLocalBounds().height));
					}

					if (player1.getDirection() == Down)
					{
						gravitySpeed = 0;
						player1.setCanMoveDown(false);
						playerRectangle.setPosition(playerRectangle.getPosition().x, rectangles[i].getPosition().y - (playerRectangle.getLocalBounds().height));
					}

					map.GetLayer("plataforma").SetColor({ 255,0,0 });
				}
				else
				{
					map.GetLayer("plataforma").SetColor({ 255,255,255 });
					//gravitySpeed = 500;
				}
			}
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
			_window.setView(_window.getDefaultView());
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