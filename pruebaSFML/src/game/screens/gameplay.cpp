#include "gameplay.h"

#include "menu.h"

namespace newgame
{
	sf::Event event;
	////------------ Tilemap Settings

	static tmx::TileMap map("res/assets/tiles/firerange.tmx");
	static tmx::TileMap map2("res/assets/tiles/level1.tmx");

	const int maxLevels = 2;
	level levels[maxLevels];

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	//Pause

	static tgui::Button::Ptr pauseButton;

	static const int maxButtons = 3;

	static tgui::Button::Ptr buttons[maxButtons];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	////---------------------------------------------------------

	// Consts

	static const int maxMedkitsFloor = 2;
	static const int maxMedkitsDrop = 3;

	static const int maxEnemiesLevelTutorial = 5;
	static const int maxEnemiesLevel1 = 20;
	static const int maxTutorialTexts = 9;
	static const int enemySpeed = 300;

	static const int defaultHP = 100;

	static const int tutorialFontSize = 50;
	static const sf::Color tutorialColor = sf::Color::Black;

	static const int HUDdefaultFontSize = 80;

	static const sf::Color transparentBlue = { 0,0,110,100 };
	static const sf::Color transparentRed = { 255,0,0,80 };
	static const sf::Color transparentGreen = { 0,255,0,80 };
	static const sf::Color shotParticlesColor = { 125, 81, 0 ,255 };

	static const int rectangleCollisionLimitX = 10;
	static const int rectangleCollisionLimitY = 20;
	static const float GravityAndWallFix = 0.5; // int 1

	static const int DifferentMousePositions = 16;
	static int DistanceValue = 1000;
	static int RectangleValue = 500;

	static int currentWeapon = -1;

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

	// Weapons

	bool inputActive = false;
	bool inputActive2 = false;
	bool inputActive3 = false;

	weapon weapons[maxWeapons];

	static sf::RectangleShape gun;
	static SpriteAnimation pistolAnimation;
	static sf::Texture playerHands;
	static const sf::Time pistolFireRate = sf::seconds(0.5f);

	static sf::RectangleShape shotgunRectangle;
	static SpriteAnimation shotgunAnimation;
	static sf::Texture shotgunTexture;
	static const sf::Time shotgunFireRate = sf::seconds(1.0f);

	static sf::RectangleShape smgRectangle;
	static SpriteAnimation smgAnimation;
	static sf::Texture smgTexture;
	static const sf::Time smgFireRate = sf::seconds(0.09f);

	// Victory Condition

	static int zombiesKilled = 0;
	static const int zombiesKilledObjetiveTutorial = 3;
	static const int zombiesKilledObjetiveLevel1 = 10;
	static bool playerWon = false;
	static bool playerLost = false;

	// Gravity

	static int gravityValue = -1;

	static int gravitySpeed = 0;

	// Mouse Position

	static sf::Vector2i MousePosition;
	static sf::Vector2f worldPos;

	//Timers

	static const sf::Time initialInvincibilityTime = sf::seconds(3.0f);
	static thor::CallbackTimer timerInvincibility;

	static const sf::Time footstepInitialTime = sf::seconds(0.49f);
	static thor::CallbackTimer footstepTimer;

	static const sf::Time bloodInitialTime = sf::seconds(0.5f);
	static thor::CallbackTimer bloodTimer;
	static sf::Vector2f bloodDisablePosition;

	static const sf::Time shootInitialTime = sf::seconds(0.2f);
	static thor::CallbackTimer shootTimer;
	static sf::Vector2f shootDisablePosition;
	static int currentEnemy = -1;

	//Textures & Animations
	static sf::Texture pistolAmmoTexture;
	static sf::Texture smgAmmoTexture;
	static sf::Texture shotgunAmmoTexture;
	static sf::Texture medkitTexture;
	static sf::Texture playerTexture;
	static sf::Texture zombieTexture;
	
	static SpriteAnimation playerAnimation;
	static SpriteAnimation zombiesAnimation[maxEnemiesLevel1];

	//Particles

	static ParticleSystem particles(900);
	static ParticleSystem particlesShoot(500);
	// Audio

	static sf::Music level1Ambience;
	static sf::Music level0Ambience;
	static sf::Music level1Song;
	static sf::Music tutorialSong;

	//static sf::SoundBuffer pistolShootBuffer;
	//static sf::Sound pistolShoot;

	static sf::SoundBuffer footstep;
	static sf::Sound playerFootStep;

	static sf::SoundBuffer jump;
	static sf::Sound playerJumpSound;

	static sf::SoundBuffer soundAttack;
	static sf::SoundBuffer soundAlert;
	static sf::SoundBuffer soundDeath;
	static sf::SoundBuffer soundPain;

	static sf::Sound zombieAttack;
	static sf::Sound zombieAlert;
	static sf::Sound zombieDeath;
	static sf::Sound zombiePain;

	static sf::SoundBuffer soundHeal;
	static sf::Sound playerHeal;

	static sf::SoundBuffer ammoPickupSoundBuffer;
	static sf::Sound ammoPickupSound;

	// Gun Rotation Variable

	static sf::Vector2f v1;
	static sf::Vector2f v2;
	static float prodVect;
	static float modv1;
	static float modv2;
	static float angle = 180;

	// Text
	static sf::Font deltaFont;
	static sf::Font font2;

	static sf::Text zombiesKilledText;

	static sf::Text playerStateText;
	static sf::Text bulletsText;

	static sf::Text tutorialText[maxTutorialTexts];

	// Characters
	

	static Character player1;

	static Character enemies[maxEnemiesLevel1];

	static Character medkitFloor[maxMedkitsFloor];
	static Character medkitDrop;
	static Character pistolAmmo;
	static Character smgAmmo;
	static Character shotgunAmmo;

	// Shapes

	static sf::RectangleShape lineCollision;
	static int inWhichRectangle = -1;
	static int inWhichEnemy = -1;
	static bool canDealDamage = false;
	//static bool 



	static sf::Texture crosshairTexture;
	static sf::CircleShape crosshairTest;
	
	static sf::CircleShape gunLimit;
	static sf::RectangleShape Exit;

	//HUD
	static sf::Texture lifeHUD;
	static sf::RectangleShape lifeHUDRectangle;
	static sf::RectangleShape lifeBar;
	static sf::Texture weaponHUD;
	static sf::RectangleShape weaponHUDRectangle;
	static sf::Texture pistolTexture;
	static sf::RectangleShape pistolRectangle;
	static sf::Texture shotgunHUDTexture;
	static sf::RectangleShape shotgunHUD;
	static sf::Texture smgHUDTexture;
	static sf::RectangleShape smgHUD;

	static bool gameOnPause;

	int aux;

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
			playerWon = false;
			playerLost = false;
			zombiesKilled = 0;
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

			view.zoom(2.0f);

			gameOnPause = false;

			//// World Entities

			// Weapons

			currentWeapon = 1;

			//pistolShootBuffer.loadFromFile("res/assets/sounds/pistolshoot.wav");
			//pistolShoot.setB
			weapons[pistol].setAmmo(60);
			weapons[pistol].setDamage(25);
			weapons[pistol].setSoundVolume(globalSoundVolume);
			weapons[pistol].setSoundBufferLocation("res/assets/sounds/pistolshoot.wav");
			weapons[pistol].setSoundBufferLocationDraw("res/assets/sounds/pistoldraw.wav");
			weapons[pistol].setFireRateTimer(pistolFireRate);

			weapons[shotgun].setAmmo(30);
			weapons[shotgun].setDamage(50);
			weapons[shotgun].setSoundVolume(globalSoundVolume);
			weapons[shotgun].setSoundBufferLocation("res/assets/sounds/shotgunshoot.wav");
			weapons[shotgun].setSoundBufferLocationDraw("res/assets/sounds/shotgundraw.wav");
			weapons[shotgun].setFireRateTimer(shotgunFireRate);

