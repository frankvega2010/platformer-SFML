#include "settings.h"

#include "Screens/gameplay.h"
#include "Screens/menu.h"

using namespace newgame;
using namespace Gameplay_Section;

namespace newgame
{
	static const int maxButtons = 7;

	static const int maxSlidersAndLabels = 2;

	static const int guiXPosition = 500;

	static const int guiTextSize = 50;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr buttons[maxButtons];

	static tgui::Slider::Ptr sliders[maxSlidersAndLabels];

	static tgui::Label::Ptr labels[maxSlidersAndLabels];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	static pugi::xml_document config;
	static pugi::xml_parse_result configResult = config.load_file("res/assets/config/config.xml");
	static pugi::xml_node configVolume = config.child("settings").child("volume");
	static pugi::xml_node configResolution = config.child("settings").child("res");

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
			Game::setButtonOption(buttonMenu);
			Screens::setHasScreenFinished(true);
		}

		static void signalChangeTo800x600()
		{
			Game::setNewScreenWidth(800);
			Game::setNewScreenHeight(600);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
			if (Game::getDefaultStyle() == sf::Style::Fullscreen)
			{
				_window.create(sf::VideoMode(Game::getScreenWidth(), Game::getScreenHeight()), "SFML Template", Game::getDefaultStyle());
			}
				
		}

		static void signalChangeTo1024x768()
		{
			Game::setNewScreenWidth(1024);
			Game::setNewScreenHeight(768);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
		}


		static void signalChangeTo1280x720()
		{
			Game::setNewScreenWidth(1280);
			Game::setNewScreenHeight(720);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
		}

		static void signalChangeTo1440x900()
		{
			Game::setNewScreenWidth(1440);
			Game::setNewScreenHeight(900);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
			if (Game::getDefaultStyle() == sf::Style::Fullscreen)
			{
				_window.create(sf::VideoMode(Game::getScreenWidth(), Game::getScreenHeight()), "SFML Template", Game::getDefaultStyle());
			}
		}

		static void signalChangeTo1600x900()
		{
			Game::setNewScreenWidth(1600);
			Game::setNewScreenHeight(900);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
			if (Game::getDefaultStyle() == sf::Style::Fullscreen)
			{
				_window.create(sf::VideoMode(Game::getScreenWidth(), Game::getScreenHeight()), "SFML Template", Game::getDefaultStyle());
			}
		}

		static void signalChangeTo1920x1080()
		{
			Game::setNewScreenWidth(1920);
			Game::setNewScreenHeight(1080);
			_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
			if (Game::getDefaultStyle() == sf::Style::Fullscreen)
			{
				_window.create(sf::VideoMode(Game::getScreenWidth(), Game::getScreenHeight()), "SFML Template", Game::getDefaultStyle());
			}
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
				buttons[i]->setTextSize(40);
				buttons[i]->setInheritedFont(fontButtons);
				buttons[i]->setPosition(50 , 70 + maxDistance);

				maxDistance = maxDistance + 130;
			}
			maxDistance = 0;

			buttons[0]->setText("800x600");
			buttons[1]->setText("1024x768");
			buttons[2]->setText("1280x720");
			buttons[3]->setText("1440x900");
			buttons[4]->setText("1600x900");
			buttons[5]->setText("1920x1080");
			buttons[6]->setText("Menu");

			buttons[0]->connect("Pressed", signalChangeTo800x600);
			buttons[1]->connect("Pressed", signalChangeTo1024x768);
			buttons[2]->connect("Pressed", signalChangeTo1280x720);
			buttons[3]->connect("Pressed", signalChangeTo1440x900);
			buttons[4]->connect("Pressed", signalChangeTo1600x900);
			buttons[5]->connect("Pressed", signalChangeTo1920x1080);
			buttons[6]->connect("Pressed", signalGoToMenu);

			for (int i = 0; i < maxSlidersAndLabels; i++)
			{
				labels[i]= tgui::Label::create();
				labels[i]->setRenderer(blackTheme.getRenderer("Label"));
				labels[i]->setTextSize(guiTextSize);
				labels[i]->setInheritedFont(fontButtons);
				gui.add(labels[i]);

				sliders[i]= tgui::Slider::create();
				sliders[i]->setRenderer(blackTheme.getRenderer("Slider"));
				sliders[i]->setMinimum(0);
				sliders[i]->setMaximum(100);
				sliders[i]->setSize(350, 30);
				gui.add(sliders[i]);
			}

			labels[0]->setText("Music Volume");
			labels[0]->setPosition(guiXPosition, 210);
			labels[1]->setText("Sound Volume");
			labels[1]->setPosition(guiXPosition, 570);

			sliders[0]->setPosition(guiXPosition, 310);
			sliders[0]->setValue(static_cast<float>(globalMusicVolume));
			sliders[1]->setPosition(guiXPosition, 670);
			sliders[1]->setValue(static_cast<float>(globalSoundVolume));

			setHasScreenFinished(false);
		}

		void SettingsScreen::input()
		{

		}

		void SettingsScreen::update()
		{
			globalMusicVolume = static_cast<int>(sliders[0]->getValue());
			globalSoundVolume=static_cast<int>(sliders[1]->getValue());
			input();
		}

		void SettingsScreen::draw()
		{
			_window.draw(backgroundSprite);
		}

		void SettingsScreen::deInit()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i]->setVisible(false);
			}
			for (int i = 0; i < maxSlidersAndLabels; i++)
			{
				labels[i]->setVisible(false);
				sliders[i]->setVisible(false);
			}
			// Config File

			configVolume.child("sound").attribute("value").set_value(static_cast<float>(globalSoundVolume));
			configVolume.child("music").attribute("value").set_value(static_cast<float>(globalMusicVolume));
			configResolution.child("width").attribute("value").set_value(Game::getNewScreenWidth());
			configResolution.child("height").attribute("value").set_value(Game::getNewScreenHeight());
			std::cout << "Saving result: " << config.save_file("res/assets/config/config.xml") << std::endl;
		}

		bool SettingsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}