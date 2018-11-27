#include "gameplay.h"

#include "menu.h"

namespace Game_Namespace
{
	////------------ Tilemap Settings
	static pugi::xml_document doc;

	static pugi::xml_parse_result result = doc.load_file("res/assets/tiles/firerange.tmx");

	static pugi::xml_node object = doc.child("map").child("objectgroup");

	static pugi::xml_node_iterator someObjects = object.begin();

	static tmx::TileMap map("res/assets/tiles/firerange.tmx");

	const int maxColisionsBoxes = 30;

	static sf::RectangleShape rectangles[maxColisionsBoxes];
	////---------------------------------------------------------

	// Camera Settings

	static sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 800.f));

	static bool cameraRight = false;
	static bool cameraLeft = false;
	static bool cameraDown = false;
	static bool cameraUp = false;
	static float cameraLimitUp = 300.f;
	static float cameraLimitDown = 350.f;
	static float cameraLimitLeft = 300.f;
	static float cameraLimitRight = 100.f;


	// Gravity

	static int gravitySpeed = 0;

	// Mouse Position

	static sf::Vector2i MousePosition;
	static sf::Vector2f worldPos;

	//Timers
	
	static const sf::Time initialJumpTime = sf::seconds(0.5f);
	static thor::CallbackTimer timerJump;

	static const sf::Time initialInvincibilityTime = sf::seconds(3.0f);
	static thor::CallbackTimer timerInvincibility;

	static const sf::Time pistolFireRate = sf::seconds(0.5f);
	static thor::CallbackTimer timerPistolFireRate;

	//Textures & Animations
	static sf::Texture playerTexture;
	static sf::Texture playerHands;
	static SpriteAnimation animation;
	static SpriteAnimation pistolAnimation;

	// Audio

	static sf::SoundBuffer pistolshoot;
	static sf::Sound pistolGunShoot;

	// Gun Rotation Variable

	static sf::Vector2f v1;
	static sf::Vector2f v2;
	static float prodVect;
	static float modv1;
	static float modv2;
	static float angle=180;

	// Text
	static sf::Font deltaFont;

	static sf::Text deltaText;
	static sf::Text Lives;

	// Characters

	static Character player1;
	static Character enemyTest;

	// Shapes

	static sf::CircleShape crosshairTest;
	static sf::RectangleShape playerRectangle;
	static sf::RectangleShape enemyRectangle;
	static sf::RectangleShape enemyPlayerDetection;
	static sf::RectangleShape gun;
	static sf::CircleShape gunLimit;

	namespace Gameplay_Section
	{
		static std::string toString(sf::Time value)
		{
			std::ostringstream stream;
			stream.setf(std::ios_base::fixed);
			stream.precision(10);
			stream << value.asSeconds();
			return stream.str();
		}

		static std::string toString(int value)
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
			//// Window & Screen Settings
			setHasScreenFinished(false);

			MousePosition = sf::Mouse::getPosition(_window);
			worldPos = _window.mapPixelToCoords(MousePosition);

			view.setCenter(200.0f, 1800.f);
			view.zoom(2.0f);

			//map.ShowObjects();

			//// World Entities

			//Tilemap

			int i = 0;
			for (pugi::xml_node_iterator it = object.begin(); it != object.end(); ++it)
			{
				rectangles[i].setPosition(sf::Vector2f(it->attribute("x").as_int(),
					it->attribute("y").as_int()));

				rectangles[i].setSize(sf::Vector2f(it->attribute("width").as_int(),
					it->attribute("height").as_int()));

				rectangles[i].setFillColor(sf::Color::Transparent);
				i++;
			}
			i = 0;

			// Player 1
			playerTexture.loadFromFile("res/assets/textures/test10.png");
			playerTexture.setSmooth(true);
			playerTexture.setRepeated(false);

			//playerHands.loadFromFile("res/assets/textures/hands.png");
			playerHands.loadFromFile("res/assets/textures/pistol.png");
			playerHands.setSmooth(true);
			playerHands.setRepeated(false);

			player1.setIsPlayer(true);
			player1.setPosition(200, 1800);
			player1.setSize(100, 150);
			player1.setColor(sf::Color::Red);
			player1.setIsAlive(true);
			player1.setSpeed(500, 1400);
			player1.setHp(100);

			playerRectangle.setFillColor(player1.getColor());
			playerRectangle.setPosition(static_cast<sf::Vector2f>(player1.getPosition()));
			playerRectangle.setSize(static_cast<sf::Vector2f>(player1.getSize()));

			playerRectangle.setTexture(&playerTexture);
			animation.SetAnimation(&playerTexture, sf::Vector2u(8, 6), 0.1f);

			// Player Gun

			gunLimit.setRadius(140);
			gunLimit.setOutlineThickness(10);
			gunLimit.setFillColor(sf::Color::Transparent);
			gunLimit.setOutlineColor(sf::Color::Blue);
			gunLimit.setPosition({ playerRectangle.getPosition().x - playerRectangle.getGlobalBounds().width / 2, playerRectangle.getPosition().y - playerRectangle.getGlobalBounds().height / 2 });

			gun.setFillColor(sf::Color::White);
			gun.setPosition(gunLimit.getPosition().x, gunLimit.getPosition().y - 80);
			gun.setSize({ 140,90 }); // 100 60
			gun.setTexture(&playerHands);
			pistolAnimation.SetAnimationY(&playerHands, sf::Vector2u(1, 9), 0.05f);

			// Enemy 1

			enemyTest.setPosition(200, 1000);
			enemyTest.setSize(100, 180);
			enemyTest.setColor(sf::Color::Yellow);
			enemyTest.setIsAlive(true);
			enemyTest.setSpeed(500, 1400);
			enemyTest.setHp(100);
			enemyTest.setCurrentlyTouchingPlayer(true);

			enemyRectangle.setFillColor(enemyTest.getColor());
			enemyRectangle.setPosition(static_cast<sf::Vector2f>(enemyTest.getPosition()));
			enemyRectangle.setSize(static_cast<sf::Vector2f>(enemyTest.getSize()));

			enemyPlayerDetection.setPosition(enemyRectangle.getPosition().x - 200, enemyRectangle.getPosition().y);
			enemyPlayerDetection.setSize(sf::Vector2f(1800.0f, 540));
			enemyPlayerDetection.setFillColor({ 150,0,0,150 });
			//enemyPlayerDetection.setFillColor(sf::Color::Transparent);
			 
			//// Text

			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");

			deltaText.setCharacterSize(30);
			deltaText.setFont(deltaFont);
			deltaText.setPosition(400, 400);

			//// HUD

			Lives.setCharacterSize(80);
			Lives.setFont(deltaFont);
			Lives.setPosition(200, 1400);

			crosshairTest.setRadius(30);
			crosshairTest.setOutlineThickness(5);
			crosshairTest.setFillColor(sf::Color::Transparent);
			crosshairTest.setOutlineColor(sf::Color::Red);
			crosshairTest.setPosition(static_cast<sf::Vector2f>(worldPos));

			//// Game Mechanics
			gravitySpeed = 800;

			//// Audio

			pistolshoot.loadFromFile("res/assets/sounds/pistolshoot.wav");
			pistolGunShoot.setBuffer(pistolshoot);
			pistolGunShoot.setVolume(globalSoundVolume);
			
		}

		void GameplayScreen::input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				cameraLeft = false;
				player1.setMove((player1.getSpeed().x * deltaTime.asSeconds()), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				cameraRight = false;
				player1.setMove((player1.getSpeed().x * deltaTime.asSeconds()*(-1)), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				cameraUp = false;
				player1.setMove(0, (player1.getSpeed().y * deltaTime.asSeconds()));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
				if (!(player1.getIsJumping()) && player1.getIsOnGround())
				{
					player1.setIsOnGround(false);
					//isOnGround = false;
					player1.setIsJumping(true);
					gravitySpeed = 0;
					player1.StartTimerJump();
				}			
			}
			else
			{
				Game::setIsKeyPressed(false);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
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

		//------- Gameplay Functions

		static void CheckCollisionWithTiles(sf::RectangleShape& shape, int i,Character Character)
		{
			if (shape.getGlobalBounds().intersects(rectangles[i].getGlobalBounds()))
			{
				if (shape.getPosition().x + shape.getGlobalBounds().width > rectangles[i].getPosition().x &&
					shape.getPosition().x + shape.getGlobalBounds().width < rectangles[i].getPosition().x + 10)
				{
					shape.setPosition(rectangles[i].getPosition().x - (shape.getGlobalBounds().width), shape.getPosition().y);
				}

				if (shape.getPosition().x < rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width &&
					shape.getPosition().x > rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width - 10
					)
				{
					shape.setPosition(rectangles[i].getPosition().x + (rectangles[i].getGlobalBounds().width), shape.getPosition().y);
				}

				if (shape.getPosition().y < rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height &&
					shape.getPosition().y > rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height - 20)
				{
					shape.setPosition(shape.getPosition().x, rectangles[i].getPosition().y + (rectangles[i].getGlobalBounds().height));
				}

				if (shape.getPosition().y + shape.getGlobalBounds().height > rectangles[i].getPosition().y &&
					shape.getPosition().y + shape.getGlobalBounds().height < rectangles[i].getPosition().y + 20)
				{
					if (Character.getIsPlayer()) player1.setIsOnGround(true); //isOnGround = true;
					cameraDown = false;
					shape.setPosition(shape.getPosition().x, rectangles[i].getPosition().y - (shape.getGlobalBounds().height));
				}
			}
			else
			{
				// blank
			}
		}

		static void GunRotation()
		{
			gunLimit.setPosition({ playerRectangle.getPosition().x - 70,playerRectangle.getPosition().y - 70 });
			gun.setPosition({ playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2 ,playerRectangle.getPosition().y + playerRectangle.getGlobalBounds().height / 2 - 30 });
			//if(player1.getFlipRight()) gun.setPosition({ playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2 + 10,playerRectangle.getPosition().y + playerRectangle.getGlobalBounds().height / 2 - 30 });
			
			//if (player1.getFlipLeft()) gun.setPosition({ playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2 - 30,playerRectangle.getPosition().y + playerRectangle.getGlobalBounds().height / 2 - 30 });

			v1.x = 0;
			v1.y = 0.0f - gun.getPosition().y;

			v2.x = worldPos.x - gun.getPosition().x;
			v2.y = worldPos.y - gun.getPosition().y;

			prodVect = v1.x*v2.x + v1.y*v2.y;
			modv1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
			modv2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));

			angle = acos(prodVect / (modv1*modv2));
			angle *= (180 / 3.1415f);
			angle = angle + 270;
			if (worldPos.x < gun.getPosition().x)
			{
				angle = 180 - angle;
			}

			gun.setRotation(angle);
		}

		static void PlayerEnemyCollision(Character& enemy, sf::RectangleShape& enemyRectangle,thor::CallbackTimer& timer)
		{
			if (playerRectangle.getGlobalBounds().intersects(enemyRectangle.getGlobalBounds()))
			{
				enemyRectangle.setFillColor(sf::Color::Cyan);
				if (enemy.getCurrentlyTouchingPlayer())
				{
					if (!(timer.isRunning()))
					{
						timer.start();
						player1.setHp(player1.getHp() - 25);
					}
				}
				enemy.setCurrentlyTouchingPlayer(false);
			}
			else
			{
				enemyRectangle.setFillColor(sf::Color::Yellow);
				enemy.setCurrentlyTouchingPlayer(true);
			}
		}

		static void isCrosshairOnTarget(Character& enemy,sf::RectangleShape& enemyRectangle)
		{
			if (crosshairTest.getGlobalBounds().intersects(enemyRectangle.getGlobalBounds()))
			{
				
				player1.setCanShoot(true);
				if (player1.getCanShoot())
				{
					crosshairTest.setOutlineColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						
						if (!timerPistolFireRate.isRunning())
						{
							pistolGunShoot.play();
							timerPistolFireRate.start();
							enemy.setHp(enemyTest.getHp() - 25);
							enemyRectangle.setPosition(enemyRectangle.getPosition().x - 30, enemyRectangle.getPosition().y);
						}
					}
					else
					{
						
					}
				}
			}
			else
			{
				crosshairTest.setOutlineColor(sf::Color::Red);
				player1.setCanShoot(false);
			}
		}

		static void CanEnemyHearPlayer(sf::RectangleShape& enemyRectangleDetection, sf::RectangleShape& enemyRectangle)
		{
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

				isCrosshairOnTarget(enemyTest, enemyRectangle);
			}
			else
			{
				enemyRectangle.move(0, 0);
				crosshairTest.setOutlineColor(sf::Color::Red);
			}
		}


		static void CheckEnemyHP(Character& enemy,sf::RectangleShape& PlayerDetection , sf::RectangleShape& enemyRectangle)
		{
			if (enemy.getHp() <= 0)
			{
				enemy.setIsAlive(false);
			}

			if (enemy.getIsAlive())
			{
				enemyRectangle.setSize(enemyRectangle.getSize());
				PlayerDetection.setSize(enemyPlayerDetection.getSize());
			}
			else
			{
				enemyRectangle.setSize(sf::Vector2f(0, 0));
				PlayerDetection.setSize(sf::Vector2f(0, 0));
			}
		}

		static void CheckCameraMovement()
		{
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
			}

			if (cameraRight) view.setCenter(playerRectangle.getPosition().x - cameraLimitRight, view.getCenter().y);
			if (cameraLeft) view.setCenter(playerRectangle.getPosition().x + cameraLimitLeft, view.getCenter().y);
		}

		static void CheckPlayerFlipSprite()
		{
			if (crosshairTest.getPosition().x < playerRectangle.getPosition().x + playerRectangle.getGlobalBounds().width / 2)
			{
				if (player1.getFlipLeft())
				{
					playerRectangle.setOrigin({ playerRectangle.getGlobalBounds().width, 0 });
					playerRectangle.scale(-1, 1);
					gun.setOrigin({ -20,40 }); // -20 0
					gun.scale(1, -1);
				}
				player1.setFlipLeft(false);
				player1.setFlipRight(true);
			}
			else
			{

				if (player1.getFlipRight())
				{
					playerRectangle.setOrigin({ 0, 0 });
					playerRectangle.scale(-1, 1);
					gun.setOrigin({ -20, 40 });
					gun.scale(1, -1);
				}
				player1.setFlipRight(false);
				player1.setFlipLeft(true);
			}
		}

		static void HUDUpdate()
		{
			deltaText.setString(toString(deltaTime));

			Lives.setString("Player HP: " + toString(player1.getHp()));
			//Lives.setString("Enemy HP: " + toString(enemyTest.getHp()));
			Lives.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - 800));

			crosshairTest.setPosition(worldPos.x - 30, worldPos.y - 30);
		}

		static void CheckPlayerGravity()
		{
			if (player1.getGravity())
			{
				playerRectangle.setPosition(playerRectangle.getPosition().x, (playerRectangle.getPosition().y + (gravitySpeed * deltaTime.asSeconds())));
				cameraUp = false;
			}
		}

		static void CheckEnemyGravity(Character& enemy,sf::RectangleShape& enemyRectangle)
		{
			if (enemy.getGravity())
			{
				enemyRectangle.setPosition(enemyRectangle.getPosition().x, enemyRectangle.getPosition().y + (enemyTest.getSpeed().y * deltaTime.asSeconds()));
			}
		}

		static void CheckCharacterJump(Character& character,sf::RectangleShape& characterRectangle)
		{
			if (character.getIsJumping())
			{
				if (character.isTimerJumpRunning())
				{
					cameraDown = false;
					characterRectangle.setPosition(characterRectangle.getPosition().x, characterRectangle.getPosition().y + (character.getSpeed().y * deltaTime.asSeconds()*(-1)));
				}

				if (character.isTimerJumpExpired())
				{
					character.setIsJumping(false);
					gravitySpeed = 800;
				}
			}
			else
			{
				character.setResetTimerJump(initialJumpTime);
			}
		}

		//WIP Function
		static void CheckWeaponsFireRate(thor::CallbackTimer& weaponFireRate)
		{
			if (weaponFireRate.isExpired())
			{
				pistolAnimation.SetSingleFrame(sf::Vector2u(0, 0));
				weaponFireRate.reset(pistolFireRate);
			}
			else if (weaponFireRate.isRunning())
			{
				pistolAnimation.UpdateY(0, deltaTime.asSeconds());
			}
		}

		//WIP Function
		static void CheckInvincibilityFrames(thor::CallbackTimer& timer)
		{
			if (timer.isRunning())
			{
				playerRectangle.setFillColor(sf::Color::Green);
			}

			if (timer.isExpired())
			{
				timer.reset(initialInvincibilityTime);
				playerRectangle.setFillColor(sf::Color::White);
				if (playerRectangle.getGlobalBounds().intersects(enemyRectangle.getGlobalBounds()))
				{
					enemyTest.setCurrentlyTouchingPlayer(true);
				}
			}
		}

		//-------END Gameplay Functions

		void GameplayScreen::update()
		{
			////// Display			
			HUDUpdate();
			CheckCameraMovement();

			//////Player Inputs
			
			MousePosition = sf::Mouse::getPosition(_window);
			worldPos = _window.mapPixelToCoords(MousePosition); // convert it to world coordinates
			input();

			//////Set View
			_window.setView(view);

			////// Characters

			animation.Update(0, deltaTime.asSeconds());
			//pistolAnimation.UpdateY(0, deltaTime.asSeconds());
			//pistolAnimation.SetSingleFrame(sf::Vector2u(0, 0));
			playerRectangle.setTextureRect(animation.uvRect);
			gun.setTextureRect(pistolAnimation.uvRect);

			//Invincibility Frames
			CheckInvincibilityFrames(timerInvincibility);

			// gravity
			CheckPlayerGravity();
			CheckEnemyGravity(enemyTest, enemyRectangle);

			// Jump
			CheckCharacterJump(player1, playerRectangle);

			// CheckWeaponsFireRate(pistol); // WIP function
			CheckWeaponsFireRate(timerPistolFireRate);

			enemyPlayerDetection.setPosition(enemyRectangle.getPosition().x - 800, enemyRectangle.getPosition().y - 190);

			playerRectangle.move(player1.getMove());

			CheckPlayerFlipSprite();

			// Checks for collisions
			for (int i = 0; i < maxColisionsBoxes; i++)
			{
					CheckCollisionWithTiles(playerRectangle,i,player1);
					CheckCollisionWithTiles(enemyRectangle, i,enemyTest);
			}

			GunRotation();

			CanEnemyHearPlayer(enemyPlayerDetection, enemyRectangle);

			PlayerEnemyCollision(enemyTest,enemyRectangle, timerInvincibility);

			CheckEnemyHP(enemyTest,enemyPlayerDetection,enemyRectangle);
			
		}

		void GameplayScreen::draw()
		{
			// Draw Tilemap with its collision objects
			for (int i = 0; i < maxColisionsBoxes; i++)
			{
				_window.draw(rectangles[i]);
			}
			_window.draw(map);

			
			////---------------------
			// Sprites / Shapes

			//// Player
			_window.draw(playerRectangle);

			//// Enemy
			_window.draw(enemyPlayerDetection);
			_window.draw(enemyRectangle);
			////---------------------

			// Text
			_window.draw(deltaText);

			// HUD
			_window.draw(crosshairTest);
			_window.draw(Lives);
			_window.draw(enemyPlayerDetection);
			_window.draw(crosshairTest);
			_window.draw(gunLimit);
			_window.draw(gun);
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