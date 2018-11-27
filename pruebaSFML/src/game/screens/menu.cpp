#include "menu.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "Thor/Shapes.hpp"
#include "Thor/Time.hpp"

#include <sstream>
#include <string>


using namespace Game_Namespace;
using namespace std;
//using namespace string;
using namespace thor::Shapes;

namespace Game_Namespace
{
	static const int maxButtons = 5;

	sf::Font font;

	sf::Text menuTitle;
	sf::Text menuSubTitle1;
	sf::Text menuSubTitle2;

	sf::Text menuText;

	sf::RectangleShape testS;

	//thor::Timer timertest;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr buttons[maxButtons];

	//static tgui::Button::Ptr button = tgui::Button::create();

	

	namespace Menu_Section
	{

		string toString(sf::Time value)
		{
			std::ostringstream stream;
			stream.setf(std::ios_base::fixed);
			stream.precision(1);
			stream << value.asSeconds();
			return stream.str();
		}

		MenuScreen::MenuScreen()
		{
		}

		MenuScreen::~MenuScreen()
		{
		}

		static void signalGoToSettings()
		{
			Game::setButtonOption(buttonSettings);
			Screens::setHasScreenFinished(true);
		}

		static void signalQuitGame()
		{
			Game::setButtonOption(buttonQuit);
			Screens::setHasScreenFinished(true);
		}

		static void signalGoToPlay()
		{
			Game::setButtonOption(buttonPlay);
			Screens::setHasScreenFinished(true);
		}

		static void signalGoToCredits()
		{
			Game::setButtonOption(buttonCredits);
			Screens::setHasScreenFinished(true);
		}

		static void signalGoToControls()
		{
			/*Game::setButtonOption(buttonControls);
			Screens::setHasScreenFinished(true);*/
		}

		void MenuScreen::init()
		{
			
			//_window.setView(windowView);
			testS.setPosition(0, 0);
			testS.setSize(sf::Vector2f(1280,800));
			testS.setFillColor(sf::Color::Red);

			int maxDistance = 0;
			int maxDistance2 = 0;
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i] = tgui::Button::create();
				gui.add(buttons[i]);
				buttons[i]->setRenderer(blackTheme.getRenderer("Button"));
				buttons[i]->setSize(240, 100);
				buttons[i]->setTextSize(50);// 240 100

				if (i < 3)
				{
					buttons[i]->setPosition(120 + maxDistance, Game::getScreenHeight() / 2); // (Game::getScreenWidth()/2 + 10 - 260)
				}
				else
				{
					buttons[i]->setPosition(180 + maxDistance2, Game::getScreenHeight() / 2 + 200); // (Game::getScreenWidth()/2 + 10 - 260)
					maxDistance2 = maxDistance2 + 350;
				}
				

				maxDistance = maxDistance + 250;
			}
			maxDistance = 0;

			buttons[0]->setText("Play");
			buttons[1]->setText("Tutorial");
			buttons[2]->setText("Settings");
			buttons[3]->setText("Credits");
			buttons[4]->setText("Quit");

			if (!font.loadFromFile("res/assets/fonts/sansation.ttf"))
			{
				cout << "could not load font file" << endl;// error...
			}

			menuTitle.setFont(font);
			menuTitle.setCharacterSize(static_cast<int>(Game::getDefaultFontSize() * 2.f));
			menuTitle.setFillColor(sf::Color::Red);
			menuTitle.setPosition((Game::getScreenWidth() / 2.f - 400.f), 50.f);
			menuTitle.setString("Patient Zero");

			menuSubTitle1.setFont(font);
			menuSubTitle1.setCharacterSize(static_cast<int>(Game::getDefaultFontSize() - 20));
			menuSubTitle1.setFillColor(sf::Color::Red);
			menuSubTitle1.setPosition(menuTitle.getPosition().x + 300, 140);
			menuSubTitle1.setString("");

			menuSubTitle2.setFont(font);
			menuSubTitle2.setCharacterSize(static_cast<int>(Game::getDefaultFontSize() - 20));
			menuSubTitle2.setFillColor(sf::Color::Red);
			menuSubTitle2.setPosition(menuTitle.getPosition().x + 200, 180);
			menuSubTitle2.setString("Version 0.1");

			buttons[0]->connect("Pressed", signalGoToPlay);
			buttons[1]->connect("Pressed", signalGoToControls);
			buttons[2]->connect("Pressed", signalGoToSettings);
			buttons[3]->connect("Pressed", signalGoToCredits);
			buttons[4]->connect("Pressed", signalQuitGame);

			//sf::Time initialTime = sf::seconds(10);
			//timertest.reset(initialTime);
			//timertest.start();
			setHasScreenFinished(false);
		}

		void MenuScreen::input()
		{
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!(Game::getIsKeyPressed()))
				{
					Game::setButtonOption(buttonPlay);
					Screens::setHasScreenFinished(true);
				}
			}
			else
			{
				Game::setIsKeyPressed(false);
			}*/
		}

		void MenuScreen::update()
		{
			#ifdef AUDIO
						UpdateMusicStream(pong_menu_song);
			#endif
			input();
		}

		void MenuScreen::draw()
		{


			
			_window.draw(menuTitle);
			_window.draw(menuSubTitle1);
			_window.draw(menuSubTitle2);
			//_window.draw(testS);
			
		}

		void MenuScreen::deInit()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i]->setVisible(false);
			}
		}

		bool MenuScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}