			shotgunTexture.loadFromFile("res/assets/textures/shotgun.png");
			shotgunTexture.setSmooth(true);
			shotgunTexture.setRepeated(false);

			shotgunRectangle.setFillColor(sf::Color::White);
			shotgunRectangle.setSize({ 140,90 });
			shotgunRectangle.setTexture(&shotgunTexture);
			shotgunAnimation.SetAnimation(&shotgunTexture, sf::Vector2u(9, 1), 0.11f);

			weapons[smg].setAmmo(150);
			weapons[smg].setDamage(5);
			weapons[smg].setSoundVolume(globalSoundVolume);
			weapons[smg].setSoundBufferLocation("res/assets/sounds/smgshoot.wav");
			weapons[smg].setSoundBufferLocationDraw("res/assets/sounds/smgdraw.wav");
			weapons[smg].setFireRateTimer(smgFireRate);

			smgTexture.loadFromFile("res/assets/textures/smg.png");
			smgTexture.setSmooth(true);
			smgTexture.setRepeated(false);

			smgRectangle.setFillColor(sf::Color::White);
			smgRectangle.setSize({ 110,70 });
			smgRectangle.setTexture(&smgTexture);
			smgAnimation.SetAnimation(&smgTexture, sf::Vector2u(9, 1), 0.025f);

			/*for (int i = 0; i < length; i++)
			{

			}*/

			//Tilemap

			levels[0].setResultPath("res/assets/tiles/firerange.tmx");
			levels[0].setRectangles(30);
			levels[0].setEnemyKillObjetive(3);

			levels[1].setResultPath("res/assets/tiles/level1.tmx");
			levels[1].setRectangles(33);
			levels[1].setEnemyKillObjetive(10);

			// Player 1
			playerTexture.loadFromFile("res/assets/textures/playersprite.png");
			playerTexture.setSmooth(true);
			playerTexture.setRepeated(false);

			playerHands.loadFromFile("res/assets/textures/pistol.png");
			playerHands.setSmooth(true);
			playerHands.setRepeated(false);


			switch (levelNumber)
			{
			case 0:
				player1.setPosition(200, 1600);
				break;
			case 1:
				player1.setPosition(200, 1200);
				break;
			default:
				break;
			}

			player1.setGravity(false);
			player1.setIsPlayer(true);
			player1.setSize(100, 150);
			player1.setColor(sf::Color::White);
			player1.setIsAlive(true);
			player1.setSpeed(500, 2100);
			player1.setHp(defaultHP);
			player1.setCanShoot(true);

			player1.setTexture(playerTexture);
			playerAnimation.SetAnimation(&playerTexture, sf::Vector2u(9, 3), 0.1f);
			player1.setVelocity({ player1.getVelocity().x,0.0f });

			// Player Gun


			lineCollision.setSize(sf::Vector2f(300, 10));
			lineCollision.setFillColor(sf::Color::Transparent);


			gunLimit.setRadius(140);
			gunLimit.setOutlineThickness(10);
			gunLimit.setFillColor(sf::Color::Transparent);
			gunLimit.setOutlineColor(sf::Color::Blue);
			gunLimit.setPosition({ player1.getRectangle().getPosition().x - player1.getRectangle().getGlobalBounds().width / 2, player1.getRectangle().getPosition().y - player1.getRectangle().getGlobalBounds().height / 2 });

			gun.setFillColor(sf::Color::White);
			gun.setSize({ 140,90 });
			gun.setTexture(&playerHands);
			pistolAnimation.SetAnimationY(&playerHands, sf::Vector2u(1, 9), 0.055f);

			// Enemy 1

			zombieTexture.loadFromFile("res/assets/textures/zombie.png");
			zombieTexture.setSmooth(true);
			zombieTexture.setRepeated(false);


			// Reseting Enemies
			for (int i = 0; i < maxEnemiesLevel1; i++)
			{
				enemies[i].setPosition(0, 0);
				enemies[i].setSize(0, 0);
				enemies[i].setColor(sf::Color::Transparent);
				enemies[i].setIsAlive(true);
				enemies[i].setSpeed(0, 0);
				enemies[i].setHp(defaultHP);
				enemies[i].setCurrentlyTouchingPlayer(false);
				enemies[i].setFlipLeft(false);
				enemies[i].setFlipRight(false);
				enemies[i].setIsDead(false);
			}

			// Creating the enemies depening on the level

			static int increaseEnemyDistance = 0;

			if (levelNumber == 0)
			{
				for (int i = 0; i < maxEnemiesLevelTutorial; i++)
				{
					enemies[i].setPosition(5000.f + static_cast<float>(increaseEnemyDistance), 1500.f);
					enemies[i].setSize(100, 180);
					enemies[i].setColor(sf::Color::White);
					enemies[i].setIsAlive(true);
					enemies[i].setSpeed(500, 1400);
					enemies[i].setHp(defaultHP);
					enemies[i].setCurrentlyTouchingPlayer(true);
					enemies[i].setFlipLeft(true);
					enemies[i].setFlipRight(true);
					enemies[i].setTexture(zombieTexture);
					zombiesAnimation[i].SetAnimation(&zombieTexture, sf::Vector2u(9, 8), 0.1f);

					enemies[i].setPlayerDetectionPosition(enemies[i].getRectangle().getPosition().x - 500, enemies[i].getRectangle().getPosition().y);
					enemies[i].setPlayerDetectionSize(1000.0f, 540); //1400
					enemies[i].setPlayerDetectionColor(sf::Color::Transparent);

					increaseEnemyDistance = increaseEnemyDistance + 100;
				}
			}

			if (levelNumber == 1)
			{
				for (int i = 0; i < maxEnemiesLevel1; i++)
				{					
					enemies[i].setSize(100, 180);
					enemies[i].setColor(sf::Color::White);
					enemies[i].setIsAlive(true);
					enemies[i].setSpeed(500, 1400);
					enemies[i].setHp(defaultHP);
					enemies[i].setCurrentlyTouchingPlayer(true);
					enemies[i].setFlipLeft(true);
					enemies[i].setFlipRight(true);
					enemies[i].setTexture(zombieTexture);
					zombiesAnimation[i].SetAnimation(&zombieTexture, sf::Vector2u(9, 8), 0.1f);

					enemies[i].setPlayerDetectionPosition(enemies[i].getRectangle().getPosition().x - 500, enemies[i].getRectangle().getPosition().y);
					enemies[i].setPlayerDetectionSize(1000.0f, 540); // 1000
					enemies[i].setPlayerDetectionColor(sf::Color::Transparent);
				}


				// NPC Positions

				//part 1
				enemies[0].setPosition(300.f, 100.f);
				enemies[1].setPosition(500.f, 100.f);

				enemies[2].setPosition(1700.f, 1100.f);

				enemies[3].setPosition(1800.f, 100.f);

				enemies[4].setPosition(2600.f, 700.f);

				enemies[5].setPosition(4000.f, 700.f);

				//part 2
				enemies[6].setPosition(4800.f, 700.f);
				enemies[7].setPosition(5100.f, 700.f);

				enemies[8].setPosition(5300.f, 1200.f);
				enemies[9].setPosition(5600.f, 1200.f);

				enemies[10].setPosition(6700.f, 700.f);

				enemies[11].setPosition(7500.f, 1000.f);
				enemies[12].setPosition(8200.f, 1200.f);

				//part 3
				enemies[13].setPosition(9000.f, 700.f);
				enemies[14].setPosition(9300.f, 700.f);

				enemies[15].setPosition(10100.f, 300.f);

				enemies[16].setPosition(10300.f, 700.f);
				enemies[17].setPosition(10800.f, 700.f);
				enemies[18].setPosition(11200.f, 700.f);
				enemies[19].setPosition(11600.f, 300.f);

			}

			increaseEnemyDistance = 0;

