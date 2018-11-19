#include "credits.h"

//#include "raylib.h"


namespace Juego
{
	static const int maxButtons = 2;

	static tgui::Theme blackTheme{ "res/assets/themes/Black.txt" };

	static tgui::Button::Ptr buttons[maxButtons];

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
			int maxDistance = 0;
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i] = tgui::Button::create();
				gui.add(buttons[i]);
				buttons[i]->setRenderer(blackTheme.getRenderer("Button"));
				buttons[i]->setSize(240, 100);
				buttons[i]->setTextSize(50);// 240 100

				buttons[i]->setPosition(120, 700 + maxDistance);

				maxDistance = maxDistance + 120;
			}
			maxDistance = 0;

			buttons[0]->setText("More");
			buttons[1]->setText("Menu");

			//buttons[0]->connect("Pressed", signalChangeTo800x600);
			buttons[1]->connect("Pressed", signalGoToMenu);

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

		}

		void CreditsScreen::deInit()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i]->setVisible(false);
			}
		}

		bool CreditsScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}