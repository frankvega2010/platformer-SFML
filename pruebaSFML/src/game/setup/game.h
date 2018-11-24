#ifndef GAME_H
#define GAME_H


//#include <iostream>


#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "TGUI/TGUI.hpp"

#include "Screens/gameplay.h"
#include "Screens/menu.h"
#include "Screens/gameover.h"
#include "Screens/settings.h"
#include "Screens/credits.h"
#include "Screens/controls.h"
#include "setup/screens.h"

//#include "raylib.h"

namespace Game_Namespace
{
	enum GameScreens
	{
		Play = 1,
		Menu,
		Controls,
		GameOver,
		Quit,
		Credits,
		Settings,
		MaxGameScreens
	};

	//extern sf::RenderWindow window;
	extern sf::RenderWindow _window;
	extern tgui::Gui gui;
	//extern sf::View windowView;
	//extern sf::View windowView2;

	class Game 
	{
	private:
		static int _screenWidth;
		static int _screenHeight;
		static int _newScreenWidth;
		static int _newScreenHeight;
		static int _gameScreen;
		static float _defaultFontSize;
		static float _defaultFontSizeGameplayText;
		static float _defaultFontSizeGameplayScore;
		static int _buttonOption;
		static bool _isKeyPressed;
		static int _defaultStyle;
	public:
		
		Game();
		~Game();
		static void setScreenWidth(int screenWidth);
		static int getScreenWidth();
		static void setScreenHeight(int screenHeight);
		static int getScreenHeight();
		static void setNewScreenWidth(int screenWidth);
		static int getNewScreenWidth();
		static void setNewScreenHeight(int screenHeight);
		static int getNewScreenHeight();
		static int getGameScreen();
		static void setGameScreen(int gameScreen);
		static float getDefaultFontSize();
		float getDefaultFontSizeGameplayText();
		float getDefaultFontSizeGameplayScore();
		static int getButtonOption();
		static void setButtonOption(int buttonOption);
		static bool getIsKeyPressed();
		static void setIsKeyPressed(bool isKeyPressed);
		static int getDefaultStyle();
		static void setDefaultStyle(int DefaultStyle);
		void init();
		void update();
		void draw();
		void deInit();
		void execute();
	};

	

	extern bool isScreenFinished;

	extern int selectOption;

	extern sf::Clock deltaClock;
	extern sf::Time deltaTime;

	//extern Sound pong_hit_wall;
	//extern Sound pong_hit_player;
	//extern Sound pong_player_scored;
	//extern Sound pong_match_end;
	//extern Sound pong_select_menu;
	//extern Sound pong_select_option1;
	//extern Sound pong_select_option2;

	//extern Music pong_menu_song;

	//void Execute();
}
#endif // GAME_H