			// Medkit Floor

			medkitTexture.loadFromFile("res/assets/textures/medkit.png");
			medkitTexture.setSmooth(true);
			medkitTexture.setRepeated(false);

			for (int i = 0; i < maxMedkitsFloor; i++)
			{
				medkitFloor[i].setColor(sf::Color::White);
				medkitFloor[i].setPosition(900.0f, 1400.0f);
				medkitFloor[i].setSize(100.0f, 70.0f);
				medkitFloor[i].setIsAlive(true);
				medkitFloor[i].setSpeed(0.0f, 900.0f);
				medkitFloor[i].setTexture(medkitTexture);
			}

			medkitFloor[0].setPosition(7000.0f, 200.0f);
			medkitFloor[1].setPosition(10600.0f, 200.0f);

			// Medkit Drop

			medkitDrop.setColor(sf::Color::White);
			medkitDrop.setSize(0.0f, 0.0f);
			medkitDrop.setIsAlive(false);
			medkitDrop.setSpeed(0.0f, 900.0f);
			medkitDrop.setTexture(medkitTexture);

			// Ammo

			pistolAmmoTexture.loadFromFile("res/assets/textures/pistolammo.png");
			pistolAmmoTexture.setSmooth(true);
			pistolAmmoTexture.setRepeated(false);

			pistolAmmo.setColor(sf::Color::White);
			pistolAmmo.setSize(0.0f, 0.0f);
			pistolAmmo.setIsAlive(false);
			pistolAmmo.setSpeed(0.0f, 900.0f);
			pistolAmmo.setTexture(pistolAmmoTexture);


			smgAmmoTexture.loadFromFile("res/assets/textures/smgammo.png");
			smgAmmoTexture.setSmooth(true);
			smgAmmoTexture.setRepeated(false);

			smgAmmo.setColor(sf::Color::White);
			smgAmmo.setSize(0.0f, 0.0f);
			smgAmmo.setIsAlive(false);
			smgAmmo.setSpeed(0.0f, 900.0f);
			smgAmmo.setTexture(smgAmmoTexture);

			shotgunAmmoTexture.loadFromFile("res/assets/textures/shotgunammo.png");
			shotgunAmmoTexture.setSmooth(true);
			shotgunAmmoTexture.setRepeated(false);
			
			shotgunAmmo.setColor(sf::Color::White);
			shotgunAmmo.setSize(0.0f, 0.0f);
			shotgunAmmo.setIsAlive(false);
			shotgunAmmo.setSpeed(0.0f, 900.0f);
			shotgunAmmo.setTexture(shotgunAmmoTexture);

			bloodDisablePosition = { -800,-800 };
			shootDisablePosition = { -3000,-3000 };

			//// Text
			deltaFont.loadFromFile("res/assets/fonts/sansation.ttf");
			font2.loadFromFile("res/assets/fonts/times_new_yorker.ttf");

			playerStateText.setCharacterSize(HUDdefaultFontSize);
			playerStateText.setFont(deltaFont);
			playerStateText.setPosition(400, 400);
			playerStateText.setString("");

			if (levelNumber==0)
			{
				tutorialText[0].setCharacterSize(tutorialFontSize);
				tutorialText[0].setFont(font2);
				tutorialText[0].setPosition(200, 1600);
				tutorialText[0].setFillColor(tutorialColor);
				tutorialText[0].setString("Press W and D to move horizontally");

				tutorialText[1].setCharacterSize(tutorialFontSize);
				tutorialText[1].setFont(font2);
				tutorialText[1].setPosition(200, 1700);
				tutorialText[1].setFillColor(tutorialColor);
				tutorialText[1].setString("Press SPACEBAR to jump, go to the next room!");

				tutorialText[7].setCharacterSize(tutorialFontSize);
				tutorialText[7].setFont(font2);
				tutorialText[7].setPosition(200, 1400);
				tutorialText[7].setFillColor(tutorialColor);
				tutorialText[7].setString("You can Run with LSHIFT and Pause the game with the ESC button.");

				tutorialText[2].setCharacterSize(tutorialFontSize);
				tutorialText[2].setFont(font2);
				tutorialText[2].setPosition(3525, 1700);
				tutorialText[2].setFillColor(tutorialColor);
				tutorialText[2].setString("Aim with the mouse cursor and shoot with Left Mouse Button");

				tutorialText[3].setCharacterSize(tutorialFontSize);
				tutorialText[3].setFont(font2);
				tutorialText[3].setPosition(3525, 1900);
				tutorialText[3].setFillColor(tutorialColor);
				tutorialText[3].setString("You will be able to shoot once the zombie sees you");

				tutorialText[6].setCharacterSize(tutorialFontSize);
				tutorialText[6].setFont(font2);
				tutorialText[6].setPosition(3525, 2100);
				tutorialText[6].setFillColor(tutorialColor);
				tutorialText[6].setString("Choose your weapons with 1 (Pistol) 2 (Shotgun) 3 (SMG) number buttons.");

				tutorialText[4].setCharacterSize(tutorialFontSize);
				tutorialText[4].setFont(font2);
				tutorialText[4].setPosition(2500, 1200);
				tutorialText[4].setFillColor(tutorialColor);
				tutorialText[4].setString("Once you have killed enough zombies,the exit will be unlocked!");

				tutorialText[8].setCharacterSize(tutorialFontSize);
				tutorialText[8].setFont(font2);
				tutorialText[8].setPosition(2400, 1400);
				tutorialText[8].setFillColor(tutorialColor);
				tutorialText[8].setString("Zombies may drop ammo and medkits!.");

				tutorialText[5].setCharacterSize(tutorialFontSize);
				tutorialText[5].setFont(font2);
				tutorialText[5].setPosition(1300, 1100);
				tutorialText[5].setFillColor(tutorialColor);
				tutorialText[5].setString("Go to the blue rectangle to exit the tutorial!");
			}
			


			//// HUD

			bulletsText.setCharacterSize(50);
			bulletsText.setFont(font2);
			bulletsText.setPosition(sf::Vector2f(view.getCenter().x - 200, view.getCenter().y - 100));
			bulletsText.setFillColor(sf::Color::Red);
			bulletsText.setString("-");

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

			pistolTexture.loadFromFile("res/assets/textures/hands.png");
			pistolRectangle.setFillColor(sf::Color::White);
			pistolRectangle.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			pistolRectangle.setSize({ 170, 90 });
			pistolRectangle.setTexture(&pistolTexture);

			shotgunHUDTexture.loadFromFile("res/assets/textures/shotgunHUD.png");
			shotgunHUD.setFillColor(sf::Color::White);
			shotgunHUD.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			shotgunHUD.setSize({ 170, 90 });
			shotgunHUD.setTexture(&shotgunHUDTexture);

			smgHUDTexture.loadFromFile("res/assets/textures/smgHUD.png");
			smgHUD.setFillColor(sf::Color::White);
			smgHUD.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			smgHUD.setSize({ 170, 90 });
			smgHUD.setTexture(&smgHUDTexture);

			zombiesKilledText.setCharacterSize(HUDdefaultFontSize);
			zombiesKilledText.setFont(deltaFont);
			zombiesKilledText.setPosition(500, 200);
			zombiesKilledText.setFillColor(sf::Color::White);

			crosshairTexture.loadFromFile("res/assets/textures/crosshair.png");
			crosshairTest.setRadius(30);
			crosshairTest.setOutlineThickness(1);
			crosshairTest.setFillColor(sf::Color::Red);
			crosshairTest.setOutlineColor(sf::Color::Transparent);
			crosshairTest.setPosition(static_cast<sf::Vector2f>(worldPos));
			crosshairTest.setTexture(&crosshairTexture);

			//// Game Mechanics
			gravitySpeed = 800;

			//// Audio

