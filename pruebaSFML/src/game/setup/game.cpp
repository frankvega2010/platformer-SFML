#include "game.h"

#include <iostream>

#include "Screens/gameplay.h"
#include "Screens/menu.h"
#include "Screens/gameover.h"
#include "Screens/settings.h"
#include "Screens/credits.h"
#include "setup/screens.h"


using namespace newgame;
using namespace Gameplay_Section;
using namespace GameOver_Section;
using namespace Menu_Section;
using namespace Settings_Section;
using namespace Credits_Section;

namespace newgame
{

	static bool gameON = true;

	static sf::Event event;

	int globalSoundVolume;
	int globalMusicVolume;
	int levelNumber;
	int Game::_buttonOption = 0;
	float Game::_defaultFontSize = 0;
	float Game::_defaultFontSizeGameplayScore = 0;
	float Game::_defaultFontSizeGameplayText = 0;
	int Game::_gameScreen = 0;
	int Game::_screenHeight = 0;
	int Game::_screenWidth = 0;
	int Game::_newScreenHeight = 0;
	int Game::_newScreenWidth = 0;
	bool Game::_isKeyPressed = false;
	int Game::_defaultStyle = 0;

	Screens* gameScreens[MaxGameScreens];

	sf::RenderWindow _window;

	tgui::Gui gui{ _window };

	sf::Clock deltaClock;
	float deltaTime;
	sf::Music menuSong;

	sf::Texture background;
	sf::Sprite backgroundSprite;


	Game::Game()
	{
		_defaultStyle = sf::Style::Default;
		_screenHeight = 0;
		_screenWidth = 0;

		_buttonOption = 0;

		_defaultFontSize = 60;
		_defaultFontSizeGameplayText = 0;
		_defaultFontSizeGameplayScore = 0;

		setScreenWidth(1920);
		setScreenHeight(1080);
		
		_window.create(sf::VideoMode(getScreenWidth(), getScreenHeight()), "Patient Zero", _defaultStyle);
		Game::setNewScreenWidth(1440);
		Game::setNewScreenHeight(900);
		_window.setPosition(sf::Vector2i(Game::getNewScreenWidth()/16, Game::getNewScreenHeight() /16));
		_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
	}

	Game::~Game()
	{

	}

	void Game::setScreenWidth(int screenWidth)
	{
		_screenWidth = screenWidth;
	}

	int Game::getScreenWidth()
	{
		return _screenWidth;
	}

	void Game::setScreenHeight(int screenHeight)
	{
		_screenHeight = screenHeight;
	}

	int Game::getScreenHeight()
	{
		return _screenHeight;
	}

	void Game::setNewScreenWidth(int screenWidth)
	{
		_newScreenWidth = screenWidth;
	}

	int Game::getNewScreenWidth()
	{
		return _newScreenWidth;
	}

	void Game::setNewScreenHeight(int screenHeight)
	{
		_newScreenHeight = screenHeight;
	}

	int Game::getNewScreenHeight()
	{
		return _newScreenHeight;
	}

	void Game::setGameScreen(int gameScreen)
	{
		_gameScreen = gameScreen;
	}

	int Game::getGameScreen()
	{
		return _gameScreen;
	}

	float Game::getDefaultFontSize()
	{
		return _defaultFontSize;
	}

	float Game::getDefaultFontSizeGameplayText()
	{
		return _defaultFontSizeGameplayText;
	}

	float Game::getDefaultFontSizeGameplayScore()
	{
		return _defaultFontSizeGameplayScore;
	}

	int Game::getButtonOption()
	{
		return _buttonOption;
	}

	void Game::setButtonOption(int buttonOption)
	{
		_buttonOption = buttonOption;
	}

	bool Game::getIsKeyPressed()
	{
		return _isKeyPressed;
	}

	void Game::setIsKeyPressed(bool isKeyPressed)
	{
		_isKeyPressed = isKeyPressed;
	}

	int Game::getDefaultStyle()
	{
		return _defaultStyle;
	}
	void Game::setDefaultStyle(int DefaultStyle)
	{
		_defaultStyle = DefaultStyle;
	}

	

