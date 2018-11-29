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

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr pauseButton;

	static const int maxButtons = 3;

	sf::Font font2;

	sf::Text pauseTitle;

	sf::Text pauseText;

	static tgui::Button::Ptr buttons[maxButtons];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	////---------------------------------------------------------

	// Consts

	static const int maxEnemiesLevelTutorial = 5;

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

	// Victory Condition

	static int zombiesKilled = 0;

	// Gravity

	static int gravityValue = -1;

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
	static sf::Texture zombieTexture;
	static sf::Texture playerHands;
	//static SpriteAnimation zombie;
	static SpriteAnimation playerAnimation;
	static SpriteAnimation pistolAnimation;

	static SpriteAnimation zombiesAnimation[maxEnemiesLevelTutorial];

	// Audio

	static sf::SoundBuffer pistolshoot;
	static sf::Sound pistolGunShoot;

	// Gun Rotation Variable

	static sf::Vector2f v1;
	static sf::Vector2f v2;
	static float prodVect;
	static float modv1;
	static float modv2;
	static float angle = 180;

	// Text
	static sf::Font deltaFont;

	static sf::Text deltaText;
	static sf::Text LivesEnemies[maxEnemiesLevelTutorial];
	static sf::Text zombiesKilledText;

	// Characters
	

	static Character player1;

	static Character enemies[maxEnemiesLevelTutorial];

	// Shapes

	static sf::CircleShape crosshairTest;
	static sf::RectangleShape gun;
	static sf::CircleShape gunLimit;

	//HUD
	static sf::Texture lifeHUD;
	static sf::RectangleShape lifeHUDRectangle;
	static sf::RectangleShape lifeBar;
	static sf::Texture weaponHUD;
	static sf::RectangleShape weaponHUDRectangle;

	static bool gameOnPause;

	namespace Gameplay_Section
	{
		static void signalGoToPause()
		{
			gameOnPause = true;
		}

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

		static void signalGoToPlay()
		{
			gameOnPause = false;
		}

		static void signalGoToRestart()
		{
			Game::setButtonOption(buttonRestart);
			Screens::setHasScreenFinished(true);
		}

		static void signalGoToMenu()
		{
			Game::setButtonOption(buttonMenu);
			Screens::setHasScreenFinished(true);
		}

		void GameplayScreen::init()
		{
			//// Buttons init
			int maxDistance = 0;
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i] = tgui::Button::create();
				gui.add(buttons[i]);
				buttons[i]->setRenderer(blackTheme.getRenderer("Button"));
				buttons[i]->setSize(240, 100);
				buttons[i]->setInheritedFont(fontButtons);
				buttons[i]->setTextSize(50);// 240 100

				buttons[i]->setPosition(400, 270 + maxDistance);

				maxDistance = maxDistance + 130;
			}
			maxDistance = 0;

			buttons[0]->setText("Resume");
			buttons[1]->setText("Restart");
			buttons[2]->setText("Menu");

			buttons[0]->connect("Pressed", signalGoToPlay);
			buttons[1]->connect("Pressed", signalGoToRestart);
			buttons[2]->connect("Pressed", signalGoToMenu);

			//// Window & Screen Settings
			setHasScreenFinished(false);

			MousePosition = sf::Mouse::getPosition(_window);
			worldPos = _window.mapPixelToCoords(MousePosition);

			view.setCenter(200.0f, 1800.f);
			view.zoom(2.0f);

			gameOnPause = false;

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
			playerTexture.loadFromFile("res/assets/textures/playersprite.png");
			playerTexture.setSmooth(true);
			playerTexture.setRepeated(false);

			playerHands.loadFromFile("res/assets/textures/pistol.png");
			playerHands.setSmooth(true);
			playerHands.setRepeated(false);

			player1.setIsPlayer(true);
			player1.setPosition(200, 1400);
			player1.setSize(100, 150);
			player1.setColor(sf::Color::White);
			player1.setIsAlive(true);
			player1.setSpeed(500, 2100);
			player1.setHp(100);

			player1.setTexture(playerTexture);
			playerAnimation.SetAnimation(&playerTexture, sf::Vector2u(9, 3), 0.1f);

			// Player Gun

			gunLimit.setRadius(140);
			gunLimit.setOutlineThickness(10);
			gunLimit.setFillColor(sf::Color::Transparent);
			gunLimit.setOutlineColor(sf::Color::Blue);
			gunLimit.setPosition({ player1.getRectangle().getPosition().x - player1.getRectangle().getGlobalBounds().width / 2, player1.getRectangle().getPosition().y - player1.getRectangle().getGlobalBounds().height / 2 });

			gun.setFillColor(sf::Color::White);
			gun.setPosition(gunLimit.getPosition().x, gunLimit.getPosition().y - 80);
			gun.setSize({ 140,90 });
			gun.setTexture(&playerHands);
			pistolAnimation.SetAnimationY(&playerHands, sf::Vector2u(1, 9), 0.05f);

			// Enemy 1

			zombieTexture.loadFromFile("res/assets/textures/zombie.png");
			zombieTexture.setSmooth(true);
			zombieTexture.setRepeated(false);

			static int increaseEnemyDistance = 0;

			for (int i = 0; i < maxEnemiesLevelTutorial; i++)
			{
				enemies[i].setPosition(400 + increaseEnemyDistance, 700);
				enemies[i].setSize(100, 180);
				enemies[i].setColor(sf::Color::White);
				enemies[i].setIsAlive(true);
				enemies[i].setSpeed(500, 1400);
				enemies[i].setHp(100);
				enemies[i].setCurrentlyTouchingPlayer(true);
				enemies[i].setFlipLeft(true);
				enemies[i].setFlipRight(true);
				enemies[i].setTexture(zombieTexture);
				zombiesAnimation[i].SetAnimation(&zombieTexture, sf::Vector2u(9, 5), 0.1f);

				enemies[i].setPlayerDetectionPosition(enemies[i].getRectangle().getPosition().x - 200, enemies[i].getRectangle().getPosition().y);
				enemies[i].setPlayerDetectionSize(1800.0f, 540);
				enemies[i].setPlayerDetectionColor(sf::Color::Transparent);

				increaseEnemyDistance = increaseEnemyDistance + 800;
			}
			increaseEnemyDistance = 0;


			//// Text

			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");

			deltaText.setCharacterSize(30);
			deltaText.setFont(deltaFont);
			deltaText.setPosition(400, 400);

			//// HUD

			lifeHUD.loadFromFile("res/assets/textures/lifebar.png");
			lifeHUDRectangle.setFillColor(sf::Color::White);
			lifeHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 1300, view.getCenter().y - 800));
			lifeHUDRectangle.setSize({ 600, 250 });
			lifeHUDRectangle.setTexture(&lifeHUD);
			lifeBar.setFillColor(sf::Color::Red);
			lifeBar.setPosition(sf::Vector2f(view.getCenter().x - 1300, view.getCenter().y - 800));
			lifeBar.setSize({ 450, 78 });

			weaponHUD.loadFromFile("res/assets/textures/weaponHUD.png");
			weaponHUDRectangle.setFillColor(sf::Color::White);
			weaponHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			weaponHUDRectangle.setSize({ 500, 250 });
			weaponHUDRectangle.setTexture(&weaponHUD);

			for (int i = 0; i < maxEnemiesLevelTutorial; i++)
			{
				LivesEnemies[i].setCharacterSize(80);
				LivesEnemies[i].setFont(deltaFont);
				LivesEnemies[i].setPosition(50, 1400);
				LivesEnemies[i].setFillColor(sf::Color::Transparent);
			}

			zombiesKilledText.setCharacterSize(80);
			zombiesKilledText.setFont(deltaFont);
			zombiesKilledText.setPosition(500, 200);
			zombiesKilledText.setFillColor(sf::Color::White);

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

			pauseButton = tgui::Button::create();
			gui.add(pauseButton);
			pauseButton->setRenderer(blackTheme.getRenderer("Button"));
			pauseButton->setInheritedFont(fontButtons);
			pauseButton->setSize(50, 50);
			pauseButton->setTextSize(40);// 240 100

			pauseButton->setPosition(940, 10);
			pauseButton->setText("II");
			pauseButton->connect("Pressed", signalGoToPause);

		}

		void GameplayScreen::input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (!(player1.getIsOnGround())) playerAnimation.SetSingleFrame(sf::Vector2u(0, playerJump));
				else if (player1.getFlipRight()) playerAnimation.Update(playerWalkBackward, deltaTime.asSeconds());
				else if (player1.getFlipLeft()) playerAnimation.Update(playerWalkForward, deltaTime.asSeconds());


				cameraLeft = false;
				player1.setMove((player1.getSpeed().x * deltaTime.asSeconds()), 0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (!(player1.getIsOnGround())) playerAnimation.SetSingleFrame(sf::Vector2u(0, playerJump));
				else if (player1.getFlipLeft()) playerAnimation.Update(playerWalkBackward, deltaTime.asSeconds());
				else if (player1.getFlipRight()) playerAnimation.Update(playerWalkForward, deltaTime.asSeconds());


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
				if (!(player1.getIsOnGround())) playerAnimation.SetSingleFrame(sf::Vector2u(0, playerJump));
				else playerAnimation.SetSingleFrame(sf::Vector2u(0, 0));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!(player1.getIsJumping()) && player1.getIsOnGround())
				{
					player1.setIsOnGround(false);
					player1.setIsJumping(true);
					player1.setGravity(false);
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

		static void CheckCollisionWithTiles(Character& Character, int i)
		{
			if (Character.getRectangle().getGlobalBounds().intersects(rectangles[i].getGlobalBounds()))
			{
				if (Character.getRectangle().getPosition().x + Character.getRectangle().getGlobalBounds().width > rectangles[i].getPosition().x &&
					Character.getRectangle().getPosition().x + Character.getRectangle().getGlobalBounds().width < rectangles[i].getPosition().x + 10) // + 10
				{
					Character.setPosition(rectangles[i].getPosition().x - (Character.getRectangle().getGlobalBounds().width), Character.getRectangle().getPosition().y);
				}

				else if (Character.getRectangle().getPosition().x < rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width &&
					Character.getRectangle().getPosition().x > rectangles[i].getPosition().x + rectangles[i].getGlobalBounds().width - 10 // - 10
					)
				{
					Character.setPosition(rectangles[i].getPosition().x + (rectangles[i].getGlobalBounds().width), Character.getRectangle().getPosition().y);
				}

				else if (Character.getRectangle().getPosition().y < rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height &&
					Character.getRectangle().getPosition().y > rectangles[i].getPosition().y + rectangles[i].getGlobalBounds().height - 20) // - 20
				{
					Character.setPosition(Character.getRectangle().getPosition().x, rectangles[i].getPosition().y + (rectangles[i].getGlobalBounds().height));
				}

				else if (Character.getRectangle().getPosition().y + Character.getRectangle().getGlobalBounds().height > rectangles[i].getPosition().y &&
					Character.getRectangle().getPosition().y + Character.getRectangle().getGlobalBounds().height < rectangles[i].getPosition().y + 20) // + 20
				{
					if (Character.getIsPlayer()) player1.setIsOnGround(true);
					cameraDown = false;
					Character.setGravity(false);
					Character.setIsOnWhichGround(i);
					Character.setPosition(Character.getRectangle().getPosition().x, rectangles[i].getPosition().y - (Character.getRectangle().getGlobalBounds().height) + 1); // + 1 , magic number, change later to "GravityFix"
				}
				else
				{
					player1.setIsOnGround(false);
					player1.setGravity(true);
				}
			}
			else
			{
				if (Character.getIsOnWhichGround() == i) Character.setGravity(true);
			}
		}

		static void GunRotation()
		{
			gunLimit.setPosition({ player1.getRectangle().getPosition().x - 70,player1.getRectangle().getPosition().y - 70 });
			gun.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width / 2 ,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 30 });
			

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

		static void PlayerEnemyCollision(Character& enemy, thor::CallbackTimer& timer,SpriteAnimation& animation)
		{
			if (player1.getRectangle().getGlobalBounds().intersects(enemy.getRectangle().getGlobalBounds()))
			{
				if (enemy.getIsAlive())
				{
					if (enemy.getCurrentlyTouchingPlayer())
					{
						if (!(timer.isRunning()))
						{
							timer.start();
							player1.setHp(player1.getHp() - 25);
							lifeBar.setSize({ lifeBar.getSize().x - 112.5f,lifeBar.getSize().y });
						}
					}
					enemy.setCurrentlyTouchingPlayer(false);
					animation.Update(0, deltaTime.asSeconds());
				}
			}
			else
			{
				enemy.setCurrentlyTouchingPlayer(true);
			}
		}

		static void isCrosshairOnTarget(Character& enemy,int i)
		{
			if (crosshairTest.getGlobalBounds().intersects(enemy.getRectangle().getGlobalBounds()))
			{
				if (enemy.getIsAlive())
				{
					LivesEnemies[i].setFillColor(sf::Color::White);
					crosshairTest.setOutlineColor(sf::Color::Green);

					player1.setCanShoot(true);
					if (player1.getCanShoot())
					{
						
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{

							if (!timerPistolFireRate.isRunning())
							{
								pistolGunShoot.play();
								timerPistolFireRate.start();
								enemy.setHp(enemy.getHp() - 25);
								enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y);
							}
						}
						else
						{
						}
					}
				}
			}
			else
			{
				LivesEnemies[i].setFillColor(sf::Color::Transparent);
				crosshairTest.setOutlineColor(sf::Color::Red);
				player1.setCanShoot(false);
			}
		}

		static void CanEnemyHearPlayer(Character& enemy,SpriteAnimation& animation,int i)
		{
			if (player1.getRectangle().getGlobalBounds().intersects(enemy.getPlayerDetection().getGlobalBounds()))
			{

				if (player1.getRectangle().getPosition().x > enemy.getPlayerDetection().getPosition().x + enemy.getPlayerDetection().getGlobalBounds().width / 2)
				{
					if (enemy.getIsAlive())
					{
						if (enemy.getFlipLeft())
						{
							enemy.setOrigin(0, 0);
							enemy.scale(-1, 1);
						}
						enemy.setMove(300 * deltaTime.asSeconds(), 0);
						animation.Update(3, deltaTime.asSeconds());
						enemy.setFlipLeft(false);
						enemy.setFlipRight(true);
					}
					

				}
				else if (player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width < enemy.getPlayerDetection().getPosition().x + enemy.getPlayerDetection().getGlobalBounds().width / 2)
				{
					if (enemy.getIsAlive())
					{
						if (enemy.getFlipRight())
						{
							enemy.setOrigin(enemy.getRectangle().getGlobalBounds().width, 0);
							enemy.scale(-1, 1);
						}
						enemy.setMove(-300 * deltaTime.asSeconds(), 0);
						animation.Update(3, deltaTime.asSeconds());
						enemy.setFlipRight(false);
						enemy.setFlipLeft(true);
					}
					
				}

				isCrosshairOnTarget(enemy,i);
			}
			else
			{
				if (enemy.getIsAlive())
				{
					enemy.getRectangle().move(0, 0);
					animation.Update(2, deltaTime.asSeconds());
				}
				crosshairTest.setOutlineColor(sf::Color::Red);
			}
		}


		static void CheckEnemyHP(Character& enemy,SpriteAnimation& animation,int i)
		{
			if (enemy.getHp() <= 0)
			{
				enemy.setIsAlive(false);
			}

			if (enemy.getIsAlive())
			{
				enemy.setSize(enemy.getSize().x, enemy.getSize().y);
				enemy.setPlayerDetectionSize(enemy.getPlayerDetectionSize().x, enemy.getPlayerDetectionSize().y);
			}
			else
			{
				if (animation.UpdateOnce(1, deltaTime.asSeconds()))
				{
					LivesEnemies[i].setFillColor(sf::Color::Transparent);
					enemy.setSize(0, 0);
					enemy.setPlayerDetectionSize(0, 0);
					enemy.setIsAlive(true);
					enemy.setHp(100);
					enemy.setIsDead(true);
				}

				if (enemy.getIsDead())
				{
					zombiesKilled++;
					enemy.setIsDead(false);
				}
			}
		}

		static void CheckCameraMovement()
		{
			if (player1.getRectangle().getPosition().x > view.getCenter().x + cameraLimitRight)
			{
				if (!(cameraRight))
				{
					cameraRight = true;
					cameraLeft = false;
				}
			}
			else if (player1.getRectangle().getPosition().x < view.getCenter().x - cameraLimitLeft)
			{
				if (!(cameraLeft))
				{
					cameraLeft = true;
					cameraRight = false;
				}
			}

			if (player1.getRectangle().getPosition().y > view.getCenter().y + cameraLimitDown)
			{
				if (!(cameraDown))
				{
					cameraDown = true;
					cameraUp = false;
				}
			}
			else if (player1.getRectangle().getPosition().y < view.getCenter().y - cameraLimitUp)
			{
				if (!(cameraUp))
				{
					cameraUp = true;
					cameraDown = false;
				}
			}

			if (cameraDown) view.setCenter(view.getCenter().x, player1.getRectangle().getPosition().y - cameraLimitDown);
			if (cameraUp)
			{
				view.setCenter(view.getCenter().x, player1.getRectangle().getPosition().y + cameraLimitUp);
			}

			if (cameraRight) view.setCenter(player1.getRectangle().getPosition().x - cameraLimitRight, view.getCenter().y);
			if (cameraLeft) view.setCenter(player1.getRectangle().getPosition().x + cameraLimitLeft, view.getCenter().y);
		}

		static void CheckPlayerFlipSprite()
		{
			if (crosshairTest.getPosition().x < player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width / 2)
			{
				if (player1.getFlipLeft())
				{
					player1.setOrigin(player1.getRectangle().getGlobalBounds().width, 0);
					player1.scale(-1, 1);
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
					player1.setOrigin(0, 0 );
					player1.scale(-1, 1);
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

			lifeBar.setPosition(sf::Vector2f(view.getCenter().x - 1232, view.getCenter().y - 700));
			lifeHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 1300, view.getCenter().y - 800));
			weaponHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			zombiesKilledText.setPosition(sf::Vector2f(view.getCenter().x + 300, view.getCenter().y - 800));

			zombiesKilledText.setString("Zombies Killed: " + toString(zombiesKilled));

			for (int i = 0; i < maxEnemiesLevelTutorial; i++)
			{
				if (enemies[i].getHp() < 0)
				{
					enemies[i].setHp(0);
				}
				LivesEnemies[i].setString("Enemy HP: " + toString(enemies[i].getHp()));
				LivesEnemies[i].setPosition(sf::Vector2f(enemies[i].getRectangle().getPosition().x - 200, enemies[i].getRectangle().getPosition().y - 100));
			}

			crosshairTest.setPosition(worldPos.x - 30, worldPos.y - 30);
		}

		static void CheckPlayerGravity()
		{
			if (player1.getGravity())
			{
				player1.setPosition(player1.getRectangle().getPosition().x, (player1.getRectangle().getPosition().y + (gravitySpeed * deltaTime.asSeconds())));
				cameraUp = false;
			}
		}

		static void CheckEnemyGravity(Character& enemy)
		{
			if (enemy.getGravity())
			{
				enemy.setPosition(enemy.getRectangle().getPosition().x, enemy.getRectangle().getPosition().y + (enemy.getSpeed().y * deltaTime.asSeconds()));
			}
		}

		static void CheckCharacterJump(Character& character)
		{
			if (character.getIsJumping())
			{
				if (character.isTimerJumpRunning())
				{
					cameraDown = false;
					character.setPosition(character.getRectangle().getPosition().x, character.getRectangle().getPosition().y + (character.getSpeed().y * deltaTime.asSeconds()*(-1)));
				}

				if (character.isTimerJumpExpired())
				{
					character.setIsJumping(false);
					character.setGravity(true);
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
				pistolAnimation.UpdateY(pistolShoot, deltaTime.asSeconds());
			}
		}

		//WIP Function
		static void CheckInvincibilityFrames(thor::CallbackTimer& timer,int i)
		{
			if (timer.isRunning())
			{
				player1.setColor(sf::Color::Green);
			}

			if (timer.isExpired())
			{
				timer.reset(initialInvincibilityTime);
				player1.setColor(sf::Color::White);
				if (player1.getRectangle().getGlobalBounds().intersects(enemies[i].getRectangle().getGlobalBounds()))
				{
					enemies[i].setCurrentlyTouchingPlayer(true);
				}
			}
		}

		//-------END Gameplay Functions

		void GameplayScreen::update()
		{
			if (!gameOnPause)
			{
				/////// Setting the pause buttons OFF
				for (int i = 0; i < maxButtons; i++)
				{
					buttons[i]->setVisible(false);
				}

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

				if (player1.getIsJumping())
				{
					player1.setGravity(true);
				}

				player1.setTextureRect(playerAnimation.uvRect);
				gun.setTextureRect(pistolAnimation.uvRect);

				for (int i = 0; i < maxEnemiesLevelTutorial; i++)
				{
					enemies[i].setTextureRect(zombiesAnimation[i].uvRect);

					//Invincibility Frames
					CheckInvincibilityFrames(timerInvincibility,i);

					// gravity
					CheckEnemyGravity(enemies[i]);

					enemies[i].setPlayerDetectionPosition(enemies[i].getRectangle().getPosition().x - 800, enemies[i].getRectangle().getPosition().y - 190);

					PlayerEnemyCollision(enemies[i], timerInvincibility, zombiesAnimation[i]);

					CheckEnemyHP(enemies[i], zombiesAnimation[i],i);

					CanEnemyHearPlayer(enemies[i], zombiesAnimation[i], i);
				}

				// gravity
				CheckPlayerGravity();
				

				// Jump
				CheckCharacterJump(player1);

				CheckWeaponsFireRate(timerPistolFireRate);


				
				
				player1.getRectangle().move(player1.getMove());

				CheckPlayerFlipSprite();

				// Checks for collisions
				for (int i = 0; i < maxColisionsBoxes; i++)
				{
					CheckCollisionWithTiles(player1, i); // Check rectangle here
					for (int f = 0; f < maxEnemiesLevelTutorial; f++)
					{
						CheckCollisionWithTiles(enemies[f], i);
					}	
				}

				GunRotation();

				

				

				
			}
			else if (gameOnPause)
			{
				//Setting the pause buttons ON
				for (int i = 0; i < maxButtons; i++)
				{
					buttons[i]->setVisible(true);
				}

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


			////---------------------
			// Sprites / Shapes

			//// Player
			_window.draw(player1.getRectangle());

			//// Enemy
			for (int i = 0; i < maxEnemiesLevelTutorial; i++)
			{
				_window.draw(enemies[i].getPlayerDetection());
				_window.draw(enemies[i].getRectangle());
			}
			
			////---------------------

			// Text
			_window.draw(deltaText);

			// HUD
			_window.draw(zombiesKilledText);
			_window.draw(crosshairTest);
			_window.draw(lifeBar);
			_window.draw(lifeHUDRectangle);
			_window.draw(weaponHUDRectangle);
			for (int i = 0; i < maxEnemiesLevelTutorial; i++)
			{
				_window.draw(LivesEnemies[i]);
			}
			_window.draw(crosshairTest);
			_window.draw(gun);
		}

		void GameplayScreen::deInit()
		{
			_window.setView(_window.getDefaultView());
			view.zoom(0.5f);
			pauseButton->setVisible(false);
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i]->setVisible(false);
			}
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