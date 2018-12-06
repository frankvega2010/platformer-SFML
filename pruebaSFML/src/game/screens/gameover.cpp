#include "gameover.h"

namespace newgame
{
	static const int Restart_Gameplay = 5;

	namespace GameOver_Section
	{
		GameOverScreen::GameOverScreen()
		{
		}

		GameOverScreen::~GameOverScreen()
		{
		}

		void GameOverScreen::init()
		{
		}

		void GameOverScreen::input()
		{
		}

		void GameOverScreen::update()
		{
			input();
		}

		void GameOverScreen::draw()
		{
		}

		void GameOverScreen::deInit()
		{

		}

		bool GameOverScreen::finish()
		{
			return getHasScreenFinished();
		}
	}
}