	void Game::init()
	{
		background.loadFromFile("res/assets/textures/background.png");
		backgroundSprite.setTexture(background);

		_window.setActive();
	
		globalSoundVolume = 40;
		globalMusicVolume = 40;
		

		for (int i = 0; i < MaxGameScreens; i++)
		{
			gameScreens[i] = NULL;
		}

		gameScreens[Menu] = new MenuScreen();
		gameScreens[Play] = new GameplayScreen();
		gameScreens[Settings] = new SettingsScreen();
		gameScreens[GameOver] = new GameOverScreen();
		gameScreens[Credits] = new CreditsScreen();

		_gameScreen = Menu;
		gameScreens[Menu]->init();

		menuSong.openFromFile("res/assets/music/menuSong.wav");
		menuSong.setLoop(true);
		menuSong.setVolume(static_cast<float>(globalMusicVolume));
		menuSong.play();
	}

	void Game::update()
	{
		menuSong.setVolume(static_cast<float>(globalMusicVolume));
		switch (_gameScreen)
		{
		case Menu:
		{
			gameScreens[Menu]->update();

			if (gameScreens[Menu]->finish())
			{
				gameScreens[Menu]->deInit();
				switch (_buttonOption)
				{
				case buttonPlay:
				{
					levelNumber = 1;
					_gameScreen = Play;
					gameScreens[Play]->init();
					break;
				}
				case buttonSettings:
				{
					_gameScreen = Settings;
					gameScreens[Settings]->init();
					break;
				}
				case buttonCredits:
				{
					_gameScreen = Credits;
					gameScreens[Credits]->init();
					break;
				}
				case buttonTutorial:
				{
					levelNumber = 0;
					_gameScreen = Play;
					gameScreens[Play]->init();
					break;
				}
				case buttonQuit:
				{
					gameON = false;
					return;
					break;
				}
				}
			}
		}
		break;
		case Settings:
		{
			gameScreens[Settings]->update();

			if (gameScreens[Settings]->finish())
			{
				gameScreens[Settings]->deInit();
				switch (_buttonOption)
				{
				case buttonMenu:
				{
					_gameScreen = Menu;
					gameScreens[Menu]->init();
					break;
				}
				}
			}
		}
		break;

		case GameOver:
		{
			gameScreens[GameOver]->update();

			if (gameScreens[GameOver]->finish())
			{
				gameScreens[GameOver]->deInit();
				switch (_buttonOption)
				{
				case buttonMenu:
				{

					_gameScreen = Menu;
					gameScreens[Menu]->init();
					break;
				}
				case buttonRestart:
				{
					_gameScreen = Play;
					gameScreens[Play]->init();
					break;
				}
				}
			}
		}
		break;

		case Play:
		{
			menuSong.stop();
			gameScreens[Play]->update();

			if (gameScreens[Play]->finish())
			{
				gameScreens[Play]->deInit();
				switch (_buttonOption)
				{
				case buttonMenu:
				{

					_gameScreen = Menu;
					gameScreens[Menu]->init();
					break;
				}
				case buttonRestart:
				{
					_gameScreen = Play;
					gameScreens[Play]->init();
					break;
				}
				case buttonGameOver:
				{
					_gameScreen = GameOver;
					gameScreens[GameOver]->init();
					break;
				}
				}
				menuSong.play();
			}
		}
		break;
		case Credits:
		{
			gameScreens[Credits]->update();

			if (gameScreens[Credits]->finish())
			{
				gameScreens[Credits]->deInit();
				_gameScreen = Menu;
				gameScreens[Menu]->init();
			}
		}
		break;
		}
		
	}

	void Game::draw()
	{
		_window.clear(sf::Color::Black);

		gameScreens[_gameScreen]->draw();

		
		gui.draw();
		
		_window.display();
	}

	void Game::deInit()
	{
		for (int i = 0; i < MaxGameScreens; i++)
		{
			delete gameScreens[i];
			gameScreens[i] = NULL;
		}
	}

	void Game::execute()
	{
		init();
		while (_window.isOpen())
		{
			deltaTime = deltaClock.restart().asSeconds();
			if (deltaTime> 1.0f / 20.0f)
			{
				deltaTime = 1.0f / 20.0f;
			}
			while (_window.pollEvent(event))
			{

				 //"close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					_window.close();

				gui.handleEvent(event);
			}

			update();
			if (!(gameON)) _window.close();
			draw();
			
		}
		deInit();
	}
}