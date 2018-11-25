#include "gameplay.h"

#include "menu.h"

#include "Thor/Time.hpp"


namespace Game_Namespace
{

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("res/assets/tiles/firingrange.tmx");

	pugi::xml_node object = doc.child("map").child("objectgroup");

	pugi::xml_node_iterator someObjects = object.begin();

	tmx::TileMap map("res/assets/tiles/firingrange.tmx");

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 800.f));

	static bool cameraRight = false;
	static bool cameraLeft = false;
	static bool cameraDown = false;
	static bool cameraUp = false;
	static float cameraLimitUp = 300.f;
	static float cameraLimitDown = 350.f;
	static float cameraLimitLeft = 300.f;
	static float cameraLimitRight = 100.f;

	static int gravitySpeed = 0;

	static bool playerInput = false;
	static bool isJumping = false;
	static bool isOnGround = false;

	//static bool flipRight = false;
	//static bool flipLeft = false;

	//sf::Mouse playerMouse;

	sf::Vector2i MousePosition;

	// convert it to world coordinates
	sf::Vector2f worldPos;

	static int playerLivesTest = 3;
	static bool currentlyTouchingPlayer = false;
	//static bool playerInvincibility = false;

	const sf::Time initialTime = sf::seconds(0.5f);
	thor::CallbackTimer timerJump;

	const sf::Time initialInvincibilityTime = sf::seconds(3.0f);
	thor::CallbackTimer timerInvincibility;


	Player player1;
	Enemy enemyTest;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::CircleShape triangle(100.0f, 3);
	sf::CircleShape crosshairTest;
	sf::RectangleShape playerRectangle;
	sf::RectangleShape enemyRectangle;
	sf::RectangleShape enemyPlayerDetection;

	sf::Font deltaFont;
	sf::Text deltaText;

	sf::Text Lives;

	const int maxColisionsBoxes = 30;

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

		std::string toString(int value)
		{
			std::ostringstream stream;
			stream.setf(std::ios_base::fixed);
			stream.precision(0);
			stream << value;
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
			MousePosition = sf::Mouse::getPosition(_window);

			// convert it to world coordinates
			worldPos = _window.mapPixelToCoords(MousePosition);

			//sf::Mouse::setPosition(sf::Vector2i(Game::getNewScreenWidth(), Game::getNewScreenHeight()), _window);

			playerTexture.loadFromFile("res/assets/textures/playertest.png");
			playerTexture.setSmooth(true);
			playerTexture.setRepeated(false);

			playerSprite.setTexture(playerTexture);
			playerSprite.setPosition(200, 1800);
			//playerSprite.setColor(sf::Color(255, 255, 255, 128));
			

			//map.ShowObjects();

			view.setCenter(200.0f, 1800.f);
			view.zoom(2.0f);

			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");

			deltaText.setCharacterSize(30);
			deltaText.setFont(deltaFont);
			deltaText.setPosition(400, 400);

			Lives.setCharacterSize(80);
			Lives.setFont(deltaFont);
			Lives.setPosition(200, 1400);
			
			
			crosshairTest.setRadius(30);
			crosshairTest.setOutlineThickness(5);
			crosshairTest.setFillColor(sf::Color::Transparent);
			crosshairTest.setOutlineColor(sf::Color::Red);
			crosshairTest.setPosition(static_cast<sf::Vector2f>(worldPos));
			

			gravitySpeed = 800;

			player1.setPosition(200, 1800);
			player1.setSize(100, 180);
			player1.setColor(sf::Color::Red);
			player1.setIsAlive(true);
			player1.setSpeed(500, 1400);

			enemyTest.setPosition(200, 1000);
			enemyTest.setSize(100, 180);
			enemyTest.setColor(sf::Color::Yellow);
			enemyTest.setIsAlive(true);
			enemyTest.setSpeed(500, 1400);
			

			enemyRectangle.setFillColor(enemyTest.getColor());
			enemyRectangle.setPosition(static_cast<sf::Vector2f>(enemyTest.getPosition()));
			enemyRectangle.setSize(static_cast<sf::Vector2f>(enemyTest.getSize()));

			enemyPlayerDetection.setPosition(enemyRectangle.getPosition().x - 200, enemyRectangle.getPosition().y);
			enemyPlayerDetection.setSize(sf::Vector2f(500.0f, 540));
			enemyPlayerDetection.setFillColor({150,0,0,150});

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

		}

		void GameplayScreen::input()
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				cameraLeft = false;
				player1.setMove((player1.getSpeed().x * deltaTime.asSeconds()), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cameraRight = false;
				player1.setMove((player1.getSpeed().x * deltaTime.asSeconds()*(-1)), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				cameraUp = false;
				player1.setMove(0, (player1.getSpeed().y * deltaTime.asSeconds()));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				cameraDown = false;
				player1.setMove(0, (player1.getSpeed().y * deltaTime.asSeconds()*(-1)));
			}
			else
			{
				player1.setMove(0, 0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!(isJumping) && isOnGround)
				{
					isOnGround = false;
					isJumping = true;
					gravitySpeed = 0;
					timerJump.start();
				}
			}
			else
			{
				Game::setIsKeyPressed(false);
			}

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
			}*/
		}

		void CheckCollisionWithTiles(sf::RectangleShape& shape, int i)
		{
			if (shape.getGlobalBounds().intersects(rectangles[i].getGlobalBounds()))
			{
				if (shape.getPosition().x + shape.getGlobalBounds().width > rectangles[i].getPosition().x &&
					shape.getPosition().x + shape.getGlobalBounds().width < rectangles[i].getPosition().x + 10)
				{
					rectangles[i].setFillColor({ 255,0,0 }); // Testing Collision, delete later!
					shape.setPosition(rectangles[i].getPosition().x - (shape.getGlobalBounds().width), shape.getPosition().y);
				}

				if (shape.getPosition().x < rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width &&
					shape.getPosition().x > rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width - 10
					)
				{
					rectangles[i].setFillColor({ 255,0,0 }); // Testing Collision, delete later!
					shape.setPosition(rectangles[i].getPosition().x + (rectangles[i].getGlobalBounds().width), shape.getPosition().y);
				}

				if (shape.getPosition().y < rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height &&
					shape.getPosition().y > rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height - 20)
				{
					rectangles[i].setFillColor({ 255,0,0 }); // Testing Collision, delete later!
					shape.setPosition(shape.getPosition().x, rectangles[i].getPosition().y + (rectangles[i].getGlobalBounds().height));
				}

				if (shape.getPosition().y + shape.getGlobalBounds().height > rectangles[i].getPosition().y &&
					shape.getPosition().y + shape.getGlobalBounds().height < rectangles[i].getPosition().y + 20)
				{
					rectangles[i].setFillColor({ 255,0,0 }); // Testing Collision, delete later!
					isOnGround = true;
					cameraDown = false;
					shape.setPosition(shape.getPosition().x, rectangles[i].getPosition().y - (shape.getGlobalBounds().height));
				}
			}
			else
			{
				rectangles[i].setFillColor({ 255,255,255 }); // Testing Collision, delete later!
			}
		}

		void GameplayScreen::update()
		{
			
			MousePosition = sf::Mouse::getPosition(_window);

			// convert it to world coordinates
			worldPos = _window.mapPixelToCoords(MousePosition);
			//MousePosition = sf::Mouse::getPosition(_window);
			//sf::Mouse::getPosition()
			_window.setView(view);
			input();

			//JUMP
			if (timerInvincibility.isRunning())
			{
				playerRectangle.setFillColor(sf::Color::Green);
			}

			if (timerInvincibility.isExpired())
			{
				timerInvincibility.reset(initialInvincibilityTime);
				playerRectangle.setFillColor(sf::Color::Red);
				if (playerRectangle.getGlobalBounds().intersects(enemyRectangle.getGlobalBounds()))
				{
					currentlyTouchingPlayer = true;
				}
			}

			if (isJumping)
			{
				cameraDown = false;
				playerRectangle.setPosition(playerRectangle.getPosition().x, playerRectangle.getPosition().y + (player1.getSpeed().y * deltaTime.asSeconds()*(-1)));
				//Lives.setPosition(Lives.getPosition().x, Lives.getPosition().y + (player1.getSpeed().y * deltaTime.asSeconds()*(-1)));
				if (timerJump.isExpired())
				{
					isJumping = false;
					gravitySpeed = 800;
				}
			}
			else
			{
				timerJump.reset(initialTime);
			}

			// gravity

			if (player1.getGravity())
			{
				playerRectangle.setPosition(playerRectangle.getPosition().x, (playerRectangle.getPosition().y + (gravitySpeed * deltaTime.asSeconds())));
				cameraUp = false;
			}

			if (enemyTest.getGravity())
			{
				enemyRectangle.setPosition(enemyRectangle.getPosition().x, enemyRectangle.getPosition().y + (enemyTest.getSpeed().y * deltaTime.asSeconds()));
			}

			enemyPlayerDetection.setPosition(enemyRectangle.getPosition().x - 200, enemyRectangle.getPosition().y - 190);
			playerRectangle.move(player1.getMove());
			//playerSprite.scale(-1, 1);

			playerSprite.setPosition(playerRectangle.getPosition());
			//playerSprite.setPosition(playerRectangle.getPosition());
			deltaText.setString(toString(deltaTime));
			Lives.setString("Player Lives:" + toString(playerLivesTest));

			crosshairTest.setPosition(worldPos.x - 30,worldPos.y - 30);
			
			Lives.move(player1.getMove());		
			
			//Lives.setPosition(playerRectangle.getPosition().x,playerRectangle.getPosition().y - Lives.getPosition().y);

			if (crosshairTest.getPosition().x < playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2)
			{
				/*playerSprite.setOrigin({ playerSprite.getGlobalBounds().width / 2.45f, 0 });
				playerSprite.scale(-1, 1);*/
				/*playerSprite.setOrigin({ playerSprite.getLocalBounds().width, 0 });
				playerSprite.scale(-1, 1);*/
				//playerSprite.setTextureRect(sf::IntRect(0, playerSprite.getGlobalBounds().height, playerSprite.getGlobalBounds().width , - playerSprite.getGlobalBounds().height));
					//playerSprite.get
			}
			else if (crosshairTest.getPosition().x > playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2)
			{
				/*playerSprite.setOrigin({ playerSprite.getGlobalBounds().width / 2.45f, 0 });
				playerSprite.scale(-1, 1);*/
				//playerSprite.setOrigin({ 0, 0 });
				//playerSprite.scale(1, 1);
				//setTextureRect(sf::IntRect(0, playerSprite.getGlobalBounds().height, playerSprite.getGlobalBounds().width , playerSprite.getGlobalBounds().height));
				//playerSprite.scale(1, 1);
			}

			if (playerRectangle.getPosition().x > view.getCenter().x + cameraLimitRight)
			{
				if (!(cameraRight))
				{
					cameraRight = true;
					cameraLeft = false;
				}
			}
			else if (playerRectangle.getPosition().x < view.getCenter().x - cameraLimitLeft)
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
			else if (playerRectangle.getPosition().y < view.getCenter().y - cameraLimitUp)
			{
				if (!(cameraUp))
				{
					cameraUp = true;
					cameraDown = false;
				}
			}

			if (cameraDown) view.setCenter(view.getCenter().x, playerRectangle.getPosition().y - cameraLimitDown);
			if (cameraUp)
			{
				view.setCenter(view.getCenter().x, playerRectangle.getPosition().y + cameraLimitUp);
				Lives.move(0, (player1.getSpeed().y * deltaTime.asSeconds()*(-1)));
			}

			if (cameraRight) view.setCenter(playerRectangle.getPosition().x - cameraLimitRight, view.getCenter().y);
			if (cameraLeft) view.setCenter(playerRectangle.getPosition().x + cameraLimitLeft, view.getCenter().y);

			// Checks for collisions

			for (int i = 0; i < maxColisionsBoxes; i++)
			{
					CheckCollisionWithTiles(playerRectangle,i);
					CheckCollisionWithTiles(enemyRectangle, i);
			}

			if (playerRectangle.getGlobalBounds().intersects(enemyPlayerDetection.getGlobalBounds()))
			{
				if (playerRectangle.getPosition().x > enemyPlayerDetection.getPosition().x + enemyPlayerDetection.getGlobalBounds().width / 2)
				{
					enemyRectangle.move(300 * deltaTime.asSeconds(), 0);
				}
				else if (playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width < enemyPlayerDetection.getPosition().x + enemyPlayerDetection.getGlobalBounds().width / 2)
				{
					enemyRectangle.move(-300 * deltaTime.asSeconds(), 0);
				}
			}
			else
			{
				enemyRectangle.move(0, 0);
			}

			if (playerRectangle.getGlobalBounds().intersects(enemyRectangle.getGlobalBounds()))
			{
				enemyRectangle.setFillColor(sf::Color::Cyan);
				if (currentlyTouchingPlayer)
				{
					if (!(timerInvincibility.isRunning()))
					{
						timerInvincibility.start();
						playerLivesTest--;
					}
					//playerInvincibility = true;
					
				}
				currentlyTouchingPlayer = false;
			}
			else
			{
				enemyRectangle.setFillColor(sf::Color::Yellow);
				currentlyTouchingPlayer = true;
			}
		}

		void GameplayScreen::draw()
		{
			// Draw Tilemap with its collision objects
			for (int i = 0; i < maxColisionsBoxes; i++)
			{
				_window.draw(rectangles[i]);
			}
			_window.draw(map);

			// Draw everything else
			_window.draw(deltaText);
			_window.draw(playerRectangle);
			_window.draw(playerSprite);
			_window.draw(enemyRectangle);
			_window.draw(Lives);
			_window.draw(enemyPlayerDetection);
			_window.draw(crosshairTest);
		}

		void GameplayScreen::deInit()
		{
			_window.setView(_window.getDefaultView());
			view.zoom(0.5f);
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