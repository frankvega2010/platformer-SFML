#ifndef PAUSE_H
#define PAUSE_H
#include "game.h"
#include "setup/screens.h"

namespace Game_Namespace
{

	namespace Pause_Section
	{
		class PauseScreen :public Screens
		{
		private:
		public:
			PauseScreen();
			~PauseScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};

	}
}
#endif // PAUSE_H
