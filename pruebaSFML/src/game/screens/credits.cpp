#include "credits.h"

#include "Setup/game.h"

namespace newgame
{
	static const int maxButtons = 1;
	static const int maxCreditsTexts = 28;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr button[maxButtons];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	static sf::Font fontCredits;

	static sf::Text creditsText[maxCreditsTexts];

	static unsigned int titleTextSize = 40;

	static unsigned int subtitleTextSize1 = 30;

	static unsigned int subtitleTextSize2 = 20;

	static float posTextX1 = 150;

	static float posTextX2 = 180;

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
				button[i]->setPosition(120, 920);
			}

			button[0]->setText("Menu");

			for (int i = 0; i < maxCreditsTexts; i++)
			{
				creditsText[i].setFont(fontCredits);
				creditsText[i].setFillColor(sf::Color::White);
			}

			creditsText[0].setCharacterSize(titleTextSize);
			creditsText[0].setPosition(posTextX1, 20);
			creditsText[0].setFillColor(sf::Color::Red);
			creditsText[0].setString("Patient Zero v1.0");

			creditsText[1].setCharacterSize(subtitleTextSize1);
			creditsText[1].setPosition(posTextX1, 70);
			creditsText[1].setString("Game made by:");

			creditsText[2].setCharacterSize(subtitleTextSize2);
			creditsText[2].setPosition(posTextX1, 110);
			creditsText[2].setString("Franco Vega and Mariano Martinez.");

			creditsText[3].setCharacterSize(subtitleTextSize1);
			creditsText[3].setPosition(posTextX1, 140);
			creditsText[3].setString("Assets:");

			creditsText[4].setCharacterSize(subtitleTextSize2);
			creditsText[4].setPosition(posTextX1, 180);
			creditsText[4].setString("- Crosshair: Crosshair pack, Kenney, https://www.kenney.nl/assets/crosshair-pack.");

			creditsText[5].setCharacterSize(subtitleTextSize2);
			creditsText[5].setPosition(posTextX1, 210);
			creditsText[5].setString("- Sounds: ");

			creditsText[6].setCharacterSize(subtitleTextSize2);
			creditsText[6].setPosition(posTextX2, 240);
			creditsText[6].setString("- ZOMBIE10.wav, JarAxe, https://freesound.org/people/JarAxe/sounds/180394/.");

			creditsText[7].setCharacterSize(subtitleTextSize2);
			creditsText[7].setPosition(posTextX2, 270);
			creditsText[7].setString("- Flesh Bite.wav, jgriffie919, https://freesound.org/people/jgriffie919/sounds/400174/.");

			creditsText[8].setCharacterSize(subtitleTextSize2);
			creditsText[8].setPosition(posTextX2, 300);
			creditsText[8].setString("- Zombie 1, Under7dude, https://freesound.org/people/Under7dude/sounds/163440/.");

			creditsText[9].setCharacterSize(subtitleTextSize2);
			creditsText[9].setPosition(posTextX2, 330);
			creditsText[9].setString("- Footstep_Metal_1.wav, GiocoSound, https://freesound.org/people/GiocoSound/sounds/421134/.");

			creditsText[10].setCharacterSize(subtitleTextSize2);
			creditsText[10].setPosition(posTextX2, 360);
			creditsText[10].setString("- Footstep_Metal_Crouch_1.wav, GiocoSound, https://freesound.org/people/GiocoSound/sounds/421147/.");

			creditsText[11].setCharacterSize(subtitleTextSize2);
			creditsText[11].setPosition(posTextX2, 390);
			creditsText[11].setString("- Single Pistol Gunshoot 4.wav, morganpurkis, https://freesound.org/people/morganpurkis/sounds/391328/.");

			creditsText[12].setCharacterSize(subtitleTextSize2);
			creditsText[12].setPosition(posTextX1, 420);
			creditsText[12].setString("- Fonts:");

			creditsText[13].setCharacterSize(subtitleTextSize2);
			creditsText[13].setPosition(posTextX2, 450);
			creditsText[13].setString("- Times New Yorker, D.O.C.S., https://www.dafont.com/times-new-yorker.font.");

			creditsText[14].setCharacterSize(subtitleTextSize2);
			creditsText[14].setPosition(posTextX2, 480);
			creditsText[14].setString("- Roman New Times, winty5, https://www.dafont.com/es/roman-new-times.font.");

			creditsText[15].setCharacterSize(subtitleTextSize2);
			creditsText[15].setPosition(posTextX2, 510);
			creditsText[15].setString("- Sansation, Bernd Montag, https://www.dafont.com/es/sansation.font.");

			creditsText[16].setCharacterSize(subtitleTextSize2);
			creditsText[16].setPosition(posTextX1, 540);
			creditsText[16].setString("- Tilemaps:");

			creditsText[17].setCharacterSize(subtitleTextSize2);
			creditsText[17].setPosition(posTextX2, 570);
			creditsText[17].setString("- Sci-fi platform tiles, Eris, https://opengameart.org/content/sci-fi-platform-tiles.");

			creditsText[18].setCharacterSize(subtitleTextSize2);
			creditsText[18].setPosition(posTextX2, 600);
			creditsText[18].setString("- Platformer Art: Requests, Kenney, https://www.kenney.nl/assets/platformer-art-requests.");

			creditsText[19].setCharacterSize(subtitleTextSize2);
			creditsText[19].setPosition(posTextX1, 630);
			creditsText[19].setString("- Music: made with BoscaCeoil.");

			creditsText[20].setCharacterSize(subtitleTextSize1);
			creditsText[20].setPosition(posTextX1, 670);
			creditsText[20].setString("Tools used:");

			creditsText[21].setCharacterSize(subtitleTextSize2);
			creditsText[21].setPosition(posTextX1, 710);
			creditsText[21].setString("- SFML.");

			creditsText[22].setCharacterSize(subtitleTextSize2);
			creditsText[22].setPosition(posTextX1, 740);
			creditsText[22].setString("- Thor (SFML lib).");

			creditsText[23].setCharacterSize(subtitleTextSize2);
			creditsText[23].setPosition(posTextX1, 770);
			creditsText[23].setString("- TGUI (SFML lib).");

			creditsText[24].setCharacterSize(subtitleTextSize2);
			creditsText[24].setPosition(posTextX1, 800);
			creditsText[24].setString("- STP (SFML lib).");

			creditsText[25].setCharacterSize(subtitleTextSize2);
			creditsText[25].setPosition(posTextX1, 830);
			creditsText[25].setString("- DragonBones.");

			creditsText[26].setCharacterSize(subtitleTextSize2);
			creditsText[26].setPosition(posTextX1, 860);
			creditsText[26].setString("- Adobe Illustrator.");

			creditsText[27].setCharacterSize(subtitleTextSize2);
			creditsText[27].setPosition(posTextX1, 890);
			creditsText[27].setString("- Adobe Photoshop.");


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