			/*pistolshoot.loadFromFile("res/assets/sounds/pistolshoot.wav");
			pistolGunShoot.setBuffer(pistolshoot);
			pistolGunShoot.setVolume(static_cast<float>(globalSoundVolume));*/

			footstep.loadFromFile("res/assets/sounds/footstep.wav");
			playerFootStep.setBuffer(footstep);
			playerFootStep.setVolume(static_cast<float>(globalSoundVolume));

			jump.loadFromFile("res/assets/sounds/jump.wav");
			playerJumpSound.setBuffer(jump);
			playerJumpSound.setVolume(static_cast<float>(globalSoundVolume));


			
			soundAttack.loadFromFile("res/assets/sounds/zombie_attack.wav");
			zombieAttack.setBuffer(soundAttack);
			zombieAttack.setVolume(static_cast<float>(globalSoundVolume));

			soundDeath.loadFromFile("res/assets/sounds/zombie_death.wav");
			zombieDeath.setBuffer(soundDeath);
			zombieDeath.setVolume(static_cast<float>(globalSoundVolume));

			soundAlert.loadFromFile("res/assets/sounds/zombie_alert.wav");
			zombieAlert.setBuffer(soundAlert);
			zombieAlert.setVolume(static_cast<float>(globalSoundVolume));

			soundPain.loadFromFile("res/assets/sounds/zombie_pain.wav");
			zombiePain.setBuffer(soundPain);
			zombiePain.setVolume(static_cast<float>(globalSoundVolume));

			soundHeal.loadFromFile("res/assets/sounds/heal.wav");
			playerHeal.setBuffer(soundHeal);
			playerHeal.setVolume(static_cast<float>(globalSoundVolume));

			ammoPickupSoundBuffer.loadFromFile("res/assets/sounds/ammopickup.wav");
			ammoPickupSound.setBuffer(ammoPickupSoundBuffer);
			ammoPickupSound.setVolume(static_cast<float>(globalSoundVolume));

			if (levelNumber == 0)
			{
				level0Ambience.openFromFile("res/assets/music/level0ambience.wav");
				level0Ambience.setLoop(true);
				level0Ambience.setVolume(static_cast<float>(globalMusicVolume / 1));
				level0Ambience.play();
				tutorialSong.openFromFile("res/assets/music/tuto.wav");
				tutorialSong.setLoop(true);
				tutorialSong.setVolume(static_cast<float>(globalMusicVolume / 1));
				tutorialSong.play();
			}

			if (levelNumber == 1)
			{
				level1Ambience.openFromFile("res/assets/music/level1ambience.wav");
				level1Ambience.setLoop(true);
				level1Ambience.setVolume(static_cast<float>(globalMusicVolume / 1));
				level1Ambience.play();
				level1Song.openFromFile("res/assets/music/level1.wav");
				level1Song.setLoop(true);
				level1Song.setVolume(static_cast<float>(globalMusicVolume / 1));
				level1Song.play();
			}

			
			aux = 0;
			// GUI

			pauseButton = tgui::Button::create();
			gui.add(pauseButton);
			pauseButton->setRenderer(blackTheme.getRenderer("Button"));
			pauseButton->setInheritedFont(fontButtons);
			pauseButton->setSize(50, 50);
			pauseButton->setTextSize(40);

			pauseButton->setPosition(940, 10);
			pauseButton->setText("II");
			pauseButton->connect("Pressed", signalGoToPause);

			// Exit

			Exit.setSize(sf::Vector2f(100, 200));
			Exit.setFillColor(transparentBlue);

