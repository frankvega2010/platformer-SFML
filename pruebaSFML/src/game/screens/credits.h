#ifndef CREDITS_H
#define CREDITS_H
#include "Setup/game.h"
#include "setup/screens.h"
namespace Juego
{
	namespace Credits_Section
	{
		class CreditsScreen :public Screens
		{
		private:
		public:
			CreditsScreen();
			~CreditsScreen();
			void init();
			void input();
			void update();
			void draw();
			void deInit();
			bool finish();
		};

		/*void UpdateCreditsScreen();
		void InitCreditsScreen();
		bool FinishCreditsScreen();
		void DrawCredits();*/
	}
}
#endif // CREDITS_H