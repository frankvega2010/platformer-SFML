#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include "Setup\game.h"
#include "setup/screens.h"
#include "setup/character.h"
#include "setup/level.h"
#include "setup\weapon.h"
#include "setup/particles.h"
#include "STP/TMXLoader.hpp"

#include "Thor/Animations.hpp"
#include "Thor/Time.hpp"
#include "Thor/Math.hpp"
#include "spriteanimation.h"

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
	//extern sf::SoundBuffer pistolShootBuffer;

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