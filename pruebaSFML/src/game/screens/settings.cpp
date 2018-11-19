#include "settings.h"

//#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtons = 5;

//	static const int Menu = 6;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr buttons[maxButtons];

	namespace Settings_Section
	{
		SettingsScreen::SettingsScreen()
		{
		}

		SettingsScreen::~SettingsScreen()
		{
		}

		static void signalGoToMenu()
		{
			Screens::setHasScreenFinished(true);
		}

		static void signalChangeTo800x600()
		{
			//Game::setScreenWidth(800);
			//Game::setScreenHeight(600);
			//_window.setSize(sf::Vector2u(Game::getScreenWidth(), Game::getScreenHeight()));
			//windowView.setCenter(0, 0);
			//windowView.setSize(800, 600);
			//_window.setView(windowView2);
			//windowView.setSize(sf::Vector2f(1600, 1200));



			//windowView.setSize(sf::FloatRect(0, 0, 800, 600));


			//_window.setView(windowView);



			//sf::RenderWindow* _window = new sf::RenderWindow();
			//_window.create(sf::VideoMode(getScreenWidth(), getScreenHeight()), "SFML Template");

			//_window.
			//_window.setPosition(sf::Vector2i(600, 600));
			
		}

		static void signalChangeTo1280x800()
		{
			//Game::setScreenWidth(1280);
			//Game::setScreenHeight(800);
			//_window.setSize(sf::Vector2u(Game::getScreenWidth(), Game::getScreenHeight()));
			//windowView.setCenter(0, 0);
			//windowView.setSize(1280, 800);
			//_window.setView(windowView);
			//_window.setView(windowView);
		}

		void SettingsScreen::init()
		{
			int maxDistance = 0;
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i] = tgui::Button::create();
				gui.add(buttons[i]);
				buttons[i]->setRenderer(blackTheme.getRenderer("Button"));
				buttons[i]->setSize(240, 100);
				buttons[i]->setTextSize(50);// 240 100

				buttons[i]->setPosition(120 , 200 + maxDistance);

				maxDistance = maxDistance + 120;
			}
			maxDistance = 0;

			buttons[0]->setText("800x600");
			buttons[1]->setText("1280x800");
			buttons[2]->setText("Resolution3");
			buttons[3]->setText("Resolution4");
			buttons[4]->setText("Menu");

			buttons[0]->connect("Pressed", signalChangeTo800x600);
			buttons[1]->connect("Pressed", signalChangeTo1280x800);
			buttons[4]->connect("Pressed", signalGoToMenu);

			setHasScreenFinished(false);
		}

		void SettingsScreen::input()
		{

		}

		void SettingsScreen::update()
		{

			input();
		}

		void SettingsScreen::draw()
		{

		}

		void SettingsScreen::deInit()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i]->setVisible(false);
			}
		}

		bool SettingsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}