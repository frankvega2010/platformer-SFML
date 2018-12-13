#include "credits.h"

#include "Setup/game.h"

namespace newgame
{
	static const int maxButtons = 1;
	static const int maxCreditsTexts = 50;

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

	static unsigned int posTextY = 20;

	static unsigned int posTextY2 = 220;

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
				else if (i == 1 || i == 3 || i == 35 || i==46)
					creditsText[i].setCharacterSize(subtitleTextSize1);
				else
					creditsText[i].setCharacterSize(subtitleTextSize2);
			}

			creditsText[0].setFillColor(sf::Color::Red);
			creditsText[0].setString("Patient Zero v1.1");
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
			creditsText[20].setString("- medikit.wav, Syna-Max, https://freesound.org/people/Syna-Max/sounds/63833/.");
			creditsText[21].setString("- Search in a bag, Tristan_Lohengrin, https://freesound.org/people/Tristan_Lohengrin/sounds/233441/.");
			creditsText[22].setString("- Weapons_GunUnHolster.wav, duckduckpony, https://freesound.org/people/duckduckpony/sounds/204043/.");
			creditsText[23].setString("- Full Reload of a Pistol (Mixed), EFlexMusic, https://freesound.org/people/EFlexMusic/sounds/370251/.");
			creditsText[24].setString("- 9mm Pistol Quick Load.wav, EverydaySounds, https://freesound.org/people/EverydaySounds/sounds/125074/.");
			creditsText[25].setString("- Goblin Scream, qubodup, https://freesound.org/people/qubodup/sounds/442816/.");
			creditsText[26].setString("- Dog Begging.wav, Coral_Island_Studios, https://freesound.org/people/Coral_Island_Studios/sounds/277195/.");
			creditsText[27].setString("- Dog Growl - Beast / Creature, coldvet, https://freesound.org/people/coldvet/sounds/404920/.");
			creditsText[28].setString("- Fonts:");
			creditsText[29].setString("- Times New Yorker, D.O.C.S., https://www.dafont.com/times-new-yorker.font.");
			creditsText[30].setString("- Roman New Times, winty5, https://www.dafont.com/es/roman-new-times.font.");
			creditsText[31].setString("- Sansation, Bernd Montag, https://www.dafont.com/es/sansation.font.");
			creditsText[32].setString("- Tilemaps:");
			creditsText[33].setString("- Sci-fi platform tiles, Eris, https://opengameart.org/content/sci-fi-platform-tiles.");
			creditsText[34].setString("- Platformer Art: Requests, Kenney, https://www.kenney.nl/assets/platformer-art-requests.");
			creditsText[35].setString("Tools used:");
			creditsText[36].setString("- SFML.");
			creditsText[37].setString("- Thor (SFML lib).");
			creditsText[38].setString("- TGUI (SFML lib).");
			creditsText[39].setString("- STP (SFML lib).");
			creditsText[40].setString("- DragonBones.");
			creditsText[41].setString("- Adobe Illustrator.");
			creditsText[42].setString("- Adobe Photoshop.");
			creditsText[43].setString("- Audacity.");
			creditsText[44].setString("- BoscaCeoil.");
			creditsText[45].setString("- Tilled.");
			creditsText[46].setString("- Testers:.");
			creditsText[47].setString("- Lucas Fernandez.");
			creditsText[48].setString("- Dylan Piserchia.");
			creditsText[49].setString("- Tomas Peralta.");

			button[0]->connect("Pressed", signalGoToMenu);

			scrollbar = tgui::Scrollbar::create();
			scrollbar->setRenderer(blackTheme.getRenderer("Scrollbar"));
			scrollbar->setPosition(900, 90);
			scrollbar->setSize(18, 740);
			scrollbar->setMaximum(630);
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
			posTextY = ((scrollbar->getValue())*-1);
			creditsText[0].setPosition(posTextX1,static_cast<float>( posTextY));
			creditsText[1].setPosition(posTextX1, static_cast<float>(posTextY + 50));
			creditsText[2].setPosition(posTextX1, static_cast<float>(posTextY + 90));
			creditsText[3].setPosition(posTextX1, static_cast<float>(posTextY + 120));
			creditsText[4].setPosition(posTextX1, static_cast<float>(posTextY + 160));
			creditsText[5].setPosition(posTextX1, static_cast<float>(posTextY + 190));
			creditsText[6].setPosition(posTextX2, static_cast<float>(posTextY + 220));
			creditsText[7].setPosition(posTextX2, static_cast<float>(posTextY + 250));
			creditsText[8].setPosition(posTextX2, static_cast<float>(posTextY + 280));
			creditsText[9].setPosition(posTextX2, static_cast<float>(posTextY + 310));
			creditsText[10].setPosition(posTextX2, static_cast<float>(posTextY + 340));
			creditsText[11].setPosition(posTextX2, static_cast<float>(posTextY + 370));
			creditsText[12].setPosition(posTextX2, static_cast<float>(posTextY + 400));
			creditsText[13].setPosition(posTextX2, static_cast<float>(posTextY + 430));
			creditsText[14].setPosition(posTextX2, static_cast<float>(posTextY + 460));
			creditsText[15].setPosition(posTextX2, static_cast<float>(posTextY + 490));
			creditsText[16].setPosition(posTextX2, static_cast<float>(posTextY + 520));
			creditsText[17].setPosition(posTextX2, static_cast<float>(posTextY + 550));
			creditsText[18].setPosition(posTextX2, static_cast<float>(posTextY + 580));
			creditsText[19].setPosition(posTextX2, static_cast<float>(posTextY + 610));
			creditsText[20].setPosition(posTextX2, static_cast<float>(posTextY + 640));
			creditsText[21].setPosition(posTextX2, static_cast<float>(posTextY + 670));
			creditsText[22].setPosition(posTextX2, static_cast<float>(posTextY + 700));
			creditsText[23].setPosition(posTextX2, static_cast<float>(posTextY + 730));
			creditsText[24].setPosition(posTextX2, static_cast<float>(posTextY + 760));
			creditsText[25].setPosition(posTextX2, static_cast<float>(posTextY + 790));
			creditsText[26].setPosition(posTextX2, static_cast<float>(posTextY + 820));
			creditsText[27].setPosition(posTextX2, static_cast<float>(posTextY + 850));
			creditsText[28].setPosition(posTextX1, static_cast<float>(posTextY + 880));
			creditsText[29].setPosition(posTextX2, static_cast<float>(posTextY + 910));
			creditsText[30].setPosition(posTextX2, static_cast<float>(posTextY + 940));
			creditsText[31].setPosition(posTextX2, static_cast<float>(posTextY + 970));
			creditsText[32].setPosition(posTextX1, static_cast<float>(posTextY + 1000));
			creditsText[33].setPosition(posTextX2, static_cast<float>(posTextY + 1030));
			creditsText[34].setPosition(posTextX2, static_cast<float>(posTextY + 1060));
			creditsText[35].setPosition(posTextX1, static_cast<float>(posTextY + 1100));
			creditsText[36].setPosition(posTextX1, static_cast<float>(posTextY + 1140));
			creditsText[37].setPosition(posTextX1, static_cast<float>(posTextY + 1170));
			creditsText[38].setPosition(posTextX1, static_cast<float>(posTextY + 1200));
			creditsText[39].setPosition(posTextX1, static_cast<float>(posTextY + 1230));
			creditsText[40].setPosition(posTextX1, static_cast<float>(posTextY + 1260));
			creditsText[41].setPosition(posTextX1, static_cast<float>(posTextY + 1290));
			creditsText[42].setPosition(posTextX1, static_cast<float>(posTextY + 1320));
			creditsText[43].setPosition(posTextX1, static_cast<float>(posTextY + 1350));
			creditsText[44].setPosition(posTextX1, static_cast<float>(posTextY + 1380));
			creditsText[45].setPosition(posTextX1, static_cast<float>(posTextY + 1410));
			creditsText[46].setPosition(posTextX1, static_cast<float>(posTextY + 1450));
			creditsText[47].setPosition(posTextX1, static_cast<float>(posTextY + 1490));
			creditsText[48].setPosition(posTextX1, static_cast<float>(posTextY + 1520));
			creditsText[49].setPosition(posTextX1, static_cast<float>(posTextY + 1550));
		}

		void CreditsScreen::draw()
		{
			_window.draw(backgroundSprite);
			for (int i = 0; i < maxCreditsTexts; i++)
			{
				if (creditsText[i].getPosition().y<950)
				{
					_window.draw(creditsText[i]);
				}
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