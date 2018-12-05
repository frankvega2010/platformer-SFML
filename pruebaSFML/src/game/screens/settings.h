#ifndef SETTINGS_H
#define SETTINGS_H
#include "setup/screens.h"
namespace Game_Namespace
{
	namespace Settings_Section
	{
		class SettingsScreen :public Screens
		{
		private:
		public:
			SettingsScreen();
			~SettingsScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};
	}
}
#endif // SETTINGS_H