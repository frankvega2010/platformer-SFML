#ifndef GAMEPLAY_H
#define GAMEPLAY_H
//#include <sstream>
#include "Setup\game.h"
#include "setup/screens.h"
#include "setup/player.h"
#include "STP/TMXLoader.hpp"
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include "Thor/Animations.hpp"
//#include "raylib.h"

namespace Game_Namespace
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