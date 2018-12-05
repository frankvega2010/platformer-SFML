#ifndef MENU_H
#define MENU_H

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
	}
}
#endif // MENU_H