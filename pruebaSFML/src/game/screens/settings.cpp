#include "settings.h"

//#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"

using namespace Game_Namespace;
using namespace Gameplay_Section;

namespace Game_Namespace
{
	static const int maxButtons = 7;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr buttons[maxButtons];

	static tgui::Button::Ptr controlsButton;

	static tgui::Slider::Ptr sliderMusic;

	static tgui::Label::Ptr labelMusicVolume;

	static tgui::Slider::Ptr sliderSound;

	static tgui::Label::Ptr labelSoundVolume;

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

		static void signalGoToControls()
		{
			Game::setButtonOption(buttonControls);
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

		//static void signalToggleFullscreen()
		//{
		//	//_window.
		//	//_window.setPosition(sf::Vector2i(0,0));
		//	if (Game::getDefaultStyle() == sf::Style::Default) Game::setDefaultStyle(sf::Style::Fullscreen);
		//	else if (Game::getDefaultStyle() == sf::Style::Fullscreen)Game::setDefaultStyle(sf::Style::Default);
		//	_window.create(sf::VideoMode(Game::getScreenWidth(), Game::getScreenHeight()), "SFML Template", Game::getDefaultStyle());
		//	//_window.setSize(sf::Vector2u(Game::getNewScreenWidth(), Game::getNewScreenHeight()));
		//	//_window.create();
		//}

		void SettingsScreen::init()
		{
			int maxDistance = 0;
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i] = tgui::Button::create();
				gui.add(buttons[i]);
				buttons[i]->setRenderer(blackTheme.getRenderer("Button"));
				buttons[i]->setSize(240, 100);
				buttons[i]->setTextSize(40);// 240 100

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
			//buttons[6]->setText("Fullscreen");
			buttons[6]->setText("Menu");

			buttons[0]->connect("Pressed", signalChangeTo800x600);
			buttons[1]->connect("Pressed", signalChangeTo1024x768);
			buttons[2]->connect("Pressed", signalChangeTo1280x720);
			buttons[3]->connect("Pressed", signalChangeTo1440x900);
			buttons[4]->connect("Pressed", signalChangeTo1600x900);
			buttons[5]->connect("Pressed", signalChangeTo1920x1080);
			//buttons[6]->connect("Pressed", signalToggleFullscreen);
			buttons[6]->connect("Pressed", signalGoToMenu);

			labelMusicVolume = tgui::Label::create();
			labelMusicVolume->setRenderer(blackTheme.getRenderer("Label"));
			labelMusicVolume->setText("Music Volume");
			labelMusicVolume->setPosition(500, 180);
			labelMusicVolume->setTextSize(40);
			gui.add(labelMusicVolume);

			sliderMusic = tgui::Slider::create();
			sliderMusic->setRenderer(blackTheme.getRenderer("Slider"));
			sliderMusic->setPosition(500, 280);
			sliderMusic->setSize(300, 30);
			sliderMusic->setValue(6);
			gui.add(sliderMusic);

			labelSoundVolume = tgui::Label::create();
			labelSoundVolume->setRenderer(blackTheme.getRenderer("Label"));
			labelSoundVolume->setText("Sound Volume");
			labelSoundVolume->setPosition(500, 480);
			labelSoundVolume->setTextSize(40);
			gui.add(labelSoundVolume);

			sliderSound = tgui::Slider::create();
			sliderSound->setRenderer(blackTheme.getRenderer("Slider"));
			sliderSound->setMinimum(0);
			sliderSound->setMaximum(100);
			sliderSound->setPosition(500, 580);
			sliderSound->setSize(300, 30);
			sliderSound->setValue(globalSoundVolume);
			gui.add(sliderSound);

			controlsButton = tgui::Button::create();
			gui.add(controlsButton);
			controlsButton->setRenderer(blackTheme.getRenderer("Button"));
			controlsButton->setSize(250, 110);
			controlsButton->setTextSize(40);// 240 100
			controlsButton->setPosition(530, 780);
			controlsButton->setText("Controls");
			controlsButton->connect("Pressed", signalGoToControls);

			setHasScreenFinished(false);
		}

		void SettingsScreen::input()
		{

		}

		void SettingsScreen::update()
		{
			globalSoundVolume=sliderSound->getValue();
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
			labelMusicVolume->setVisible(false);
			sliderMusic->setVisible(false);
			labelSoundVolume->setVisible(false);
			sliderSound->setVisible(false);
			controlsButton->setVisible(false);
		}

		bool SettingsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}