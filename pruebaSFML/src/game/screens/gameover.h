#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "Setup/game.h"
#include "Screens/gameplay.h"
#include "setup/screens.h"

namespace newgame
{
	namespace GameOver_Section
	{
		class GameOverScreen :public Screens
		{
		private:
		public:
			GameOverScreen();
			~GameOverScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};
	}
}
#endif // GAMEOVER_H