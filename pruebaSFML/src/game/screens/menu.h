#ifndef MENU_H
#define MENU_H
#include "game.h"
#include "setup/screens.h"

namespace Game_Namespace
{
	enum menuOptions {
		buttonPlay = 10,
		buttonSettings,
		buttonCredits,
		buttonResume,
		buttonPause,
		buttonMenu,
		buttonTutorial,
		buttonQuit
	};

	//extern tgui::Gui gui;

	namespace Menu_Section
	{
		class MenuScreen :public Screens
		{
		private:
		public:
			MenuScreen();
			~MenuScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};

		/*void UpdateMenuScreen();
		void InitMenuScreen();
		bool FinishMenuScreen();
		void DrawMenu();*/
	}
}
#endif // MENU_H