#ifndef SETTINGS_H
#define SETTINGS_H
#include "game.h"
#include "setup/screens.h"
namespace Juego
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
		/*void UpdateSettingsScreen();
		void InitSettingsScreen();
		bool FinishSettingsScreen();
		void DrawSettings();*/
	}
}
#endif // SETTINGS_H