			switch (levelNumber)
			{
			case 0:
				Exit.setPosition(900, 1100);
				break;
			case 1:
				Exit.setPosition(11750, 1400);
				break;
			default:
				break;
			}

			
		}

		void GameplayScreen::input()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (player1.getMoveRight())
				{
					if (!(player1.getIsOnGround())) playerAnimation.SetSingleFrame(sf::Vector2u(0, playerJump));
					else if (player1.getFlipRight()) playerAnimation.Update(playerWalkBackward, deltaTime);
					else if (player1.getFlipLeft()) playerAnimation.Update(playerWalkForward, deltaTime);

					if (!footstepTimer.isRunning())
					{
						footstepTimer.reset(footstepInitialTime);
						footstepTimer.start();
						playerFootStep.play();
					}

					cameraLeft = false;
					player1.setMove((player1.getSpeed().x * deltaTime), 0);
				}		
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (player1.getMoveLeft())
				{
					if (!(player1.getIsOnGround())) playerAnimation.SetSingleFrame(sf::Vector2u(0, playerJump));
					else if (player1.getFlipLeft()) playerAnimation.Update(playerWalkBackward, deltaTime);
					else if (player1.getFlipRight()) playerAnimation.Update(playerWalkForward, deltaTime);

					if (!footstepTimer.isRunning())
					{
						footstepTimer.reset(footstepInitialTime);
						footstepTimer.start();
						playerFootStep.play();
					}

					cameraRight = false;
					player1.setMove((player1.getSpeed().x * deltaTime*(-1)), 0);
				}
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
					playerJumpSound.play();
				}
			}
			else
			{
				Game::setIsKeyPressed(false);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				player1.setSpeed(750, 2100);
			}
			else
			{
				player1.setSpeed(500, 2100);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				if (!inputActive)
				{
					weapons[pistol].playDrawSound();
					currentWeapon = pistol;
					inputActive = true;
				}			
			}
			else
			{
				inputActive = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				if (!inputActive2)
				{
					weapons[shotgun].playDrawSound();
					currentWeapon = shotgun;
					inputActive2 = true;
				}
			}
			else
			{
				inputActive2 = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				if (!inputActive3)
				{
					weapons[smg].playDrawSound();
					currentWeapon = smg;
					inputActive3 = true;
				}
			}
			else
			{
				inputActive3 = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				signalGoToPause();
			}
			else
				Game::setIsKeyPressed(false);
		}

		

		//------- Gameplay Functions

		static void CheckCollisionWithTiles(Character& Character, int i)
		{
			if (Character.getRectangle().getGlobalBounds().intersects(levels[levelNumber].getRectangles(i).getGlobalBounds()))
			{
				if (Character.getRectangle().getPosition().x + Character.getRectangle().getGlobalBounds().width > levels[levelNumber].getRectangles(i).getPosition().x &&
					Character.getRectangle().getPosition().x + Character.getRectangle().getGlobalBounds().width < levels[levelNumber].getRectangles(i).getPosition().x + rectangleCollisionLimitX)
				{
					Character.setPosition(levels[levelNumber].getRectangles(i).getPosition().x - (Character.getRectangle().getGlobalBounds().width) + GravityAndWallFix, Character.getRectangle().getPosition().y);
					Character.setMoveRight(false);
					Character.setIsOnWhichLeftWall(i);
					if (Character.getIsPlayer())
					{
						player1.setIsOnGround(false);
					}
				}

				else if (Character.getRectangle().getPosition().x < levels[levelNumber].getRectangles(i).getPosition().x + levels[levelNumber].getRectangles(i).getGlobalBounds().width &&
					Character.getRectangle().getPosition().x > levels[levelNumber].getRectangles(i).getPosition().x + levels[levelNumber].getRectangles(i).getGlobalBounds().width - rectangleCollisionLimitX
					)
				{
					Character.setPosition(levels[levelNumber].getRectangles(i).getPosition().x + (levels[levelNumber].getRectangles(i).getGlobalBounds().width) - GravityAndWallFix, Character.getRectangle().getPosition().y);
					Character.setMoveLeft(false);
					Character.setIsOnWhichRightWall(i);
					if (Character.getIsPlayer())
					{
						player1.setIsOnGround(false);
					}
				}

				else if (Character.getRectangle().getPosition().y < levels[levelNumber].getRectangles(i).getPosition().y + levels[levelNumber].getRectangles(i).getGlobalBounds().height &&
					Character.getRectangle().getPosition().y > levels[levelNumber].getRectangles(i).getPosition().y + levels[levelNumber].getRectangles(i).getGlobalBounds().height - (levels[levelNumber].getRectangles(i).getGlobalBounds().height / 2)) // rectangleCollisionLimitY
				{
					Character.setPosition(Character.getRectangle().getPosition().x, levels[levelNumber].getRectangles(i).getPosition().y + (levels[levelNumber].getRectangles(i).getGlobalBounds().height));
					Character.setMoveUp(false);
					Character.setIsOnWhichCeiling(i);
					if (Character.getIsPlayer())
					{
						player1.setVelocity({ player1.getVelocity().x,0.0f });
					}
					
				}

				else if (Character.getRectangle().getPosition().y + Character.getRectangle().getGlobalBounds().height > levels[levelNumber].getRectangles(i).getPosition().y &&
					Character.getRectangle().getPosition().y + Character.getRectangle().getGlobalBounds().height < levels[levelNumber].getRectangles(i).getPosition().y + (levels[levelNumber].getRectangles(i).getGlobalBounds().height/2) ) // + rectangleCollisionLimitY
				{
					if (Character.getIsPlayer()) player1.setIsOnGround(true);
					if (player1.getIsOnGround())
					{
						player1.setVelocity({ player1.getVelocity().x,0.0f });
						player1.setIsJumping(false);
						
					}
					else
					{
						playerFootStep.stop();
					}
					cameraDown = false;
					Character.setGravity(false);
					Character.setIsOnWhichGround(i);
					Character.setPosition(Character.getRectangle().getPosition().x, levels[levelNumber].getRectangles(i).getPosition().y - (Character.getRectangle().getGlobalBounds().height) + GravityAndWallFix);
				}
				else
				{
					if (Character.getIsPlayer()) player1.setIsOnGround(false);
					if (Character.getIsOnWhichGround() == i) Character.setGravity(true);
					if (Character.getIsOnWhichLeftWall() == i) Character.setMoveRight(true);
					if (Character.getIsOnWhichRightWall() == i) Character.setMoveLeft(true);
					if (Character.getIsOnWhichCeiling() == i) Character.setMoveUp(true);
				}
			}
			else
			{
				if (Character.getIsOnWhichGround() == i) Character.setGravity(true);
				if (Character.getIsOnWhichRightWall() == i) Character.setMoveLeft(true);
				if (Character.getIsOnWhichLeftWall() == i) Character.setMoveRight(true);
				if (Character.getIsOnWhichCeiling() == i) Character.setMoveUp(true);

			}
		}

		static void CheckCollisionBetweenEnemies(int iFromEnemy)
		{
			for (int i = 0; i < maxEnemiesLevel1; i++)
			{
				if (i != iFromEnemy)
				{
					if (enemies[iFromEnemy].getRectangle().getGlobalBounds().intersects(enemies[i].getRectangle().getGlobalBounds()))
					{
						if (enemies[iFromEnemy].getRectangle().getPosition().x + enemies[iFromEnemy].getRectangle().getGlobalBounds().width > enemies[i].getRectangle().getPosition().x &&
							enemies[iFromEnemy].getRectangle().getPosition().x + enemies[iFromEnemy].getRectangle().getGlobalBounds().width < enemies[i].getRectangle().getPosition().x + rectangleCollisionLimitX)
						{
							enemies[iFromEnemy].setPosition(enemies[i].getRectangle().getPosition().x - (enemies[iFromEnemy].getRectangle().getGlobalBounds().width) + GravityAndWallFix, enemies[iFromEnemy].getRectangle().getPosition().y);
							enemies[iFromEnemy].setMoveRight(false);
							enemies[iFromEnemy].setIsOnWhichCharacterLeftSide(i);
						}


						if (enemies[iFromEnemy].getRectangle().getPosition().x < enemies[i].getRectangle().getPosition().x + enemies[i].getRectangle().getGlobalBounds().width &&
							enemies[iFromEnemy].getRectangle().getPosition().x > enemies[i].getRectangle().getPosition().x + enemies[i].getRectangle().getGlobalBounds().width - rectangleCollisionLimitX
							)
						{
							enemies[iFromEnemy].setPosition(enemies[i].getRectangle().getPosition().x + (enemies[i].getRectangle().getGlobalBounds().width) - GravityAndWallFix, enemies[iFromEnemy].getRectangle().getPosition().y);
							enemies[iFromEnemy].setMoveLeft(false);
							enemies[iFromEnemy].setIsOnWhichCharacterRightSide(i);
						}


						if (enemies[iFromEnemy].getRectangle().getPosition().y < enemies[i].getRectangle().getPosition().y + enemies[i].getRectangle().getGlobalBounds().height &&
							enemies[iFromEnemy].getRectangle().getPosition().y > enemies[i].getRectangle().getPosition().y + enemies[i].getRectangle().getGlobalBounds().height - rectangleCollisionLimitY)
						{
							enemies[iFromEnemy].setPosition(enemies[iFromEnemy].getRectangle().getPosition().x, enemies[i].getRectangle().getPosition().y + (enemies[i].getRectangle().getGlobalBounds().height));
							enemies[iFromEnemy].setMoveUp(false);
							enemies[iFromEnemy].setIsOnWhichCharacterDownSide(i);
						}


						if (enemies[iFromEnemy].getRectangle().getPosition().y + enemies[iFromEnemy].getRectangle().getGlobalBounds().height > enemies[i].getRectangle().getPosition().y &&
							enemies[iFromEnemy].getRectangle().getPosition().y + enemies[iFromEnemy].getRectangle().getGlobalBounds().height < enemies[i].getRectangle().getPosition().y + (enemies[i].getRectangle().getGlobalBounds().height / 2))
						{
							enemies[iFromEnemy].setPosition(enemies[iFromEnemy].getRectangle().getPosition().x, enemies[i].getRectangle().getPosition().y - (enemies[iFromEnemy].getRectangle().getGlobalBounds().height) );
							enemies[iFromEnemy].setGravity(false);
							enemies[iFromEnemy].setIsOnWhichCharacterTopSide(i);
						}
						else
						{
							enemies[iFromEnemy].setGravity(true);
						}
					}
					else
					{
						if (enemies[iFromEnemy].getIsOnWhichCharacterRightSide() == i) enemies[iFromEnemy].setMoveLeft(true);
						if (enemies[iFromEnemy].getIsOnWhichCharacterLeftSide() == i) enemies[iFromEnemy].setMoveRight(true);
						if (enemies[iFromEnemy].getIsOnWhichCharacterTopSide() == i) enemies[iFromEnemy].setGravity(true);
						if (enemies[iFromEnemy].getIsOnWhichCharacterDownSide() == i) enemies[iFromEnemy].setMoveUp(true);
					}
				}
			}
		}

		static void GunRotation()
		{
			//lineCollision.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width + 10,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 28 });
			gunLimit.setPosition({ player1.getRectangle().getPosition().x - 70,player1.getRectangle().getPosition().y - 70 });

			switch (currentWeapon)
			{
			case pistol:
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


				break;
			case shotgun:
				shotgunRectangle.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width / 2 ,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 30 });

				v1.x = 0;
				v1.y = 0.0f - shotgunRectangle.getPosition().y;

				v2.x = worldPos.x - shotgunRectangle.getPosition().x;
				v2.y = worldPos.y - shotgunRectangle.getPosition().y;

				prodVect = v1.x*v2.x + v1.y*v2.y;
				modv1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
				modv2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));

				angle = acos(prodVect / (modv1*modv2));
				angle *= (180 / 3.1415f);
				angle = angle + 270;
				if (worldPos.x < shotgunRectangle.getPosition().x)
				{
					angle = 180 - angle;
				}
				
				break;
			case 2:
				smgRectangle.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width / 2 ,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 15 });

				v1.x = 0;
				v1.y = 0.0f - smgRectangle.getPosition().y;

				v2.x = worldPos.x - smgRectangle.getPosition().x;
				v2.y = worldPos.y - smgRectangle.getPosition().y;

				prodVect = v1.x*v2.x + v1.y*v2.y;
				modv1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
				modv2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));

				angle = acos(prodVect / (modv1*modv2));
				angle *= (180 / 3.1415f);
				angle = angle + 270;
				if (worldPos.x < smgRectangle.getPosition().x)
				{
					angle = 180 - angle;
				}

				break;
			default:
				break;
			}

			gun.setRotation(angle);
			shotgunRectangle.setRotation(angle);
			smgRectangle.setRotation(angle);
			lineCollision.setRotation(angle);
			particlesShoot.setRotation(angle);
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
							zombieAttack.play();
							player1.setHp(player1.getHp() - 25);
							lifeBar.setSize({ lifeBar.getSize().x - 112.5f,lifeBar.getSize().y });
						}
					}
					enemy.setCurrentlyTouchingPlayer(false);

					if(enemy.getMoveRight()) animation.Update(0, deltaTime);

					if(enemy.getMoveLeft()) animation.Update(6, deltaTime);
					
				}
			}
			else
			{
				enemy.setCurrentlyTouchingPlayer(true);
			}
		}

		static void playerShoot()
		{
			if (player1.getCanShoot())
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!weapons[currentWeapon].isFireRateTimerRunning() && weapons[currentWeapon].getAmmo() > 0)
					{
						weapons[currentWeapon].playSound();
						weapons[currentWeapon].StartFireRateTimer();
						weapons[currentWeapon].setAmmo(weapons[currentWeapon].getAmmo() - 1);

						shootTimer.reset(shootInitialTime);
						shootTimer.start();
					}				
				}
			}
		}

		static void isCrosshairOnTarget(Character& enemy,int i)
		{	
			if (crosshairTest.getGlobalBounds().intersects(enemy.getRectangle().getGlobalBounds()))
			{
				if (enemy.getIsAlive())
				{
					crosshairTest.setFillColor(sf::Color::Green);
					inWhichEnemy = i;


					if (player1.getCanShoot() && canDealDamage)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (!weapons[currentWeapon].isFireRateTimerRunning() && weapons[currentWeapon].getAmmo() > 0)
							{
								zombiePain.play();
								weapons[currentWeapon].playSound();
								weapons[currentWeapon].StartFireRateTimer();
								weapons[currentWeapon].setAmmo(weapons[currentWeapon].getAmmo() - 1);
								enemy.setHp(enemy.getHp() - weapons[currentWeapon].getDamage());
								enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y);
								
								bloodTimer.reset(bloodInitialTime);
								bloodTimer.start();
								shootTimer.reset(shootInitialTime);
								shootTimer.start();
								currentEnemy = i;

								
								//particles.set
							}
						}
					}
				}
				else
				{
					if (inWhichEnemy == i)
					{
						crosshairTest.setFillColor(sf::Color::Red);
					}
				}
			}
			else
			{
				if (inWhichEnemy == i)
				{
					crosshairTest.setFillColor(sf::Color::Red);
				}
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
							zombieAlert.play();
						}

						if (enemy.getMoveRight())
						{
							enemy.setMove(enemySpeed * deltaTime, 0);
							animation.Update(3, deltaTime);
						}

						enemy.setFlipLeft(false);
						enemy.setFlipRight(true);

						enemy.setFaceRight(true);
						enemy.setFaceLeft(false);
					}
					

				}
				else if (player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width < enemy.getPlayerDetection().getPosition().x + enemy.getPlayerDetection().getGlobalBounds().width / 2)
				{
					if (enemy.getIsAlive())
					{
						if (enemy.getFlipRight())
						{
							zombieAlert.play();
						}

						

						if (enemy.getMoveLeft())
						{
							enemy.setMove(-(enemySpeed)* deltaTime, 0);
							animation.Update(7, deltaTime);
						}

						
						enemy.setFlipRight(false);
						enemy.setFlipLeft(true);

						enemy.setFaceLeft(true);
						enemy.setFaceRight(false);
					}
					
				}

				isCrosshairOnTarget(enemy,i);
			}
			else
			{
				if (enemy.getIsAlive())
				{
					enemy.getRectangle().move(0, 0);
					if(enemy.getMoveRight()) animation.Update(4, deltaTime);

					if (enemy.getMoveLeft()) animation.Update(2, deltaTime);
					
				}

				if (inWhichEnemy == i)
				{
					crosshairTest.setFillColor(sf::Color::Red);
				}
			}
		}


		static void CheckEnemyHP(Character& enemy,SpriteAnimation& animation,int i)
		{
			if (enemy.getHp()==75)
			{
				enemy.setColor({ 255,180,180,255 });
			}
			if (enemy.getHp() == 50)
			{
				enemy.setColor({ 255,100,100,255 });
			}
			if (enemy.getHp() == 25)
			{
				enemy.setColor({ 255,50,50,255 });
			}
			if (enemy.getHp() <= 0)
			{
				enemy.setIsAlive(false);
				enemy.setColor({ 170,0,0,255 });
			}

			if (enemy.getIsAlive())
			{
				enemy.setSize(enemy.getSize().x, enemy.getSize().y);
				enemy.setPlayerDetectionSize(enemy.getPlayerDetectionSize().x, enemy.getPlayerDetectionSize().y);
			}
			else
			{
				if (enemy.getFaceRight())
				{
					if (animation.UpdateOnce(1, deltaTime))
					{
						//thor::setRandomSeed(0);
						int RandomDropNumber = thor::random(0, 8); // change to consts

						zombieDeath.play();
						enemy.setSize(0, 0);
						enemy.setPlayerDetectionSize(0, 0);
						enemy.setIsAlive(true);
						enemy.setHp(defaultHP);
						enemy.setIsDead(true);

						switch (RandomDropNumber)
						{
						case 2:
							if (!pistolAmmo.getIsAlive())
							{
								pistolAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								pistolAmmo.setSize(100.0f, 70.0f);
								pistolAmmo.setIsAlive(true);
							}
							break;
						case 4:
							if (!medkitDrop.getIsAlive())
							{
								medkitDrop.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								medkitDrop.setSize(100.0f, 70.0f);
								medkitDrop.setIsAlive(true);
							}
							break;
						case 7:
							if (!smgAmmo.getIsAlive())
							{
								smgAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								smgAmmo.setSize(100.0f, 70.0f);
								smgAmmo.setIsAlive(true);
							}
							break;
						case 8:
							if (!shotgunAmmo.getIsAlive())
							{
								shotgunAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								shotgunAmmo.setSize(100.0f, 70.0f);
								shotgunAmmo.setIsAlive(true);
							}
							break;
						default:
							break;
						}

						//if (RandomDropNumber == 4) // change to consts
						//{
						//	
						//}
					}
				}
				else if (enemy.getFaceLeft())
				{
					if (animation.UpdateOnce(5, deltaTime))
					{
						//thor::setRandomSeed(0);
						int RandomDropNumber = thor::random(0, 8); // change to consts

						zombieDeath.play();
						enemy.setSize(0, 0);
						enemy.setPlayerDetectionSize(0, 0);
						enemy.setIsAlive(true);
						enemy.setHp(defaultHP);
						enemy.setIsDead(true);

						switch (RandomDropNumber)
						{
						case 2:
							if (!pistolAmmo.getIsAlive())
							{
								pistolAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								pistolAmmo.setSize(100.0f, 70.0f);
								pistolAmmo.setIsAlive(true);
							}
							break;
						case 4:
							if (!medkitDrop.getIsAlive())
							{
								medkitDrop.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								medkitDrop.setSize(100.0f, 70.0f);
								medkitDrop.setIsAlive(true);
							}
							break;
						case 7:
							if (!smgAmmo.getIsAlive())
							{
								smgAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								smgAmmo.setSize(100.0f, 70.0f);
								smgAmmo.setIsAlive(true);
							}
							break;
						case 8:
							if (!shotgunAmmo.getIsAlive())
							{
								shotgunAmmo.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
								shotgunAmmo.setSize(100.0f, 70.0f);
								shotgunAmmo.setIsAlive(true);
							}
							break;
						default:
							break;
						}

						
						//if (RandomDropNumber == 4) // change to consts
						//{
						//	if (!medkitDrop.getIsAlive())
						//	{
						//		medkitDrop.setPosition(enemy.getPosition().x, enemy.getPosition().y - 20);
						//		medkitDrop.setSize(100.0f, 70.0f);
						//		medkitDrop.setIsAlive(true);
						//	}
						//}
					}
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
				lineCollision.setPosition({ player1.getRectangle().getPosition().x - 30,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 28 });
				if (player1.getFlipLeft())
				{
					player1.setOrigin(static_cast<int>(player1.getRectangle().getGlobalBounds().width), 0);
					player1.scale(-1, 1);
					gun.setOrigin({ -20,40 });
					gun.scale(1, -1);
					shotgunRectangle.setOrigin({ -20,40 });
					shotgunRectangle.scale(1, -1);
					smgRectangle.setOrigin({ -20,40 });
					smgRectangle.scale(1, -1);
					
				}
				player1.setFlipLeft(false);
				player1.setFlipRight(true);
			}
			else
			{
				lineCollision.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width + 30,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 28 });
				if (player1.getFlipRight())
				{
					player1.setOrigin(0, 0 );
					player1.scale(-1, 1);
					gun.setOrigin({ -20, 40 });
					gun.scale(1, -1);
					shotgunRectangle.setOrigin({ -20, 40 });
					shotgunRectangle.scale(1, -1);
					smgRectangle.setOrigin({ -20, 40 });
					smgRectangle.scale(1, -1);
				}
				player1.setFlipRight(false);
				player1.setFlipLeft(true);
			}
		}

		static void HUDUpdate()
		{

			lifeBar.setPosition(sf::Vector2f(view.getCenter().x - 1232, view.getCenter().y - 700));
			lifeHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 1300, view.getCenter().y - 800));
			weaponHUDRectangle.setPosition(sf::Vector2f(view.getCenter().x - 700, view.getCenter().y - 800));
			bulletsText.setPosition(sf::Vector2f(view.getCenter().x - 450, view.getCenter().y - 625));
			zombiesKilledText.setPosition(sf::Vector2f(view.getCenter().x + 300, view.getCenter().y - 800));
			pistolRectangle.setPosition(sf::Vector2f(view.getCenter().x - 530, view.getCenter().y - 720));
			shotgunHUD.setPosition(sf::Vector2f(view.getCenter().x - 530, view.getCenter().y - 720));
			smgHUD.setPosition(sf::Vector2f(view.getCenter().x - 530, view.getCenter().y - 720));

			zombiesKilledText.setString("Zombies Killed: " + toString(zombiesKilled));

			for (int i = 0; i < maxEnemiesLevel1; i++)
			{
				if (enemies[i].getHp() < 0)
				{
					enemies[i].setHp(0);
				}
			}

			crosshairTest.setPosition(worldPos.x - 30, worldPos.y - 30);
		}

		static void CheckPlayerGravity()
		{
			if (player1.getGravity())
			{
				player1.setPosition(player1.getRectangle().getPosition().x, (player1.getRectangle().getPosition().y + (gravitySpeed * deltaTime)));
				cameraUp = false;
			}
		}

		static void CheckCharacterGravity(Character& character)
		{
			if (character.getGravity())
			{
				character.setPosition(character.getRectangle().getPosition().x, character.getRectangle().getPosition().y + (character.getSpeed().y * deltaTime));
			}
		}

		//WIP Function
		static void CheckWeaponsFireRate(weapon& weapon)
		{
			//if (weaponFireRate.isExpired())
			if(weapon.isFireRateTimerExpired())
			{
				switch (currentWeapon)
				{
				case 0:
					pistolAnimation.SetSingleFrame(sf::Vector2u(0, 0));
					weapon.setFireRateTimer(pistolFireRate);
					break;
				case 1:
					shotgunAnimation.SetSingleFrame(sf::Vector2u(0, 0));
					weapon.setFireRateTimer(shotgunFireRate);
					break;
				case 2:
					smgAnimation.SetSingleFrame(sf::Vector2u(0, 0));
					weapon.setFireRateTimer(smgFireRate);
					break;
				default:
					break;
				}
				
				//weaponFireRate.reset(pistolFireRate);
			}
			//else if (weaponFireRate.isRunning())
			else if(weapon.isFireRateTimerRunning())
			{
				switch (currentWeapon)
				{
				case 0:
					pistolAnimation.UpdateY(pistolShoot, deltaTime);
					break;
				case 1:
					shotgunAnimation.Update(0, deltaTime);
					break;
				case 2:
					smgAnimation.Update(0, deltaTime);
					break;
				default:
					break;
				}
				
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


		static void CheckWinCondition()
		{
			if (zombiesKilled >= levels[levelNumber].getEnemyKillObjetive())
			{
				zombiesKilledText.setFillColor(sf::Color::Green);
			}

			if (player1.getRectangle().getGlobalBounds().intersects(Exit.getGlobalBounds()) && zombiesKilled >= levels[levelNumber].getEnemyKillObjetive())
			{
				playerWon = true;
				playerLost = false;
				gameOnPause = true;
			}
		}

		static void CheckLossCondition()
		{
			if (player1.getHp() <= 0)
			{
				player1.setIsAlive(false);
			}

			if (!player1.getIsAlive())
			{
				playerLost = true;
				playerWon = false;
				gameOnPause = true;
			}
		}

		static void CheckMedkitCollisionWithPlayer(Character& medkit)
		{
			if (player1.getRectangle().getGlobalBounds().intersects(medkit.getRectangle().getGlobalBounds()))
			{
				player1.setHp(player1.getHp() + 25);
				lifeBar.setSize({ lifeBar.getSize().x + 112.5f,lifeBar.getSize().y });
				if (player1.getHp() > 100)
				{
					player1.setHp(defaultHP);
					lifeBar.setSize({ 450,lifeBar.getSize().y });
				}
				medkit.setSize(0, 0);
				medkit.setIsAlive(false);

				playerHeal.play();
			}
		}

		static void CheckAmmoCollisionWithPlayer()
		{
			if (player1.getRectangle().getGlobalBounds().intersects(pistolAmmo.getRectangle().getGlobalBounds()))
			{
				weapons[pistol].setAmmo(weapons[pistol].getAmmo() + 12);
				if (weapons[pistol].getAmmo() >= 100)
				{
					weapons[pistol].setAmmo(100);
				}
				pistolAmmo.setSize(0, 0);
				pistolAmmo.setIsAlive(false);
				ammoPickupSound.play();
			}

			if (player1.getRectangle().getGlobalBounds().intersects(smgAmmo.getRectangle().getGlobalBounds()))
			{
				weapons[smg].setAmmo(weapons[smg].getAmmo() + 50);
				if (weapons[smg].getAmmo() >= 400)
				{
					weapons[smg].setAmmo(400);
				}
				smgAmmo.setSize(0, 0);
				smgAmmo.setIsAlive(false);
				ammoPickupSound.play();
			}

			if (player1.getRectangle().getGlobalBounds().intersects(shotgunAmmo.getRectangle().getGlobalBounds()))
			{
				weapons[shotgun].setAmmo(weapons[shotgun].getAmmo() + 6);
				if (weapons[shotgun].getAmmo() >= 50)
				{
					weapons[shotgun].setAmmo(50);
				}
				shotgunAmmo.setSize(0, 0);
				shotgunAmmo.setIsAlive(false);
				ammoPickupSound.play();
			}
		}

		//-------END Gameplay Functions

		void GameplayScreen::update()
		{
			if (!gameOnPause)
			{


				


				_window.setMouseCursorVisible(false);
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


				//// Items




				// Ammo Count

				bulletsText.setString(toString(weapons[currentWeapon].getAmmo()));

				for (int i = 0; i < maxMedkitsFloor; i++)
				{
					CheckCharacterGravity(medkitFloor[i]);

					CheckMedkitCollisionWithPlayer(medkitFloor[i]);
				}

				CheckCharacterGravity(medkitDrop);
				CheckCharacterGravity(pistolAmmo);
				CheckCharacterGravity(smgAmmo);
				CheckCharacterGravity(shotgunAmmo);


				CheckMedkitCollisionWithPlayer(medkitDrop);
				CheckAmmoCollisionWithPlayer();


				////// Characters

				if (player1.getIsJumping())
				{
					player1.setGravity(true);
				}

				player1.setTextureRect(playerAnimation.uvRect);
				gun.setTextureRect(pistolAnimation.uvRect);
				shotgunRectangle.setTextureRect(shotgunAnimation.uvRect);
				smgRectangle.setTextureRect(smgAnimation.uvRect);


				for (int i = 0; i < maxEnemiesLevel1; i++)
				{
					enemies[i].setTextureRect(zombiesAnimation[i].uvRect);

					CheckInvincibilityFrames(timerInvincibility, i);

					CheckCharacterGravity(enemies[i]);

					enemies[i].setPlayerDetectionPosition(enemies[i].getRectangle().getPosition().x - 500, enemies[i].getRectangle().getPosition().y - 190);

					PlayerEnemyCollision(enemies[i], timerInvincibility, zombiesAnimation[i]);

					CheckEnemyHP(enemies[i], zombiesAnimation[i], i);

					CanEnemyHearPlayer(enemies[i], zombiesAnimation[i], i);

					CheckCollisionBetweenEnemies(i);

					//particles.setEmitter(enemies[i].getPosition());
				}

				playerShoot();

				// gravity
				CheckPlayerGravity();


				// Jump
				player1.updateJump(deltaTime);

				CheckWeaponsFireRate(weapons[currentWeapon]);

				player1.getRectangle().move(player1.getMove());

				CheckPlayerFlipSprite();

				GunRotation();

				// Checks for collisions

				for (int i = 0; i < levels[levelNumber].getRectanglesInLevel(); i++)
				{
					if (lineCollision.getGlobalBounds().intersects(levels[levelNumber].getRectangles(i).getGlobalBounds()))
					{
						crosshairTest.setFillColor(transparentRed);
						canDealDamage = false;
						inWhichRectangle = i;
					}
					else
					{
						if (inWhichRectangle == i)
						{
							canDealDamage = true;
						}
					}


					CheckCollisionWithTiles(player1, i);
					for (int f = 0; f < maxEnemiesLevel1; f++)
					{
						CheckCollisionWithTiles(enemies[f], i);
					}

					for (int c = 0; c < maxMedkitsFloor; c++)
					{
						CheckCollisionWithTiles(medkitFloor[c], i);
					}


					CheckCollisionWithTiles(medkitDrop, i);

					CheckCollisionWithTiles(pistolAmmo, i);
					CheckCollisionWithTiles(smgAmmo, i);
					CheckCollisionWithTiles(shotgunAmmo, i);
				}

				// Check Winning Condition
				CheckWinCondition();

				// Check Losing Condition
				CheckLossCondition();

				//Audio
				if (footstepTimer.isExpired())
				{
					footstepTimer.reset(footstepInitialTime);
				}

				//Particles

				if (bloodTimer.isRunning())
				{
					particles.setEmitter({ enemies[currentEnemy].getPosition().x + 45, enemies[currentEnemy].getPosition().y + 45 });
				}

				if (bloodTimer.isExpired())
				{
					bloodTimer.reset(bloodInitialTime);
					particles.setEmitter(bloodDisablePosition);
				}

				if (shootTimer.isRunning())
				{
					particlesShoot.setPosition({ player1.getRectangle().getPosition().x + player1.getRectangle().getGlobalBounds().width / 2 ,player1.getRectangle().getPosition().y + player1.getRectangle().getGlobalBounds().height / 2 - 15 });
					particlesShoot.setEmitter({ shotgunRectangle.getGlobalBounds().width,0.f });
				}

				if (shootTimer.isExpired())
				{
					shootTimer.reset(shootInitialTime);
					particlesShoot.setEmitter(shootDisablePosition);
					particlesShoot.setRotation(0.f);
				}

				particles.update(sf::seconds(deltaTime));
				particlesShoot.update(sf::seconds(deltaTime));
				particles.setColor(sf::Color::Red);
				particlesShoot.setColor(shotParticlesColor);
			}
			else if (gameOnPause)
			{
				_window.setMouseCursorVisible(true);
				//Setting the pause buttons ON
				for (int i = 0; i < maxButtons; i++)
				{
					buttons[i]->setVisible(true);
				}

				if (playerWon)
				{
					buttons[0]->setVisible(false);
					playerStateText.setFillColor(sf::Color::Green);
					playerStateText.setString("You Passed the level!");
					playerStateText.setPosition(sf::Vector2f(view.getCenter().x - 300, view.getCenter().y - 600));
				}

				if (playerLost)
				{
					buttons[0]->setVisible(false);
					playerStateText.setFillColor(sf::Color::Red);
					playerStateText.setString("You died!");
					playerStateText.setPosition(sf::Vector2f(view.getCenter().x - 200, view.getCenter().y - 600));
				}

			}
			
			
			
		}

		void GameplayScreen::draw()
		{
			// Draw Tilemap with its collision objects
			for (int i = 0; i < levels[levelNumber].getRectanglesInLevel(); i++)
			{
				_window.draw(levels[levelNumber].getRectangles(i));
			}

			switch (levelNumber)
			{
			case 0:
				_window.draw(map);
				break;
			case 1:
				_window.draw(map2);
				break;
			default:
				break;
			}

			_window.draw(Exit);
			
			////---------------------
			// Sprites / Shapes

			_window.draw(lineCollision);

			//// Player
			_window.draw(player1.getRectangle());

			//// Enemy
			for (int i = 0; i < maxEnemiesLevel1; i++)
			{
				_window.draw(enemies[i].getPlayerDetection());
				_window.draw(enemies[i].getRectangle());
			}

			//Items

			for (int i = 0; i < maxMedkitsFloor; i++)
			{
				_window.draw(medkitFloor[i].getRectangle());
			}

			_window.draw(medkitDrop.getRectangle());

			_window.draw(pistolAmmo.getRectangle());
			_window.draw(smgAmmo.getRectangle());
			_window.draw(shotgunAmmo.getRectangle());
			////---------------------

			// Text
			if (levelNumber == 0)
			{
				for (int i = 0; i < maxTutorialTexts; i++)
				{
					_window.draw(tutorialText[i]);
				}
			}
			_window.draw(playerStateText);
			

			// HUD
			_window.draw(crosshairTest);
			_window.draw(lifeBar);
			_window.draw(lifeHUDRectangle);
			_window.draw(weaponHUDRectangle);
			

			_window.draw(zombiesKilledText);
			_window.draw(crosshairTest);
			//
			_window.draw(bulletsText);

			switch (currentWeapon)
			{
			case pistol:
				_window.draw(pistolRectangle);
				_window.draw(gun);
				break;
			case shotgun:
				_window.draw(shotgunHUD);
				_window.draw(shotgunRectangle);
				break;
			case 2:
				_window.draw(smgHUD);
				_window.draw(smgRectangle);
				break;
			default:
				break;
			}

			_window.draw(particles);
			_window.draw(particlesShoot);		
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

			level0Ambience.stop();
			level1Ambience.stop();
			tutorialSong.stop();
			level1Song.stop();
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