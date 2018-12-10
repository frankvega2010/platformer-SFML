#include "credits.h"

#include "Setup/game.h"

namespace newgame
{
	static const int maxButtons = 1;
	static const int maxCreditsTexts = 36;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr button[maxButtons];

	static tgui::Font fontButtons("res/assets/fonts/times_new_yorker.ttf");

	static sf::Font fontCredits;

	static sf::Text creditsText[maxCreditsTexts];

	static tgui::Scrollbar::Ptr scrollbar;

	static unsigned int titleTextSize = 48;

	static unsigned int subtitleTextSize1 = 38;

	static unsigned int subtitleTextSize2 = 28;

	static float posTextX1 = 150;

	static float posTextX2 = 180;

	static float posTextY = 20;

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
				if (i == 0)
					creditsText[i].setCharacterSize(titleTextSize);
				else if (i == 1 || i == 3 || i == 28)
					creditsText[i].setCharacterSize(subtitleTextSize1);
				else
					creditsText[i].setCharacterSize(subtitleTextSize2);
			}

			creditsText[0].setFillColor(sf::Color::Red);
			creditsText[0].setString("Patient Zero v1.01");
			creditsText[1].setString("Game made by:");
			creditsText[2].setString("Franco Vega and Mariano Martinez.");
			creditsText[3].setString("Assets:");
			creditsText[4].setString("- Crosshair: Crosshair pack, Kenney, https://www.kenney.nl/assets/crosshair-pack.");
			creditsText[5].setString("- Sounds: ");
			creditsText[6].setString("- ZOMBIE10.wav, JarAxe, https://freesound.org/people/JarAxe/sounds/180394/.");
			creditsText[7].setString("- Flesh Bite.wav, jgriffie919, https://freesound.org/people/jgriffie919/sounds/400174/.");
			creditsText[8].setString("- Zombie 1, Under7dude, https://freesound.org/people/Under7dude/sounds/163440/.");
			creditsText[9].setString("- Footstep_Metal_1.wav, GiocoSound, https://freesound.org/people/GiocoSound/sounds/421134/.");
			creditsText[10].setString("- Footstep_Metal_Crouch_1.wav, GiocoSound, https://freesound.org/people/GiocoSound/sounds/421147/.");
			creditsText[11].setString("- Single Pistol Gunshoot 4.wav, morganpurkis, https://freesound.org/people/morganpurkis/sounds/391328/.");
			creditsText[12].setString("- INT Factory nearby 3 water dripping.wav, Adam_n, https://freesound.org/people/Adam_N/sounds/164741/.");
			creditsText[13].setString("- wind_howling_01.wav, Fasolt, https://freesound.org/people/Fasolt/sounds/113173/.");
			creditsText[14].setString("- Zombie distant ambience, ryanconway, https://freesound.org/people/ryanconway/sounds/253362/.");
			creditsText[15].setString("- Gas Chamber Ambience.flac, qubodup, https://freesound.org/people/qubodup/sounds/197255/.");
			creditsText[16].setString("- AKManipulation.wav, Mittelmorder, https://freesound.org/people/Mittelmorder/sounds/122690/.");
			creditsText[17].setString("- smgshoot.wav, tehlordoswag420, https://freesound.org/people/tehlordoswag420/sounds/240377/.");
			creditsText[18].setString("- Various Shotgun Pumps.aif, jeseid77, https://freesound.org/people/jeseid77/sounds/86246/.");
			creditsText[19].setString("- Shotgun Shot/Blast (Outdoors/Close), EFlexMusic, https://freesound.org/people/EFlexMusic/sounds/416280/.");
			creditsText[20].setString("- Fonts:");
			creditsText[21].setString("- Times New Yorker, D.O.C.S., https://www.dafont.com/times-new-yorker.font.");
			creditsText[22].setString("- Roman New Times, winty5, https://www.dafont.com/es/roman-new-times.font.");
			creditsText[23].setString("- Sansation, Bernd Montag, https://www.dafont.com/es/sansation.font.");
			creditsText[24].setString("- Tilemaps:");
			creditsText[25].setString("- Sci-fi platform tiles, Eris, https://opengameart.org/content/sci-fi-platform-tiles.");
			creditsText[26].setString("- Platformer Art: Requests, Kenney, https://www.kenney.nl/assets/platformer-art-requests.");
			creditsText[27].setString("- Music: made with BoscaCeoil.");
			creditsText[28].setString("Tools used:");
			creditsText[29].setString("- SFML.");
			creditsText[30].setString("- Thor (SFML lib).");
			creditsText[31].setString("- TGUI (SFML lib).");
			creditsText[32].setString("- STP (SFML lib).");
			creditsText[33].setString("- DragonBones.");
			creditsText[34].setString("- Adobe Illustrator.");
			creditsText[35].setString("- Adobe Photoshop.");

			button[0]->connect("Pressed", signalGoToMenu);

			scrollbar = tgui::Scrollbar::create();
			scrollbar->setRenderer(blackTheme.getRenderer("Scrollbar"));
			scrollbar->setPosition(900, 90);
			scrollbar->setSize(18, 740);
			scrollbar->setMaximum(200);
			scrollbar->setValue(0);
			gui.add(scrollbar);

			setHasScreenFinished(false);
		}

		void CreditsScreen::input()
		{

		}

		void CreditsScreen::update()
		{
			input();
			posTextY = static_cast<int>((scrollbar->getValue())*-1);
			creditsText[0].setPosition(posTextX1, posTextY);
			creditsText[1].setPosition(posTextX1, posTextY + 50);
			creditsText[2].setPosition(posTextX1, posTextY + 90);
			creditsText[3].setPosition(posTextX1, posTextY + 120);
			creditsText[4].setPosition(posTextX1, posTextY + 160);
			creditsText[5].setPosition(posTextX1, posTextY + 190);
			creditsText[6].setPosition(posTextX2, posTextY + 220);
			creditsText[7].setPosition(posTextX2, posTextY + 250);
			creditsText[8].setPosition(posTextX2, posTextY + 280);
			creditsText[9].setPosition(posTextX2, posTextY + 310);
			creditsText[10].setPosition(posTextX2, posTextY + 340);
			creditsText[11].setPosition(posTextX2, posTextY + 370);
			creditsText[12].setPosition(posTextX2, posTextY + 400);
			creditsText[13].setPosition(posTextX2, posTextY + 430);
			creditsText[14].setPosition(posTextX2, posTextY + 460);
			creditsText[15].setPosition(posTextX2, posTextY + 490);
			creditsText[16].setPosition(posTextX2, posTextY + 520);
			creditsText[17].setPosition(posTextX2, posTextY + 550);
			creditsText[18].setPosition(posTextX2, posTextY + 580);
			creditsText[19].setPosition(posTextX2, posTextY + 610);
			creditsText[20].setPosition(posTextX1, posTextY + 640);
			creditsText[21].setPosition(posTextX2, posTextY + 670);
			creditsText[22].setPosition(posTextX2, posTextY + 700);
			creditsText[23].setPosition(posTextX2, posTextY + 730);
			creditsText[24].setPosition(posTextX1, posTextY + 760);
			creditsText[25].setPosition(posTextX2, posTextY + 790);
			creditsText[26].setPosition(posTextX2, posTextY + 820);
			creditsText[27].setPosition(posTextX1, posTextY + 850);
			creditsText[28].setPosition(posTextX1, posTextY + 890);
			creditsText[29].setPosition(posTextX1, posTextY + 930);
			creditsText[30].setPosition(posTextX1, posTextY + 960);
			creditsText[31].setPosition(posTextX1, posTextY + 990);
			creditsText[32].setPosition(posTextX1, posTextY + 1020);
			creditsText[33].setPosition(posTextX1, posTextY + 1050);
			creditsText[34].setPosition(posTextX1, posTextY + 1080);
			creditsText[35].setPosition(posTextX1, posTextY + 1110);
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
			scrollbar->setVisible(false);
		}

		bool CreditsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}