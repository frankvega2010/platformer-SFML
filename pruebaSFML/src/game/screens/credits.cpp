#include "credits.h"

#include "Setup/game.h"

namespace Game_Namespace
{
	static const int maxButtons = 1;
	static const int maxCreditsTexts = 18;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr button[maxButtons];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	static sf::Font fontCredits;

	static sf::Text creditsText[maxCreditsTexts];

	namespace Credits_Section
	{

		CreditsScreen::CreditsScreen()
		{
		}

		CreditsScreen::~CreditsScreen()
		{
		}

		static void signalGoToMenu()
		{
			Screens::setHasScreenFinished(true);
		}

		void CreditsScreen::init()
		{
			fontCredits.loadFromFile("res/assets/fonts/times_new_yorker.ttf");
			for (int i = 0; i < maxButtons; i++)
			{
				button[i] = tgui::Button::create();
				gui.add(button[i]);
				button[i]->setRenderer(blackTheme.getRenderer("Button"));
				button[i]->setSize(170, 60);
				button[i]->setTextSize(30);// 240 100
				button[i]->setInheritedFont(fontButtons);
				button[i]->setPosition(120, 850);
			}

			button[0]->setText("Menu");

			creditsText[0].setCharacterSize(50);
			creditsText[0].setFont(fontCredits);
			creditsText[0].setPosition(150, 50);
			creditsText[0].setFillColor(sf::Color::Red);
			creditsText[0].setString("Patient Zero v1.0");

			creditsText[1].setCharacterSize(40);
			creditsText[1].setFont(fontCredits);
			creditsText[1].setPosition(150, 110);
			creditsText[1].setFillColor(sf::Color::White);
			creditsText[1].setString("Game made by:");

			creditsText[2].setCharacterSize(30);
			creditsText[2].setFont(fontCredits);
			creditsText[2].setPosition(150, 150);
			creditsText[2].setFillColor(sf::Color::White);
			creditsText[2].setString("Franco Vega and Mariano Martinez");

			creditsText[3].setCharacterSize(40);
			creditsText[3].setFont(fontCredits);
			creditsText[3].setPosition(150, 200);
			creditsText[3].setFillColor(sf::Color::White);
			creditsText[3].setString("Assets:");

			creditsText[4].setCharacterSize(30);
			creditsText[4].setFont(fontCredits);
			creditsText[4].setPosition(150, 250);
			creditsText[4].setFillColor(sf::Color::White);
			creditsText[4].setString("- Crosshair: https://www.kenney.nl/assets/crosshair-pack.");

			creditsText[5].setCharacterSize(30);
			creditsText[5].setFont(fontCredits);
			creditsText[5].setPosition(150, 290);
			creditsText[5].setFillColor(sf::Color::White);
			creditsText[5].setString("- Sounds: https://freesound.org/.");

			creditsText[6].setCharacterSize(30);
			creditsText[6].setFont(fontCredits);
			creditsText[6].setPosition(150, 330);
			creditsText[6].setFillColor(sf::Color::White);
			creditsText[6].setString("- Music: Made with BoscaCeoil.");

			creditsText[7].setCharacterSize(30);
			creditsText[7].setFont(fontCredits);
			creditsText[7].setPosition(150, 370);
			creditsText[7].setFillColor(sf::Color::White);
			creditsText[7].setString("- Fonts: https://www.dafont.com/ (Roman New Times, Times New Yorker, Sansation).");

			creditsText[8].setCharacterSize(30);
			creditsText[8].setFont(fontCredits);
			creditsText[8].setPosition(150, 410);
			creditsText[8].setFillColor(sf::Color::White);
			creditsText[8].setString("- Tilemaps: https://opengameart.org/content/sci-fi-platform-tiles, https://www.kenney.nl/assets/platformer-art-requests ");

			creditsText[9].setCharacterSize(30);
			creditsText[9].setFont(fontCredits);
			creditsText[9].setPosition(150, 450);
			creditsText[9].setFillColor(sf::Color::White);
			creditsText[9].setString("");

			creditsText[10].setCharacterSize(40);
			creditsText[10].setFont(fontCredits);
			creditsText[10].setPosition(150, 490);
			creditsText[10].setFillColor(sf::Color::White);
			creditsText[10].setString("Tools used:");

			creditsText[11].setCharacterSize(30);
			creditsText[11].setFont(fontCredits);
			creditsText[11].setPosition(150, 540);
			creditsText[11].setFillColor(sf::Color::White);
			creditsText[11].setString("- SFML");

			creditsText[12].setCharacterSize(30);
			creditsText[12].setFont(fontCredits);
			creditsText[12].setPosition(150, 580);
			creditsText[12].setFillColor(sf::Color::White);
			creditsText[12].setString("- Thor(SMFL Lib)");

			creditsText[13].setCharacterSize(30);
			creditsText[13].setFont(fontCredits);
			creditsText[13].setPosition(150, 620);
			creditsText[13].setFillColor(sf::Color::White);
			creditsText[13].setString("- TGUI(SFML Lib)");

			creditsText[14].setCharacterSize(30);
			creditsText[14].setFont(fontCredits);
			creditsText[14].setPosition(150, 660);
			creditsText[14].setFillColor(sf::Color::White);
			creditsText[14].setString("- STP (SFML Lib)");

			creditsText[15].setCharacterSize(30);
			creditsText[15].setFont(fontCredits);
			creditsText[15].setPosition(150, 700);
			creditsText[15].setFillColor(sf::Color::White);
			creditsText[15].setString("- DragonBones");

			creditsText[16].setCharacterSize(30);
			creditsText[16].setFont(fontCredits);
			creditsText[16].setPosition(150, 740);
			creditsText[16].setFillColor(sf::Color::White);
			creditsText[16].setString("- Adobe Illustrator");

			creditsText[17].setCharacterSize(30);
			creditsText[17].setFont(fontCredits);
			creditsText[17].setPosition(150, 780);
			creditsText[17].setFillColor(sf::Color::White);
			creditsText[17].setString("- Adobe Photoshop");


			button[0]->connect("Pressed", signalGoToMenu);

			setHasScreenFinished(false);
		}

		void CreditsScreen::input()
		{

		}

		void CreditsScreen::update()
		{

			input();
		}

		void CreditsScreen::draw()
		{
			_window.draw(backgroundSprite);
			for (int i = 0; i < maxCreditsTexts; i++)
			{
				_window.draw(creditsText[i]);
			}
		}

		void CreditsScreen::deInit()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				button[i]->setVisible(false);
			}
		}

		bool CreditsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}