#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include "Setup\game.h"
#include "setup/screens.h"
#include "setup/level.h"
#include "Thor/Time.hpp"


namespace newgame
{
	enum gameplayOptions
	{
		buttonContinue = 20,
		buttonRestart,
		buttonGameOver,
		buttonQuitToMenu
	};

	extern int scoreLimit;

	namespace Gameplay_Section
	{
		class GameplayScreen :public Screens
		{
		private:
		public:
			GameplayScreen();
			~GameplayScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
			void restart();
		};

	}
}
#endif // GAMEPLAY_H